/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/14 15时20分18秒
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

typedef struct _Entry Entry;

struct _Entry {
   struct _Entry *next; 
   struct _Entry *prev; 

   void *data;
};

class Queue {
    private:
        Entry *mHead;
        Entry *mTail;

        Entry *mIdleQueue;

        uint32_t mCapSize;
        uint32_t mSize;

    public:
        Queue(uint32_t maxSize);
        ~ Queue();
        
        uint32_t queueSize();
        uint32_t queueSpace();

        void* queuePop();
        int   queuePush(void *data);
};

#endif
