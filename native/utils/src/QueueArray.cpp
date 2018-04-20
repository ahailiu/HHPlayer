/*
 * =====================================================================================
 *
 *       Filename:  list.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/14 15时20分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>

#include "QueueArray.h"

QueueArray::QueueArray(uint32_t cap)
:mCapSize(cap)
,mWIndex(0)
,mRIndex(0)
{
    mEntryArray = (Entry *)calloc(cap, sizeof(Entry));
}

QueueArray::~QueueArray()
{
    free(mEntryArray);
}

void* QueueArray::queuePop()
{
    if (!_queueSize())
        return NULL;

    int index = mRIndex % mCapSize;
    mRIndex ++;
    return mEntryArray[index].data;
}

uint32_t QueueArray::_queueSize()
{
    return mWIndex - mRIndex;
}

uint32_t QueueArray::_queueSpace()
{
    return mCapSize - ((uint32_t)(mWIndex - mRIndex));
}

uint32_t QueueArray::queueSize()
{
    return _queueSize();
}

uint32_t QueueArray::queueSpace()
{
    return _queueSpace();
}

int QueueArray::queuePush(void *data)
{
    if (!_queueSpace()) {
        return -1;
    }

    int index = mWIndex % mCapSize;
    mWIndex ++;
    mEntryArray[index].data = data;
    return 0;
}
