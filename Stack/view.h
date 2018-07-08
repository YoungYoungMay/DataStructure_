#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SHOW_NAME printf("\n===============%s===============\n",__FUNCTION__);
#define MAX_SIZE 100

typedef char StackType;

typedef struct SeqStack//顺序栈
{
    StackType* data;
    size_t size;//当前的元素个数
    size_t capacity;//当前的MAXSIZE
}SeqStack;

typedef struct SeqQueue//顺序队列
{
    StackType data[MAX_SIZE];
    size_t size;
    size_t head;
    size_t tail;
}SeqQueue;

typedef struct MinStack//栈顶元素保证为最小值
{
    SeqStack stack;
}MinStack;

typedef struct QueueBy2Stack//两个栈实现一个队列
{
    SeqStack input;//实现入队
    SeqStack output;//实现出队
}QueueBy2Stack;

typedef struct StackBy2Queue//两个队列实现一个栈
{   
    SeqQueue queue1;
    SeqQueue queue2;
}StackBy2Queue;

typedef struct SharedStack//一个数组实现两个栈
{
    StackType data[MAX_SIZE];
    size_t top1;
    size_t top2;
}SharedStack;
