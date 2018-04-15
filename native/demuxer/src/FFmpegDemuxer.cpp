/*
 * =====================================================================================
 *
 *       Filename:  FFmpegDemuxuer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/05 18时10分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdarg.h>

#include "FFmpegDemuxer.h"
#include "libavutil/error.h"
#include "libavutil/avutil.h"


FFmpegDemuxer::FFmpegDemuxer()
:mUrl(NULL)
,mFFmpegLogEnable(false)
,mOpened(false)
,mAvFmtCtx(NULL)
,mCb(NULL)
{
    mStreamIndex[0] = -1;
    mStreamIndex[1] = -1;
    pthread_mutex_init(&mLock, NULL);
}

FFmpegDemuxer::~FFmpegDemuxer()
{
    pthread_mutex_destroy(&mLock);
}

static int _upperAbort(void *ctx)
{
    // TODO
    return 0;
}

static void _onLog(void *avc1, int level, const char *fmt, va_list vl)
{
    // TODO
}

int FFmpegDemuxer::open(const char *url, uint64_t timeStamp) 
{
    int ret = -1;
    AVDictionary *opts = NULL;

    if (NULL == url 
            || strlen(url) <= 0)
        return -1;

    pthread_mutex_lock(&mLock);

    av_register_all();
    avformat_network_init();

    mStartTimeStamp = timeStamp;
    if (NULL != mCb &&
            mFFmpegLogEnable) {
        av_log_set_callback(&_onLog);
        av_log_set_level(99);
    }

    mAvFmtCtx = avformat_alloc_context();
    if (NULL == mAvFmtCtx) {
        goto err;
    }

    mAvFmtCtx->interrupt_callback.callback = _upperAbort;
    mAvFmtCtx->interrupt_callback.opaque   = this;

    av_dict_set_int(&opts, "live_start_index", 10, 0);

    ret = avformat_open_input(&mAvFmtCtx, url, NULL, NULL);
    if (ret != 0) {
        goto err;
    }

    if (opts) {
        av_dict_free(&opts);
    }

    ret = avformat_find_stream_info(mAvFmtCtx, NULL);
    if (ret < 0) {
        goto err;
    }

    mStreamIndex[VIDEO_FRAME] = av_find_best_stream(mAvFmtCtx, AVMEDIA_TYPE_VIDEO, 
            mStreamIndex[VIDEO_FRAME], -1, NULL, 0);

    mStreamIndex[AUDIO_FRAME] = av_find_best_stream(mAvFmtCtx, AVMEDIA_TYPE_AUDIO, 
            mStreamIndex[AUDIO_FRAME], -1, NULL, 0);

    mStreamIndex[SUBTITLE_FRAME] = av_find_best_stream(mAvFmtCtx, AVMEDIA_TYPE_SUBTITLE, 
            mStreamIndex[SUBTITLE_FRAME], -1, NULL, 0);

    if (-1 == mStreamIndex[VIDEO_FRAME]
            && -1 == mStreamIndex[AUDIO_FRAME]) {
        printf("found not video and audio stream.\n");
        goto err;
    }

    av_dump_format(mAvFmtCtx, 0, url, 0);

    printf("Video Index:%d, Audio Index:%d.\n", mStreamIndex[VIDEO_FRAME], mStreamIndex[AUDIO_FRAME]);

    mOpened = true;
    pthread_mutex_unlock(&mLock);
    return 0;    

err:
    pthread_mutex_unlock(&mLock);
    return -1;
}

void FFmpegDemuxer::close()
{
    ;
}

void FFmpegDemuxer::registerDemuxerCb(IDemuxerCB *cb)
{
    pthread_mutex_lock(&mLock);
    mCb = cb; 
    pthread_mutex_unlock(&mLock);
}

void FFmpegDemuxer::unregisterDemuxerCb()
{
    pthread_mutex_lock(&mLock);
    mCb = NULL;
    pthread_mutex_unlock(&mLock);
}

int FFmpegDemuxer::seekWithPosition(uint64_t pos)
{
    return 0;
}

int FFmpegDemuxer::seekWithTimestamp(uint64_t timestamp)
{
    return 0;
}

uint64_t FFmpegDemuxer::getDuration()
{
    return 0;
}

int FFmpegDemuxer::getOneFrame(uint8_t* data, 
        int& size,
        int64_t& pts,
        int64_t& dts,
        int64_t& duration,
        int64_t& position,
        AV_MEDIA_TYPE& type,
        VIDEO_FRAME_TYPE& videoFtype)
{
    pthread_mutex_lock(&mLock);
    if (!mOpened) {
        pthread_mutex_unlock(&mLock);
        return -1;
    }

    AVPacket pkt;
    av_init_packet(&pkt);

    pkt.data = data;
    int ret = av_read_frame(mAvFmtCtx, &pkt);
    if (ret < 0) {
        goto err;
    }

    if (pkt.stream_index == mStreamIndex[VIDEO_FRAME]) {
        type = VIDEO_FRAME;
    } else if (pkt.stream_index == mStreamIndex[AUDIO_FRAME]) {
        type = AUDIO_FRAME;
    } else {
        type = UNKNOWN_MEDIA;
    }

    size     = pkt.size;
    pts      = pkt.pts;
    dts      = pkt.dts;
    duration = pkt.duration;
    position = pkt.pos;

    if (pkt.flags & AV_PKT_FLAG_KEY) {
        videoFtype = FRAME_I;
    } else {
        videoFtype = UNKNOWN_FRAME; 
    }
    
    av_packet_unref(&pkt);
    pthread_mutex_unlock(&mLock);
    return 0;

err:
    pthread_mutex_unlock(&mLock);
    return -1; 
}
