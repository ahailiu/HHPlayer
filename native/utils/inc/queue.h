/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/13 19时46分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct _entry {
    int index;
    void *data;
} Entry;

class Queue {
    private:
        int    mQueueSize;
        Entry  *mEntry;
        int    mWIndex;
        int    mRIndex;
    
    public:
        Queue(int size);
        ~ Queue();
        int   queueSpace();
        int   queuePush(void *data);
        int   queueSize();
        void  queueReset();
        void* queuePop();
};

#endif
