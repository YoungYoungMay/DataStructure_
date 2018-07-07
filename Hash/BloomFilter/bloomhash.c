//哈希扩展—布隆过滤器
//用于标记字符串是否存在
#include "bloomhash.h"
#include "bitmap.c"
#include "func.c"

//1.初始化
void BloomFilterInit(BloomFilter* bf)
{
    if(bf == NULL)//非法操作
        return;
    BitmapInit(&bf->bm, 1000);//该位图最多标记1000个数据
    bf->bloom_hash[0] = SDBMHash;
    bf->bloom_hash[1] = BKDRHash;
    return;
}

//2.销毁
void BloomFilterDestroy(BloomFilter* bf)
{
    if(bf == NULL)
        return;
    bf->bloom_hash[0] = NULL;
    bf->bloom_hash[1] = NULL;
    BitmapDestroy(&bf->bm);
    return;
}

//3.插入
//用多个哈希函数计算出不同位置的下标，在位图中将对应下标全部置为1，用来表示某个字符串的存在
void BloomFilterInsert(BloomFilter* bf, const char* str)
{
    if(bf == NULL || str == NULL)
        return;
    size_t i = 0;
    for(i=0; i<BLOOMHASHCOUNT; ++i)
    {
        uint64_t hash = bf->bloom_hash[i](str) % (bf->bm.capacity);
        BitmapSet(&bf->bm, hash);
    }
    return;
}

//4.查找
//每个哈希函数对应的下标位置都表示存在，该字符串才存在
int BloomFilterFind(BloomFilter* bf, const char* str)
{
    if(bf == NULL || str == NULL)
        return 0;
    size_t i = 0;
    for(; i<BLOOMHASHCOUNT; ++i)
    {
        uint64_t hash = bf->bloom_hash[i](str) % (bf->bm.capacity);
        int ret = BitmapTest(&bf->bm, hash);
        if(ret == 0)
            return 0;
    }
    return 1;
}

int main()
{
    BloomFilter bf;

    BloomFilterInit(&bf);    
    printf("expcted is 1000, actual is %d\n", bf.bm.capacity);
    printf("expcted is %p, actual is %p\n", SDBMHash, bf.bloom_hash[0]);
    printf("expcted is %p, actual is %p\n", BKDRHash, bf.bloom_hash[1]);
    
    BloomFilterInsert(&bf, "this is youngmay");
    int ret = BloomFilterFind(&bf, "this is youngmay");
    printf("expcted is 1, actual is %d\n", ret);
    ret = BloomFilterFind(&bf, "Jony J YoungJack");
    printf("expcted is 0, actual is %d\n", ret);

    BloomFilterDestroy(&bf);
    printf("expcted is 0, actual is %d\n", bf.bm.capacity);
    printf("expcted is nil, actual is %p\n", bf.bloom_hash[0]);
    printf("expcted is nil, actual is %p\n", bf.bloom_hash[1]);
   
    return 0;
}
