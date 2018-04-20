/*
 * =====================================================================================
 *
 *       Filename:  DecoderBase.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/12 16时45分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "DecoderBase.h"

DecoderBase::DecoderBase()
{
    printf("DecoderBase::DecoderBase().\n");
}

DecoderBase::~DecoderBase()
{
    printf("DecoderBase::~DecoderBase().\n");
}

int DecoderBase::init()
{
    DecoderBase::_noImplement();
    return 0;
}

void DecoderBase::sendPacket()
{
    DecoderBase::_noImplement();
}

int DecoderBase::recvFrame()
{
    DecoderBase::_noImplement();
    return 0;
}

void DecoderBase::releaseFrame(int index)
{
    DecoderBase::_noImplement();
}

int DecoderBase::start(enum CodecID id)
{
    DecoderBase::_noImplement();
    return 0;
}

void DecoderBase::stop()
{
    DecoderBase::_noImplement();
}
