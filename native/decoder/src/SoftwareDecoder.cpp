/*
 * =====================================================================================
 *
 *       Filename:  SoftwareDecoder.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/12 16时07分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "SoftwareDecoder.h"

SoftwareDecoder::SoftwareDecoder()
:mCodecOpened(false)
{
}

SoftwareDecoder::~SoftwareDecoder()
{

}

int SoftwareDecoder::init()
{
    avcodec_register_all();
    return 0;
}

void SoftwareDecoder::_stop()
{
    if (mCodecOpened) {
        avcodec_close(mCodecCtx);
        avcodec_free_context(&mCodecCtx);
        mCodecCtx = NULL;

        mCodecOpened = false;
    }
}

int SoftwareDecoder::start(enum CodecID cid, int bufFrames)
{
    mQueue = new BlockQueue(bufFrames);
    if (!mQueue)
        return -1;

    enum AVCodecID id;

    switch(cid) {
        case VIDEO_AVC:
            id = AV_CODEC_ID_H264;
            break;
        case VIDEO_HEVC:
            id = AV_CODEC_ID_HEVC;
            break;
        case AUDIO_AAC:
            id = AV_CODEC_ID_AAC;
            break;
        default:
            return -1;
            break;
    }

    mCodec = avcodec_find_decoder(id);
    if (!mCodec) {
        return -1;
    }

    mCodecCtx = avcodec_alloc_context3(mCodec);
    if (!mCodecCtx) {
        return -1;
    }

    if (avcodec_open2(mCodecCtx, mCodec, NULL) < 0) {
        goto err;
    }

    mCodecOpened = true;
    return 0;

err:
    _stop();
    return -1;
}

/*  
 * -1 EAGAIN
 * -2 NO INIT.
 * -3 OTHER ERROR.
 *
 *  */

int SoftwareDecoder::sendPacket(const uint8_t *buf,
        size_t nbytes, uint64_t pts, uint64_t dts,
        bool keyFrame)
{
    if (!mCodecOpened) {
        return -2;
    }

    AVPacket pkt;
    av_packet_init(&pkt);

    pkt.pts = pts;
    pkt.dts = dts;
    pkt.data = buf;
    pkt.size = nbytes;

    if (keyframe)
        pkt.flags |= AV_PKT_FLAG_KEY; 

    int ret = avcodec_send_packet(avctx, &pkt);
    if (ret < 0) {
        if (ret == AVERROR(EAGAIN))
            return -1;
        else
            return -3;
    }

    return 0;
}

#define DEQUEUE_VIDEO_INTERVAL 10

int SoftwareDecoder::recvFrame(int64_t timeoutMs)
{
    if (!mCodecOpened) {
        return -2;
    }

    AVFrame *frame = NULL;
    int ret = mQueue->PopEmpty((void **)&frame, timeoutMs);
    if (ret < 0) {
        if (ret == -1)
            ret = -1;
        else 
            ret = -3;

        goto err;
    }

    if (frame == NULL) {
        frame = av_frame_alloc():
    }

    if (timeoutMs < 0) {
        timeoutMs = LONG_MAX;
    }

    ret = 0;
    while (timeoutMs < 0) {
        ret = avcodec_receive_frame(avctx, frame);
        if (ret < 0) {
            if (ret == AVERROR(EAGAIN)) {
                timeoutMs -= DEQUEUE_VIDEO_INTERVAL;
                if (timeoutMs >= 0)
                    usleep(DEQUEUE_VIDEO_INTERVAL*1000);
            } else {
                // TODO frame 处理.
                ret = -3;
                goto err;             
            }
        } else if (ret == 0)
            break;
    }

    if (ret == AVERROR(EAGAIN)) {
        ret = mQueue->PushEmpty((void *)frame, timeoutMs);
        if (ret < 0) { 
            // never;
            ret = -3;
        } else {
            ret = -1; 
        }

        goto err;
    }

    // 这里必须是可push.
    ret = mQueue->PushFill((void *)frame, timeoutMs);
    if (ret < 0) {
        // never
        ret = -3;
    }

err:
    return ret;
}

int SoftwareDecoder::releaseFrame(int timeoutMs)
{
    if (!mCodecOpened) {
        return -2;
    }    

    AVFrame *frame = NULL;
    int ret = mQueue->popFill((void **)&frame, timeoutMs);
    if (ret < 0) {
        if (ret != -1) {
            ret = -3;
        }

        goto err;
    }

    if (frame->pts) {
        
    }

err:
    return ret;
}

void SoftwareDecoder::stop()
{
    _stop(); 
}
