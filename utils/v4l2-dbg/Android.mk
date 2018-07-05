LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := v4l2-dbg
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../.. \
    $(LOCAL_PATH)/../../include

LOCAL_SRC_FILES := v4l2-dbg.cpp

# Include for C++ support in Android Froyo to Kitkat.
ifneq ($(filter 8 9 10 11 12 13 14 15 16 17 18 19,$(PLATFORM_SDK_VERSION)),)
LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk
endif
include $(BUILD_EXECUTABLE)
