/*
 * =====================================================================================
 *
 *       Filename:  blockQueue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/14 23时46分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "blockQueue.h"

BlockQueue::BlockQueue(uint32_t cap)
:mCapSize(cap)
{
    mEmpty = new Queue(cap); 
    mFill  = new Queue(cap); 

    mBuffer = (struct _Buffer_t *)calloc(cap, sizeof(struct _Buffer_t));

    for (int i=0; i<cap; i++) {
        mEmpty->queuePush(mBuffer[i]);
    }
}
