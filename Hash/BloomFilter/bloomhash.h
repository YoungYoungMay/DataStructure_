//实现布隆过滤器
//基于位图实现，表示字符串是否存在

#pragma once

#include <stdio.h>
#include <stdint.h>//uint64_t
#include <stdlib.h>
#include <string.h>

#define SHOW_NAME printf("\n========================%s=======================\n", __FUNCTION__);
#define BLOOMHASHCOUNT 2

typedef uint64_t BitmapType;//uint64_t类型可跨平台使用，占8字节
typedef uint64_t(* BloomHash)(const char*);//实现布隆过滤器的哈希函数

typedef struct Bitmap//位图
{
    BitmapType* data;
    uint64_t capacity;//能容纳的最多元素个数(单位是比特位)
}Bitmap;

typedef struct BloomFilter//布隆过滤器
{
    Bitmap bm;//用于表示状态的位图
    BloomHash bloom_hash[BLOOMHASHCOUNT];//存放多个哈希函数
}BloomFilter;
