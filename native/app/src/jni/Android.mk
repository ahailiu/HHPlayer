LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := PlayerCore
LOCAL_SRC_FILES := Native.cpp \
	mediacodec_ndk.cpp

LOCAL_C_INCLUDES :=  \
	$(JNI_H_INCLUDE)

LOCAL_CFLAGS    = -g -Wall
LOCAL_LDLIBS    = -llog -landroid

include $(BUILD_SHARED_LIBRARY)
