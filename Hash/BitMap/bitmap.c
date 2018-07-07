//哈希扩展—位图
#include "bitmap.h"

//1.初始化
void BitmapInit(Bitmap* bm, uint64_t capacity)//初始化
{
    if(bm == NULL)//非法输入
        return;
    bm->capacity = capacity;//表示位图能保存的最大数(bit数)
    uint64_t size = bm->capacity/(sizeof(bm->data[0])*8) + 1;//要申请的元素个数
    bm->data = (BitmapType*)malloc(sizeof(BitmapType)*size);
    memset(bm->data, 0, sizeof(BitmapType)*size);//初始化数据
    return;
}

//2.销毁
void BitmapDestroy(Bitmap* bm)
{
    if(bm == NULL)
        return;
    bm->capacity = 0;
    free(bm->data);
    return;
}

//3.测试函数—输出某一位是0还是
void GetOffset(uint64_t index, uint64_t* n, uint64_t* offset)//确定要测试的是在第几个元素的第几个比特位
{//n输出元素下标，offset输出比特位置
    *n = index / (sizeof(BitmapType)*8);
    *offset = index % (sizeof(BitmapType)*8);
    return;
}

int BitmapTest(Bitmap* bm, uint64_t index)//该bit位上是1返回1，是0返回0
{//index表示是数组中的第多少位bit
    if(bm == NULL || index >= bm->capacity)//非法输入
        return 0;
    uint64_t n,offset;
    GetOffset(index, &n, &offset);
    
    uint64_t ret = bm->data[n] & (0x1ul << offset);//这里使用0x1ul是为了防止因为类型问题导致移位得到的数据出错
    return ret > 0 ? 1 : 0;
}

//4.设置某个比特位为1
void BitmapSet(Bitmap* bm, uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)//非法输入
        return;
    uint64_t n,offset;
    GetOffset(index, &n, &offset);
    bm->data[n] |= (0x1ul << offset);//或1 一定为1
    return;
}

//5.设置某个比特位为0
void BitmapUnSet(Bitmap* bm, uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)//非法输入
        return;
    uint64_t n,offset;
    GetOffset(index, &n, &offset);
    bm->data[n] &= ~(0x1ul << offset);//与0 一定为0
    return;
}

//6.设置所有比特位为1
void BitmapFill(Bitmap* bm)
{
    if(bm == NULL)//非法输入
        return;
    uint64_t size = bm->capacity/(sizeof(bm->data[0])*8) + 1;
    memset(bm->data, 0xff, sizeof(BitmapType)*size);
    return;
}

//7.设置所有比特位为0
void BitmapEmpty(Bitmap* bm)
{
    if(bm == NULL)//非法输入
        return;
    uint64_t size = bm->capacity/(sizeof(bm->data[0])*8) + 1;
    memset(bm->data, 0x0, sizeof(BitmapType)*size);
    return;
}


/////////////////////////////////////////////////////////////////
////////////////        以下为测试代码      ////////////////////
////////////////////////////////////////////////////////////////
void Test()
{
    SHOW_NAME;
    Bitmap bm;
    BitmapInit(&bm, 100);
    printf("capacity: expected is 100, actual is %d\n", bm.capacity);
    printf("expected is 0, actual is %lu\n", bm.data[0]);//uint64_t类型用%lu输出
    BitmapSet(&bm, 4);
    printf("expected is 1, actual is %d\n", BitmapTest(&bm, 4));
    BitmapUnSet(&bm, 7);
    printf("expected is 0, actual is %d\n", BitmapTest(&bm, 7));
    BitmapFill(&bm);
    printf("expected is 1, actual is %d\n", BitmapTest(&bm, 31));
    BitmapEmpty(&bm);
    printf("expected is 0, actual is %d\n", BitmapTest(&bm, 27));
    BitmapDestroy(&bm);
    printf("expected is 0, actual is %d\n", bm.capacity);
}

int main()
{
    Test();
    return 0;
}
