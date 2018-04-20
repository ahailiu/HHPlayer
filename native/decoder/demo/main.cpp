/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/12 17时05分21秒
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

#include "SoftwareDecoder.h"

int main(void)
{
    DecoderBase *dec = new SoftwareDecoder();

    int ret = dec->init();
    ret = dec->start(VIDEO_HEVC);
    delete dec;
    while (1) {
        sleep(3);
    }

    return 0;
}
