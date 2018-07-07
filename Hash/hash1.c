//闭散列实现哈希表
#include "hash1.h"

//1.初始化
size_t HashFuncDefault(KeyType key)//哈希函数
{
    return key%HASHMAXSIZE;
}
void HashInit(HashTable* ht, HashFunc func)//初始化
{
    ht->size = 0;
    ht->func = func;
    size_t i = 0;
    for(i=0; i<HASHMAXSIZE; ++i)
    {
        ht->data[i].stat = Empty;
    }
    return;
}

//2.销毁
void HashDestroy(HashTable* ht)//销毁
{
    ht->size = 0;
    ht->func = NULL;
    size_t i = 0;
    for(i=0; i<HASHMAXSIZE; ++i)
    {
        ht->data[i].stat = Empty;
    }
    return;
}

//3.打印函数，用于测试
void HashPrint(HashTable* ht, const char* msg)//打印函数
{
    printf("[%s]\n", msg);
    if(ht == NULL)
        return;
    size_t i = 0;
    for(; i<HASHMAXSIZE; ++i)
    {
        if(ht->data[i].stat == Valid)
        {
            printf("%d: [%d:%d]\n", i, ht->data[i].key, ht->data[i].val);
        }
    }
    return;
}

//4.插入操作
void HashInsert(HashTable* ht, KeyType key, ValType val)//插入
{
    if(ht == NULL)//非法输入
        return;
    //1.根据负载因子判断哈希表是否可以继续插入
    //我们约定负载因子为0.8
    if(ht->size >= 0.8*HASHMAXSIZE)
    {
        //当前哈希表已达到负载因子上限，插入失败
        return;
    }
    //2.根据key计算插入位置offset
    size_t offset = ht->func(key);
    while(1)
    {
        //3.若offset位置状态不为Valid，直接插入
        if(ht->data[offset].stat != Valid)
        {
            ht->data[offset].stat = Valid;
            ht->data[offset].key = key;
            ht->data[offset].val = val;
            //6.插入结束后++size
            ++ht->size;
            return;
        }
        //5.若发现哈希表中已有key相同的元素，我们约定为插入失败
        //也可以约定为继续向后查找插入或者替换已有的key键值对,这个由程序员自行决定
        else if(ht->data[offset].key == key && ht->data[offset].stat == Valid)
        {
            return;
        }
        //4.当前offset位置状态是Valid，线性向后查找，找到第一个不为Valid状态的位置插入
        else
        {
            ++offset;
            //若已探测到数组最后，就从头开始
            if(offset >= HASHMAXSIZE)
                offset = 0;
        }       
    }
}

//5.给定一个key，查找对应的val
int HashFind(HashTable* ht, KeyType key, ValType* val)//查找
{
    if(ht == NULL || val == NULL)//非法操作
        return 0;
    if(ht->size == 0)//哈希表为空
        return 0;
    //1.根据key计算offset
    size_t offset = ht->func(key);
    while(1)
    {
        //2.从offset开始线性向后查找
        //3.找到了相同的key，返回val，操作成功
        if(ht->data[offset].key == key && ht->data[offset].stat == Valid)
        {
            *val = ht->data[offset].val;
            return 1;
        }
        //5.查找过程直至遇到一个不为Valid状态的元素，说明查找失败
        else if(ht->data[offset].stat != Valid)
            return 0;
        //4.找不到相同的key,继续向后查找
        else
        {
            offset++;
            if(offset >= HASHMAXSIZE)
                offset = 0;
        }
    }
}

//6.给定一个key,删除对应元素
void HashRemove(HashTable* ht, KeyType key)//删除操作
{
    if(ht == NULL)//非法操作
        return;
    if(ht->size == 0)//空哈希表
        return;
    //1.根据key计算offset
    size_t offset = ht->func(key);
    //2.从offset线性向后查找要删除元素
    while(1)
    {
        //3.若当前key与要删除的key相同，删除元素即将其状态设置为Deleted
        if(ht->data[offset].key == key && ht->data[offset].stat == Valid)
        {
            ht->data[offset].stat = Deleted;
            --ht->size;
            return;
        }
        //4.若查找过程中遇到状态为Empty的元素，则查找失败
        else if(ht->data[offset].stat == Empty)
            return;
        //5.除3、4情况以外，++offset,线性探测下一个元素
        else
        {
            ++offset;
            offset = offset >= HASHMAXSIZE ? 0 : offset;
        }
    }
}
  

////////////////////////////////////////////////////////////
///////////////       以下为测试代码      /////////////////
///////////////////////////////////////////////////////////

void TestInit()
{
    SHOW_NAME;
    HashTable ht;
    HashInit(&ht, HashFuncDefault);
    printf("expected is 0, actual is %d\n", ht.size);
    printf("expected is %p, actual is %p\n", HashFuncDefault, ht.func);
}

void TestDestroy()
{
    SHOW_NAME;
    HashTable ht;
    HashInit(&ht, HashFuncDefault);
    HashDestroy(&ht);
    printf("expected is 0, actual is %d\n", ht.size);
    printf("expected is nil, actual is %p\n", ht.func);
}

void TestInsert()
{
    SHOW_NAME;
    HashTable ht;
    HashInit(&ht, HashFuncDefault);
    HashInsert(&ht, 1, 1);
    HashInsert(&ht, 2, 2);
    HashInsert(&ht, 1001, 3);
    HashInsert(&ht, 1002, 4);
    HashPrint(&ht, "插入4个元素");
}

void TestFind()
{
    SHOW_NAME;
    HashTable ht;
    HashInit(&ht, HashFuncDefault);
    HashInsert(&ht, 1, 1);
    HashInsert(&ht, 2, 2);
    HashInsert(&ht, 1001, 3);
    HashInsert(&ht, 1002, 4);
    HashPrint(&ht, "插入4个元素");
    int value;
    int ret = HashFind(&ht, 1001, &value);
    printf("expected is 3, actual is %d\n", value);
    ret = HashFind(&ht, 2001, &value);
    if(ret == 0)
        printf("查找失败\n");
}

void TestRemove()
{
    SHOW_NAME;
    HashTable ht;
    HashInit(&ht, HashFuncDefault);
    HashInsert(&ht, 1, 1);
    HashInsert(&ht, 2, 2);
    HashInsert(&ht, 1001, 3);
    HashInsert(&ht, 1002, 4);
    HashPrint(&ht, "插入4个元素");
    HashRemove(&ht, 1001);
    HashPrint(&ht, "删除key=1001的元素");
    HashRemove(&ht, 2001);
    HashPrint(&ht, "删除key=2001的元素");
}

int main()
{
    TestInit();
    TestDestroy();
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
