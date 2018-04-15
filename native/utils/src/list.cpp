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

#include "list.h"

List::List(uint32_t size)
:mHead(NULL)
,mTail(NULL)
,mCapSize(size)
,mSize(0)
{
}

List::~List()
{
}

struct _Entry* List::listPop()
{
    if (!mSize)
        return NULL;

    struct _Entry *entry = mHead;

    mTail->next = mHead->next;

    mHead = mHead->next;
    mHead->prev = mTail;

    if (mHead == mTail && 
            mHead == NULL)
        mTail = NULL;

    mSize --;
    return entry;
}

uint32_t List::listSize()
{
    return mSize; 
}

uint32_t List::listSpace()
{
    return mCapSize - mSize;
}

int List::listPush(struct _Entry *entry)
{
    if (mSize >= mCapSize) {
        return -1;
    }

    if (!mHead) {
        entry->next = entry->prev = NULL;

        mHead = mTail = entry;
        mSize ++;
        return 0;
    }

    entry->prev = mTail;
    entry->next = mHead;

    mHead->prev = entry;
    mTail->next = entry;

    mTail = entry;
    mSize ++;
    return 0;
}
