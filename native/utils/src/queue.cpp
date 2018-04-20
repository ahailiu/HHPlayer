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

#include "Queue.h"

Queue::Queue(uint32_t size)
:mHead(NULL)
,mTail(NULL)
,mCapSize(size)
,mSize(0)
{

}

Queue::~Queue()
{
}

Entry* Queue::queuePop()
{
    if (!mSize)
        return NULL;

    Entry *entry = mHead;

    mHead = mHead->next;
    if (mHead != NULL)
        mHead->prev = NULL;
    else
        mTail = NULL;

    mSize --;
    return entry;
}

uint32_t Queue::queueSize()
{
    return mSize; 
}

uint32_t Queue::queueSpace()
{
    return mCapSize - mSize;
}

int Queue::queuePush(Entry *entry)
{
    if (mSize >= mCapSize) {
        return -1;
    }

    entry->next = entry->prev = NULL;
    if (!mHead) {
        mHead = mTail = entry;
        mSize ++;
        return 0;
    }

    entry->prev = mTail;
    mTail->next = entry;
    mTail = entry;
    mSize ++;
    return 0;
}
