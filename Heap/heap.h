//堆就是一个完全二叉树，分为大堆和小堆
#pragma once

#include <stdio.h>
#include <string.h>

#define SHOW_NAME printf("\n===========%s==============\n",__FUNCTION__);
#define MAXSIZE 1024

typedef char HeapType;
typedef int(*Compare) (HeapType a, HeapType b);//定义函数指针，用来控制当前堆是大堆还是小堆

typedef struct Head
{
    HeapType data[MAXSIZE];
    size_t size;//标志当前堆
    Compare cmp;//控制大小堆
}Heap;
