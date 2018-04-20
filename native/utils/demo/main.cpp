/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/14 09时03分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "BlockQueue.h"

void *queuePush(void *arg)
{
    BlockQueue* dq = (BlockQueue*)arg;

    int a[10000] = {0};
    for (int i=0; i<sizeof(a)/sizeof(int); i++) {
        a[i] = 2*i;
    }

    int ret   = -1;
    int index = 0;
    while (1) {
        void *data = NULL;
        ret = dq->PopEmpty(&data, -1);
        if (ret == -2) {
            abort();
        } else if (ret == -1) {
            continue;
        }

        if (data == NULL) {
            data = calloc(1, sizeof(int));
        }

        memcpy(data, &a[index++], sizeof(int));
        if (index == 10000) {
            index = 0; 
        }
        
        while (1) {
            ret = dq->PushFill(data, -1);
            if (ret == -2) {
                abort();
            } else if (ret == 0) {
                break;
            }
        }
    }

    return NULL;
}

void *queuePop(void *arg)
{
    BlockQueue *dq = (BlockQueue*)arg;

    while (1) {
        void *data = NULL;
        int ret = dq->PopFill(&data, -1);
        if (ret == -2) {
            abort();
        } else if (ret == -1)
            continue;

        printf("%d ", (*(int *)data));

        while (1) {
            ret = dq->PushEmpty(data, -1);
            if (ret == -2) {
                abort();
            } else if (ret == 0) {
                break;
            }
        }
    }

    return NULL;
}

int main(void)
{
    BlockQueue  *dq = new BlockQueue(8);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, queuePush, dq);
    pthread_create(&t2, NULL, queuePop, dq);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    delete dq;
    return 0;
}
