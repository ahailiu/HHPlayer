/*
 * =====================================================================================
 *
 *       Filename:  FFmpegDemuxuer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/05 17时30分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _FFMPEGDEMUXER_H_
#define _FFMPEGDEMUXER_H_

#include <pthread.h>

extern "C" {
#include "libavutil/log.h"
#include "libavformat/avformat.h"
}

class IDemuxerCB {
    public:
        virtual void onFrame(const char *buf, uint32_t len, uint64_t decodeTs, uint64_t presentTs) = 0; 
        virtual void onLog(void*, int, const char*, va_list);
};

enum AV_MEDIA_TYPE {
    VIDEO_FRAME = 0,
    AUDIO_FRAME,
    SUBTITLE_FRAME,
    UNKNOWN_MEDIA,
};

enum VIDEO_FRAME_TYPE {
    UNKNOWN_FRAME = 0,
    FRAME_I,
    FRAME_P,
    FRAME_B,
};


class FFmpegDemuxer {
    public:
        FFmpegDemuxer();
        ~FFmpegDemuxer();

        int  open(const char *url, uint64_t ts = 0);
        void close();

        void registerDemuxerCb(IDemuxerCB *cb); 
        void unregisterDemuxerCb(); 

        int seekWithPosition(uint64_t pos);
        int seekWithTimestamp(uint64_t timestamp);
        uint64_t getDuration();
        int getOneFrame(uint8_t* data, 
                int& size,
                int64_t& pts,
                int64_t& dts,
                int64_t& duration,
                int64_t& position,
                AV_MEDIA_TYPE& type,
                VIDEO_FRAME_TYPE& videoFtype);

    private:
        char *mUrl;
        bool mFFmpegLogEnable;
        bool mOpened;
        int  mStreamIndex[3];

        uint64_t mStartTimeStamp;

        AVFormatContext *mAvFmtCtx;

        pthread_mutex_t mLock;
        IDemuxerCB *mCb;

        
};

#endif
