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

#ifndef _QUEUEARRAY_H_
#define _QUEUEARRAY_H_

typedef struct _Entry Entry;

struct _Entry {
   void *data;
};

class QueueArray {
    private:
        Entry *mEntryArray;
        uint32_t mCapSize;
        uint64_t mWIndex;
        uint64_t mRIndex;

    private:
        uint32_t _queueSize();
        uint32_t _queueSpace();

    public:
        QueueArray(uint32_t cap);
        ~ QueueArray();
        
        uint32_t queueSize();
        uint32_t queueSpace();

        void* queuePop();
        int   queuePush(void *data);
};

#endif
