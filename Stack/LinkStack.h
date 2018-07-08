#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SHOW_NAME printf("\n===================%s================\n",__FUNCTION__);

typedef char LinkStackType;

//typedef struct LinkNode
//{
//    LinkStackType data;
//    LinkNode* next;
//}LinkNode;

typedef struct LinkStack//带头结点的链栈
{
    LinkStackType data;
    struct LinkStack* next; 
}LinkStack;

