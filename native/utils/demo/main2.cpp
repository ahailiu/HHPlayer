/*
 * =====================================================================================
 *
 *       Filename:  main2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018/04/14 22时28分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

int main(void)
{
    List *ls = new List(8); 

    for (int i=0; i<10; i++) {
        struct _Entry *entry = (struct _Entry *)calloc(1, sizeof(struct _Entry));
        entry->index = i;

        int ret = ls->listPush(entry);
        if (ret < 0) {
            printf("push err, i=%d.\n", i);
            break;
        }
    }

    for (int i=0; i<13; i++) {
        struct _Entry *entry = ls->listPop();
        if (!entry) {
            printf("pop err, i=%d.\n", i);
            break;
        }

        printf("pop index:%d.\n", entry->index);
    }

    return 0;
}
