LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := v4l2-compliance
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -DNO_LIBV4L2
LOCAL_CFLAGS += -Wno-missing-braces
LOCAL_CFLAGS += -Wno-missing-field-initializers
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../.. \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../common

LOCAL_SRC_FILES := \
    v4l2-compliance.cpp v4l2-test-debug.cpp v4l2-test-input-output.cpp \
    v4l2-test-controls.cpp v4l2-test-io-config.cpp v4l2-test-formats.cpp \
    v4l2-test-buffers.cpp v4l2-test-codecs.cpp v4l2-test-colors.cpp

# Include for C++ support in Android Froyo to Kitkat.
ifneq ($(filter 8 9 10 11 12 13 14 15 16 17 18 19,$(PLATFORM_SDK_VERSION)),)
LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk
endif
include $(BUILD_EXECUTABLE)
