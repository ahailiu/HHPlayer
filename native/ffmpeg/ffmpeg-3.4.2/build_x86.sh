#!/bin/bash

CUR_PATH=$(pwd)
FFMPEG_OUTPUT_PATH=${CUR_PATH}/../ffmpeg-dev-out
LIB_NAME=libffmpeg.so

LD=ld
EXTRA_LD_FLAGS="-z noexecstack"

FFMPEG_OUTPUT_LIBS=" \
    libavcodec/libavcodec.a \
    libswresample/libswresample.a \
    libavformat/libavformat.a \
    libavutil/libavutil.a \
    libswscale/libswscale.a \
    "

make distclean

./configure \
    --disable-x86asm  \
    --disable-avdevice \
    --disable-avfilter \
    --enable-pthreads \
    --enable-static \
    --enable-pic \
    --enable-runtime-cpudetect \
    --prefix=${FFMPEG_OUTPUT_PATH} \
    --disable-linux-perf \
    --enable-debug

make -j32
make install

SEARCH_PATH=${PLATFORM}/usr/lib 
SEARCH_PATH+=${FFMPEG_OUTPUT_PATH}/lib

${LD} \
    -rpath-link=${SEARCH_PATH} -L${PLATFORM}/usr/lib  \
    -shared -nostdlib -Bsymbolic --whole-archive --no-undefined ${EXTRA_LD_FLAGS} \
     ${FFMPEG_OUTPUT_LIBS} \
    -lc -lm -lz --dynamic-linker=/system/bin/linker \
    ${LIB_GCC} \
    -soname ${LIB_NAME} \
    -o ${FFMPEG_OUTPUT_PATH}/${LIB_NAME}
