CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(demuxer)

MESSAGE(STATUS "Project:build Demuxer")
SET(CMAKE_BUILD_TYPE DEBUG)

SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

SET(SOURCE_FILES src/FFmpegDemuxer.cpp)

INCLUDE_DIRECTORIES(inc src)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

ADD_LIBRARY(demuxer ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(demuxer avcodec avformat swscale swresample avutil)

add_executable(demuxerDemo demo/main.cpp)
TARGET_LINK_LIBRARIES(
    demuxerDemo 
    demuxer 
    avcodec 
    avformat 
    swscale 
    swresample 
    avutil 
    bz2 
    z 
    iconv 
    pthread 
    "-framework VideoToolbox" 
    "-framework CoreServices" 
    "-framework CoreFoundation" 
    "-framework AudioUnit" 
    "-framework AudioToolbox" 
    "-framework CoreAudio"
    "-framework CoreVideo" 
    "-framework CoreMedia" 
    "-framework Security")
