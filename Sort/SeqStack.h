#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SHOW_NAME printf("===================%s================\n",__FUNCTION__);

typedef int64_t SeqStackType;

typedef struct SeqStack
{
    SeqStackType* data;
    size_t size;
    size_t capacity;//data指向内存的最大容量，即顺序表中数组的MAXSIZE的替代品
}SeqStack;

