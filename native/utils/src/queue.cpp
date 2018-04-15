/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/12 23时13分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "queue.h"

Queue::Queue(int size)
:mQueueSize(size)
,mWIndex(0)
,mRIndex(0)
{
    mEntry = (Entry *)calloc(1, sizeof(Entry) * size);
    if (!mEntry) {
        //TODO
        //abort();
    }

    for (int i=0; i<size; i++) {
       mEntry[i].index = i;
    }
}

Queue::~Queue()
{
    free(mEntry);
}

int Queue::queueSpace()
{
    return (mQueueSize - mWIndex);
}

int Queue::queuePush(void *data)
{
    if (mWIndex >= mQueueSize) {
        // never
        return -1;
    }

    mEntry[mWIndex ++].data = data;
    return 0;
}

int Queue::queueSize()
{
    return (mWIndex - mRIndex);
}

void Queue::queueReset()
{
    mWIndex = mRIndex = 0;
}

void* Queue::queuePop()
{
    if (mRIndex >= mQueueSize) {
        // never
        return NULL;
    }

    void *data = mEntry[mRIndex].data;    
    mEntry[mRIndex ++].data = NULL;
    return data;

}
