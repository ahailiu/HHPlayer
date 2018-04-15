/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/06 10时46分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#include "FFmpegDemuxer.h"

int main(int argc, char *argv[])
{
    const char *url = "http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8";
    if (argc == 2) {
        url = argv[1];
    }

    struct timeval tv, tv2;
    gettimeofday(&tv, NULL);

    FFmpegDemuxer *demuxer = new FFmpegDemuxer();

    if (demuxer->open(url) < 0) {
        abort();
        return -1;
    }

    gettimeofday(&tv2, NULL);

    long time = (tv2.tv_sec * 1000 + tv2.tv_usec/1000) - (tv.tv_sec * 1000 + tv.tv_usec/1000);
    printf("demuxer open succ, open cost time:%ld.\n", time);

    uint8_t *data = (uint8_t *)malloc(1024*1024);
    int size = 0;
    int64_t pts = 0;
    int64_t dts = 0;
    int64_t duration = 0;
    int64_t position = 0;

    AV_MEDIA_TYPE    mediaType = UNKNOWN_MEDIA;
    VIDEO_FRAME_TYPE videoType = UNKNOWN_FRAME;

    while (1) {
        int ret = demuxer->getOneFrame(data, 
                size,
                pts,
                dts,
                duration,
                position,
                mediaType,
                videoType);
        if (ret < 0)
            break;

        printf("get one frame, ret:%d, size:%d, pts:%ld, dts:%ld, duration:%ld, postion:%ld, type:%d, videoFtype:%d.\n", 
                ret, size, pts, dts, duration, position, mediaType, videoType);
    }


    free(data);
    while (1) {
        sleep(3);
    }

    demuxer->close();
    delete demuxer;
    return 0;
}
