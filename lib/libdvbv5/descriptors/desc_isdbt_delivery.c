/*
 * Copyright (c) 2013 - Mauro Carvalho Chehab <m.chehab@samsung.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * Or, point your browser to http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 */

#include <libdvbv5/desc_isdbt_delivery.h>
#include <libdvbv5/dvb-fe.h>

int isdbt_desc_delivery_init(struct dvb_v5_fe_parms *parms,
			      const uint8_t *buf, struct dvb_desc *desc)
{
	struct isdbt_desc_terrestrial_delivery_system *d = (void *)desc;
	unsigned char *p = (unsigned char *) buf;
	int i;
	size_t len;

	len = sizeof(*d) - offsetof(struct isdbt_desc_terrestrial_delivery_system, bitfield);
	memcpy(&d->bitfield, p, len);
	p += len;

	bswap16(d->bitfield);

	d->num_freqs = d->length / 2;
	if (!len)
		return -1;
	d->frequency = malloc(d->num_freqs * sizeof(*d->frequency));
	if (!d->frequency) {
		dvb_perror("Can't allocate space for ISDB-T frequencies");
		return -2;
	}
	memcpy(d->frequency, p, d->num_freqs * sizeof(*d->frequency));

	for (i = 0; i < d->num_freqs; i++)
		bswap16(d->frequency[i]);
	return 0;
}

static const char *interval_name[] = {
	[0] =    "1/4",
	[1] =    "1/8",
	[2] =   "1/16",
	[3] =   "1/32",
};

static const char *tm_name[] = {
	[0] =   "2K",
	[1] =   "4K",
	[2] =   "8K",
	[3] = "AUTO",
};

const uint32_t isdbt_interval[] = {
	[0] = GUARD_INTERVAL_1_32,
	[1] = GUARD_INTERVAL_1_16,
	[2] = GUARD_INTERVAL_1_8,
	[3] = GUARD_INTERVAL_1_4,
};

const uint32_t isdbt_mode[] = {
	[0] = TRANSMISSION_MODE_2K,	/* Mode 1 */
	[1] = TRANSMISSION_MODE_4K,	/* Mode 2 */
	[2] = TRANSMISSION_MODE_8K,	/* Mode 3 */
	[3] = TRANSMISSION_MODE_AUTO	/* Reserved */
};

void isdbt_desc_delivery_print(struct dvb_v5_fe_parms *parms, const struct dvb_desc *desc)
{
	const struct isdbt_desc_terrestrial_delivery_system *d = (const void *) desc;
	int i;

	dvb_loginfo("|           transmission mode %s (%d)",
		tm_name[d->transmission_mode], d->transmission_mode);
	dvb_loginfo("|           guard interval    %s (%d)",
		interval_name[d->guard_interval], d->guard_interval);
	dvb_loginfo("|           area code         %d", d->area_code);

	for (i = 0; i < d->num_freqs; i++) {
		dvb_loginfo("|           frequency[%d]      %ld Hz", i, d->frequency[i] * 1000000l / 7);
	}
}

void isdbt_desc_delivery_free(struct dvb_desc *desc)
{
	const struct isdbt_desc_terrestrial_delivery_system *d = (const void *) desc;

	free(d->frequency);
}
