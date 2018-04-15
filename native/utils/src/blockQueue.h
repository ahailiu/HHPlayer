/*
 * =====================================================================================
 *
 *       Filename:  blockQueue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/14 23时27分36秒
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

#include "queue.h"

struct _Buffer_t {
    uint32_t size;
    uint8_t  *data;
};

class BlockQueue {
    private:
        Queue *mEmpty;
        Queue *mFill;
        struct _Buffer_t *mBuffer;
        uint32_t mCapSize;

    public:
        BlockQueue(uint32_t cap);
        ~ BlockQueue();

        uint32_t dequeueInputBuffer(int64_t ms);
        struct _Buffer_t *getInputBuffer(uint32_t index);
        void queueInputBuffer(uint32_t index);

        uint32_t dequeueOutputBuffer(int64_t ms);
        void releaseOutputBuffer(uint32_t index);
};

#endif
