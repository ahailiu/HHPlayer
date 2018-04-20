/*
 * =====================================================================================
 *
 *       Filename:  DecoderBase.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/11 20时47分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _DECODERBASE_H_
#define _DECODERBASE_H_

#include <stdio.h>

#include "IDecoder.h"

class DecoderBase : public IDecoder  {
    public:
        DecoderBase();
        virtual ~ DecoderBase();

        virtual int  init();
        virtual void sendPacket();
        virtual int  recvFrame();
        virtual void releaseFrame(int index);
        virtual int  start(enum CodecID id);
        virtual void stop();

    private:
        static void _noImplement() {
            printf("no Implement.\n");
            return ;
        }
};

#endif
