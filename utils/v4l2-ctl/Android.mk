LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := v4l2-ctl
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -DNO_LIBV4L2
LOCAL_CFLAGS += -Wno-missing-field-initializers
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../.. \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../common

LOCAL_SRC_FILES := \
    v4l2-ctl.cpp v4l2-ctl.h v4l2-ctl-common.cpp v4l2-ctl-tuner.cpp \
    v4l2-ctl-io.cpp v4l2-ctl-stds.cpp v4l2-ctl-vidcap.cpp v4l2-ctl-vidout.cpp \
    v4l2-ctl-overlay.cpp v4l2-ctl-vbi.cpp v4l2-ctl-selection.cpp v4l2-ctl-misc.cpp \
    v4l2-ctl-streaming.cpp v4l2-ctl-sdr.cpp v4l2-ctl-edid.cpp v4l2-ctl-modes.cpp \
    v4l2-tpg-colors.c v4l2-tpg-core.c v4l-stream.c

# Include for C++ support in Android Froyo to Kitkat.
ifneq ($(filter 8 9 10 11 12 13 14 15 16 17 18 19,$(PLATFORM_SDK_VERSION)),)
LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk
endif
include $(BUILD_EXECUTABLE)
