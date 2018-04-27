LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := filenative
LOCAL_SRC_FILES := filenative.cpp

LOCAL_SHARED_LIBRARIES += libandroid
LOCAL_LDLIBS += -llog -landroid -lEGL -lz

include $(BUILD_SHARED_LIBRARY)