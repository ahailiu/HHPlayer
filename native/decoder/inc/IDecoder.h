/*
 * =====================================================================================
 *
 *       Filename:  IDecode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/09 21时48分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _IDECODE_H_
#define _IDECODE_H_

enum CodecID {
    VIDEO_AVC  = 0,
    VIDEO_HEVC,
    AUDIO_AAC,
};

class IDecoder {
    public:
        virtual int init() = 0;
        virtual void sendPacket() = 0;
        virtual int  recvFrame() = 0;

        virtual void releaseFrame(int index) = 0;
        virtual int  start(enum CodecID id);
        virtual void stop();
};

#endif
