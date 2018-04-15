# The ARMv7 is significanly faster due to the use of the hardware FPU
# APP_PIE := false
# APP_CFLAGS := -fvisibility=hidden
# APP_CPPFLAGS := -fvisibility=hidden
APP_CPPFLAGS := -fexceptions -frtti	#允许异常功能，及运行时类型识别  
APP_CPPFLAGS += -std=c++11			#允许使用c++11的函数等功能 
APP_ABI := armeabi-v7a armeabi x86
APP_STL := gnustl_static
APP_PLATFORM := android-21
