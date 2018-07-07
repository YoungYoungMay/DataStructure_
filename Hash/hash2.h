//哈希桶存放数据
#pragma once

#include <stdio.h>
#include <stdlib.h>

#define SHOW_NAME printf("\n====================%s====================\n", __FUNCTION__);
#define HASHMAXSIZE 1000

typedef int KeyType;
typedef int ValType;
typedef size_t (*HashFunc)(KeyType key);//函数指针，控制元素存入位置

typedef struct HashElem//相当于链表的结点
{
    KeyType key;
    ValType val;
    struct HashElem* next;//指向下一个元素
}HashElem;

typedef struct HashTable
{
    HashElem* data[HASHMAXSIZE];//哈希表不带头结点，所以用HashElem*型;若哈希表带头结点，用HashElem型，与链表原理一样
    HashFunc func;
    size_t size;//表示当前哈希表中有效元素的个数
}HashTable;
