//哈希扩展-位图的实现
//省空间;但是只能表示存在与否，不能具体存储
#pragma once

#include <stdio.h>
#include <stdint.h>//uint64_t
#include <stdlib.h>
#include <string.h>

#define SHOW_NAME printf("\n========================%s=======================\n", __FUNCTION__);

typedef uint64_t BitmapType;//uint64_t类型可跨平台使用，占8字节

typedef struct Bitmap
{
    BitmapType* data;
    uint64_t capacity;//能容纳的最多元素个数(单位是比特位)
}Bitmap;

