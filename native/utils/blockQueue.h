/*
 * =====================================================================================
 *
 *       Filename:  blockQueue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/14 22时46分36秒
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

#include "list.h"

struct buffer {
    void *data;
    int  size;
};

class BlockQueue {
    private:
        List *productList;
        List *consumeList;

    public:
        BlockQueue();
        ~ BlockQueue();

        void *dequeueInputbuffer(int64_t ms);
        void *queueInputbuffer(int );
};

#endif
