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

int SoftwareDecoder::start(enum CodecID cid)
{
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

int SoftwareDecoder::recvFrame()
{
    if (!mCodecOpened) {
        return -2;
    }

    AVFrame frame;
    int ret = avcodec_receive_frame(avctx, AVFrame *frame);
    return 0;
}

void SoftwareDecoder::releaseFrame(int index)
{
    return ;
}

void SoftwareDecoder::stop()
{
    _stop(); 
}
