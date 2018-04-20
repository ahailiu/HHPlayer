/*
 * =====================================================================================
 *
 *       Filename:  SoftwareDecoder.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/11 20时59分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _SOFTWAREDECODER_H_
#define _SOFTWAREDECODER_H_

#include "DecoderBase.h"
#include "libavcodec/avcodec.h"

typedef struct _HHFrame HHFrame;

class SoftwareDecoder : public DecoderBase {
    public:
        SoftwareDecoder(); 
        ~ SoftwareDecoder(); 

        int  init();
        int  start(enum CodecID id);
        int  sendPacket(int64_t waitMs);
        int  recvFrame(int64_t waitMs);
        void releaseFrame(int index);

        void stop();

    private:
        void _stop();

    private:
        enum CodecID   mCodecId;
        AVCodec        *mCodec;
        AVCodecContext *mCodecCtx;
        bool            mCodecOpened;

        BlockQueue     *mQueue;
};

#endif
