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

#include "doubleQueue.h"

void *queuePush(void *arg)
{
    DoubleQueue *dq = (DoubleQueue *)arg;

    int a[10000] = {0};
    for (int i=0; i<sizeof(a)/sizeof(int); i++) {
        a[i] = 2*i;
    }

    int ret   = -1;
    int index = 0;
    while (1) {
        ret = dq->doubleQueuePush((void *)&a[index], -1);
        if (ret < 0) {
            abort();
        } else if (ret == 0)
            continue;

        if (++ index == 10000)
            index = 0;
    }

    return NULL;
}

void *queuePop(void *arg)
{
    DoubleQueue *dq = (DoubleQueue *)arg;

    while (1) {
        void *data = NULL;
        int ret = dq->doubleQueuePop(&data, -1);
        if (ret < 0) {
            abort();
        } else if (ret == 0)
            continue;

        printf("%d ", (*(int *)data));
    }

    return NULL;
}

int main(void)
{
    DoubleQueue  *dq = new DoubleQueue(8);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, queuePush, dq);
    pthread_create(&t2, NULL, queuePop, dq);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    delete dq;
    return 0;
}
