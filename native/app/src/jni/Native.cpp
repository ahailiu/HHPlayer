/*
 * =====================================================================================
 *
 *       Filename:  Native.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/03/16 17时24分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <android/native_window_jni.h>

#include "mediacodec.h"

static const char *TAG = "NativePlayer";

#define Jni_Print(prio, ...) __android_log_print((prio),  __VA_ARGS__)

static const char *gJavaClassName = "com/tencent/mediaplayer/PlayerNative";



static jmethodID gMediaCodecGetCodecName = NULL;
static jclass    gPlayerNativeClass      = NULL;

jint NativePlayerOpen(JNIEnv *env, jobject obj, jobject surface)
{
    if (!gPlayerNativeClass) {
        gPlayerNativeClass = reinterpret_cast<jclass>(env->NewGlobalRef(obj));
    }

    mc_api  api;
    memset(&api, 0, sizeof(mc_api));

    const char *mimeType = "video/hevc";
    strncpy(api.psz_mime, mimeType, strlen(mimeType));
    api.i_cat = VIDEO_ES;

    if (MediaCodecNdk_Init(&api) < 0) { 
        return -1;
    }

    jstring jmimeType = env->NewStringUTF(mimeType);
    if (!jmimeType) {
        return -1;
    }

    jclass cls = env->GetObjectClass(obj);

    jstring jcodecName = (jstring)env->CallStaticObjectMethod(cls, gMediaCodecGetCodecName, jmimeType);
    if (!jcodecName) {
        env->DeleteLocalRef(jmimeType);
        return -1;
    }

    const char *codecName = env->GetStringUTFChars(jcodecName, NULL);
    env->DeleteLocalRef(jmimeType);

    api.configure(&api, codecName);
    env->ReleaseStringUTFChars(jcodecName, codecName);

    union mc_api_args args;
    memset(&args, 0, sizeof(union mc_api_args));

    args.video.p_surface = (void *)ANativeWindow_fromSurface(env, surface);
    args.video.i_width  = 1080;
    args.video.i_height = 1920;
    args.video.i_angle  = 0;
//    args.video.b_tunneled_playback = true;
    args.video.b_adaptive_playback = true;

    api.start(&api, &args);

    return 0;
}

static JNINativeMethod const gNativeMethods[] = {
    {"NativePlayer_PlayerOpen", "(Landroid/view/Surface;)I", reinterpret_cast<void *>(NativePlayerOpen)}
};


jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env;
    if (JNI_OK != vm->GetEnv(reinterpret_cast<void **> (&env), JNI_VERSION_1_4)) {
        Jni_Print(ANDROID_LOG_ERROR, TAG, "Jni_OnLoad Err.\n");
        return JNI_ERR;
    }

    if (!env) {
        Jni_Print(ANDROID_LOG_ERROR, TAG, "Jni_OnLoad Err, env is NULL.\n");
        return JNI_ERR;
    }

    jclass cls = env->FindClass(gJavaClassName);
    if (!cls) {
        Jni_Print(ANDROID_LOG_ERROR, TAG, "Jni_OnLoad not found java class.\n");
        return JNI_ERR;
    }

    if (JNI_OK != env->RegisterNatives(cls, gNativeMethods, sizeof(gNativeMethods)/sizeof(gNativeMethods[0]))) {
        Jni_Print(ANDROID_LOG_ERROR, TAG, "Jni_OnLoad RegisterNatives Err.\n");
        return JNI_ERR;
    }

    gMediaCodecGetCodecName = env->GetStaticMethodID(cls, "MediaCodec_GetCodecName", "(Ljava/lang/String;)Ljava/lang/String;");
    if (NULL == gMediaCodecGetCodecName) {
        Jni_Print(ANDROID_LOG_ERROR, TAG, "Jni_OnLoad Err, GetStaticMethodID err.\n");
        return JNI_ERR;
    }

    Jni_Print(ANDROID_LOG_INFO, TAG, "Jni_OnLoad Ok.\n");
    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM *vm, void *reserved)
{
    Jni_Print(ANDROID_LOG_INFO, TAG, "Jni_OnUnLoad Ok.\n");
    return ; 
}
