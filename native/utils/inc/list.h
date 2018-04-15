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

#ifndef _LIST_H_
#define _LIST_H_

struct _Entry {
   struct _Entry *next; 
   struct _Entry *prev; 

   uint32_t  index;
   void *data;
};

class List {
    private:
        struct _Entry *mHead;
        struct _Entry *mTail;

        uint32_t mCapSize;
        uint32_t mSize;

    public:
        List(uint32_t maxSize);
        ~ List();
        
        struct _Entry* listPop();
        uint32_t listSize();
        uint32_t listSpace();

        int listPush(struct _Entry* entry);
};

#endif
