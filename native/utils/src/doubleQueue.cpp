/*
 * =====================================================================================
 *
 *       Filename:  DoubleQueue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/12 23时40分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>

#include "doubleQueue.h"

DoubleQueue::DoubleQueue(int size)
{
    mQ1 = new Queue(size);
    mQ2 = new Queue(size);

    pthread_mutex_init(&mMutex1, NULL);
    pthread_mutex_init(&mMutex2, NULL);

    pthread_cond_init(&mCond, NULL);
}

DoubleQueue::~DoubleQueue()
{
    delete mQ1;
    delete mQ1;

    pthread_mutex_destroy(&mMutex1);
    pthread_mutex_destroy(&mMutex2);

    pthread_cond_destroy(&mCond);
}

int DoubleQueue::cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, int64_t ms)
{
    if (ms < 0) {
        return pthread_cond_wait(cond, mutex);
    }

    struct timeval tv;
    struct timespec ts;
    gettimeofday(&tv, NULL);
    ts.tv_sec = tv.tv_sec + 0;
    ts.tv_nsec = 0;

    return pthread_cond_timedwait(cond, mutex, &ts);
}

int DoubleQueue::doubleQueuePush(void *data, int64_t waitMs)
{
    int ret = -1;
    pthread_mutex_lock(&mMutex1);

    while (1)  {
        if (mQ1->queueSpace() <= 0) {
            ret = cond_timedwait(&mCond, &mMutex1, waitMs);
            if (ret < 0) {
                if (ret == ETIMEDOUT) {
                    ret = 0;
                    break;
                }

                break;
            }

            continue;
        }

        mQ1->queuePush(data);
        if (mQ1->queueSpace() == 1) {
            pthread_cond_signal(&mCond); 
        }

        ret = 1;
        break;
    }

    pthread_mutex_unlock(&mMutex1);
    return ret;
}

void DoubleQueue::swapQueue()
{
    Queue *tmp = mQ1;
    mQ1 = mQ2;
    mQ2 = tmp;
}

int DoubleQueue::doubleQueuePop(void **data, int64_t waitMs)
{
    int ret = -1;

    pthread_mutex_lock(&mMutex2);
    if (!!mQ2->queueSize()) {
        *data = mQ2->queuePop();
        ret = 1;
    } else {
        pthread_mutex_lock(&mMutex1);
        while (1) {
            if (!mQ1->queueSize()) {
                ret = cond_timedwait(&mCond, &mMutex1, waitMs);
                if (ret < 0) {
                    if (ret == ETIMEDOUT) {
                        ret = 0;
                        break;
                    }

                    //TODO abort;
                    break;
                }

                continue;
            }

            int spaceSize = mQ1->queueSpace();

            swapQueue();
            mQ1->queueReset();

            if (spaceSize == 0)
                pthread_cond_signal(&mCond);

            *data = mQ2->queuePop();
            ret = 1;
            break;
        }
        pthread_mutex_unlock(&mMutex1);
    }

    pthread_mutex_unlock(&mMutex2);
    return ret;
}
