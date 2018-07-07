//除整取余法：线性向后探测存放
#pragma once

#include <stdio.h>

#define SHOW_NAME printf("\n====================%s====================\n", __FUNCTION__);
#define HASHMAXSIZE 1000

typedef int KeyType;
typedef int ValType;
typedef size_t (*HashFunc)(KeyType key);//函数指针,用来调用哈希函数，控制元素存入位置

typedef enum
{
    Empty,//表示当前元素为空状态
    Valid,//表示当前元素为有效状态
    Deleted,//表示当前元素为被删除状态
}Stat;

typedef struct HashElem//表示哈希表中的一个元素，该元素包括键值对
{
    KeyType key;
    ValType val;
    Stat stat;//表示当前元素的状态
}HashElem;

typedef struct HashTable
{
    HashElem data[HASHMAXSIZE];
    HashFunc func;
    size_t size;//表示当前哈希表中有效元素的个数,哈希表不是线性结构，所以不能用[0,size)表示有效元素区间
}HashTable;
