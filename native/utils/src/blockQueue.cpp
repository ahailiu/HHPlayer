/*
 * =====================================================================================
 *
 *       Filename:  BlockQueue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/17 23时29分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#include "BlockQueue.h"

BlockQueue::BlockQueue(int cap)
{
    mFill  = new QueueArray(cap);
    mEmpty = new QueueArray(cap);

    mEntry = (Entry *)calloc(cap, sizeof(Entry));
    for (int i=0; i<cap; i++) {
        mEmpty->queuePush((void *)&mEntry[i]);
    }

    pthread_mutex_init(&mFillQueueMutex,  NULL);
    pthread_mutex_init(&mEmptyQueueMutex, NULL);
    pthread_cond_init(&mFillQueueCond,    NULL);
    pthread_cond_init(&mEmptyQueueCond,   NULL);
}

BlockQueue::~BlockQueue()
{
    delete mEmpty;
    delete mFill;
    free(mEntry);
}

int BlockQueue::PushEmpty(void *data, int64_t ms)
{
    int ret = 0;
    pthread_mutex_lock(&mEmptyQueueMutex);
    while (1) {
        int size = mEmpty->queueSpace();
        if (size > 0) {
            break;
        }

        int ret = _cond_wait(&mEmptyQueueMutex, &mEmptyQueueCond, ms);
        if (ret < 0) {
            if (ret == ETIMEDOUT) {
                ret = -1;
            } else {
                ret = -2;
            }

            break;
        }
    }

    if (ret == 0) {
        mEmpty->queuePush(data);
        pthread_cond_signal(&mEmptyQueueCond);
    }

    pthread_mutex_unlock(&mEmptyQueueMutex);
    return ret;
}

int BlockQueue::PushFill(void *data, int64_t ms)
{
    int ret = 0;
    pthread_mutex_lock(&mFillQueueMutex);
    while (1) {
        int size = mFill->queueSpace();
        if (size > 0) {
            break;
        }

        int ret = _cond_wait(&mFillQueueMutex, &mFillQueueCond, ms);
        if (ret < 0) {
            if (ret == ETIMEDOUT) {
                ret = -1;
            } else {
                ret = -2;
            }

            break;
        }
    }

    if (ret == 0) {
        mFill->queuePush(data);
        pthread_cond_signal(&mFillQueueCond);
    }

    pthread_mutex_unlock(&mFillQueueMutex);
    return ret;
}

int BlockQueue::_cond_wait(pthread_mutex_t *mutex, pthread_cond_t *cond, int64_t ms)
{
    struct timeval tv;
    struct timespec ts;
    gettimeofday(&tv, NULL);

    if (ms >= 0) {
        ts.tv_sec  = tv.tv_sec;
        ts.tv_nsec = tv.tv_usec + ms * 1000;
        return pthread_cond_timedwait(cond, mutex, &ts);
    } else {
        return pthread_cond_wait(cond, mutex);
    }
}

int BlockQueue::PopEmpty(void **data, int64_t ms)
{
    int ret = 0;
    pthread_mutex_lock(&mEmptyQueueMutex);
    while (1) {
        int size = mEmpty->queueSize();
        if (size > 0) {
            break;
        }
        
        int ret = _cond_wait(&mEmptyQueueMutex, &mEmptyQueueCond, ms);
        if (ret < 0) {
            if (ret == ETIMEDOUT) {
                ret = -1;
            } else {
                ret = -2;
            }
               
            break;
        }
    }

    if (ret == 0) {
        *data = mEmpty->queuePop();
        pthread_cond_signal(&mEmptyQueueCond);
    }

    pthread_mutex_unlock(&mEmptyQueueMutex);
    return ret;
}

int BlockQueue::PopFill(void **data, int64_t ms)
{
    int ret = 0;
    pthread_mutex_lock(&mFillQueueMutex);
    while (1) {
        int size = mFill->queueSize();
        if (size > 0) {
            break;
        }

        int ret = _cond_wait(&mFillQueueMutex, &mFillQueueCond, ms);
        if (ret < 0) {
            if (ret == ETIMEDOUT) {
                ret = -1;
            } else {
                ret = -2;
            }
               
            break;
        }
    }

    if (ret == 0) {
        *data = mFill->queuePop();
        pthread_cond_signal(&mFillQueueCond);
    }

    pthread_mutex_unlock(&mFillQueueMutex);
    return ret;
}
