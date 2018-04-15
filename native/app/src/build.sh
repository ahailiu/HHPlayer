#!/bin/bash

PREBUILT=${ANDROID_NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64
PLATFORM=${ANDROID_NDK_ROOT}/platforms/android-9/arch-arm
CUR_PATH=$(pwd)
FFMPEG_OUTPUT_PATH=${CUR_PATH}/../ffmpeg-dev-out
LIB_NAME=libffmpeg.so
LIB_GCC=${PREBUILT}/lib/gcc/arm-linux-androideabi/4.9/libgcc.a

ANDROID_LD=${PREBUILT}/bin/arm-linux-androideabi-ld
EXTRA_LD_FLAGS="-z noexecstack"

make distclean

./configure \
    --disable-avdevice \
    --disable-avfilter \
    --enable-cross-compile \
    --target-os=linux \
    --cross-prefix=${PREBUILT}/bin/arm-linux-androideabi- \
    --sysroot=${PLATFORM} \
    --arch=arm \
    --enable-asm \
    --cpu=cortex-a9 \
    --enable-neon \
    --extra-cflags="-O3 -DANDROID -fpic -mfloat-abi=softfp -mfpu=neon -Wimplicit-function-declaration -DBUILD_CONFIG_TYPE=full" \
    --extra-ldflags="-L${PLATFORM}/usr/lib" \
    --enable-pthreads \
    --enable-static \
    --enable-pic \
    --enable-runtime-cpudetect \
    --prefix=${FFMPEG_OUTPUT_PATH} \
    --disable-linux-perf \
    --enable-debug

make -j32
make install

${ANDROID_LD} \
    -rpath-link=${PLATFORM}/usr/lib -L${PLATFORM}/usr/lib -L${FFMPEG_OUTPUT_PATH}/lib  \
    -shared -nostdlib -Bsymbolic --whole-archive --no-undefined ${EXTRA_LD_FLAGS} \
    ${FFMPEG_OUTPUT_LIBS} \
    -lc -lm -lz --dynamic-linker=/system/bin/linker \
    ${LIB_GCC} \
    -soname ${LIB_NAME} \
    -o ${FFMPEG_OUTPUT_PATH}/${LIB_NAME}
