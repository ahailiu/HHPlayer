/*
 * =====================================================================================
 *
 *       Filename:  doubleQueue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/14 08时08分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _DOUBLEQUEUE_H_
#define _DOUBLEQUEUE_H_

#include <pthread.h>

#include "queue.h"

class DoubleQueue {
    public:
        DoubleQueue(int size);
        ~ DoubleQueue();

        int doubleQueuePush(void *data, int64_t waitMs);
        int doubleQueuePop(void **data, int64_t waitMs);

    private:
        int cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, int64_t ms);
        void swapQueue();

    private:
        Queue *mQ1;
        Queue *mQ2;
        pthread_mutex_t mMutex1;
        pthread_cond_t  mCond;
        pthread_mutex_t mMutex2;
};

#endif
