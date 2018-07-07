//链式队列
#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SHOW_NAME printf("\n=================%s==================\n",__FUNCTION__);

typedef char LinkNodeType;

typedef struct LinkNode
{
    LinkNodeType data;
    struct LinkNode* next;
}LinkNode;

typedef struct LinkQueue//入队(尾插)、出队(头删)
{
    LinkNode* head;
    LinkNode* tail;
}LinkQueue;
