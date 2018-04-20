/*
 * =====================================================================================
 *
 *       Filename:  BlockQueue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/19 19时33分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _BLOCKQUEUE_H_
#define _BLOCKQUEUE_H_

#include <pthread.h>

#include "QueueArray.h"

class BlockQueue {
    private:
       QueueArray *mFill;
       QueueArray *mEmpty;
       Entry *mEntry;

       pthread_mutex_t mFillQueueMutex;
       pthread_mutex_t mEmptyQueueMutex;
       pthread_cond_t  mFillQueueCond;
       pthread_cond_t  mEmptyQueueCond;

    private:
       int _cond_wait(pthread_mutex_t *mutex, pthread_cond_t *cond, int64_t ms);

    public:
        BlockQueue(int size);
        ~ BlockQueue();
    
        int  PushEmpty(void *data, int64_t ms);
        int  PushFill(void *data,  int64_t ms);
        int  PopEmpty(void **data, int64_t ms);
        int  PopFill(void **data,  int64_t ms);
};

#endif
