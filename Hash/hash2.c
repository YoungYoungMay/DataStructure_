//
#include "hash2.h"

//1.初始化
size_t HashFuncDefault(KeyType key)//
{
    return key%HASHMAXSIZE;
}
void HashInit(HashTable* ht, HashFunc func)//初始化
{
    if(ht == NULL)
        return;
    ht->size = 0;
    ht->func = func;
    size_t i = 0;
    for(i=0; i<HASHMAXSIZE; ++i)
    {
        ht->data[i] = NULL;
    }
    return;
}

//2.销毁
void ElemDestroy(HashElem* node)//销毁结点
{
    free(node);
    return;
}

void HashDestroy(HashTable* ht)//销毁哈希表
{
    if(ht == NULL)
        return;
    ht->size = 0;
    ht->func = NULL;
    size_t i = 0;
    for(i=0; i<HASHMAXSIZE; ++i)
    {
        HashElem* cur = ht->data[i];
        while(cur != NULL)
        {
            HashElem* next = cur->next;
            ElemDestroy(cur);
            cur = next;
        }
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
        if(ht->data[i] == NULL)
            continue;
        printf("i = %d\n", i);
        HashElem* cur = ht->data[i];
        while(cur != NULL)
        {
            printf("[%d:%d] ", cur->key, cur->val);
            cur = cur->next;
        }
        printf("\n");
    }
    return;
}

//4.创建链表的一个结点
HashElem* ElemCreate(KeyType key, ValType val)
{
    HashElem* new_node = (HashElem*)malloc(sizeof(HashElem));
    new_node->key = key;
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}


//5.插入操作
HashElem* HashBucketFind(HashElem* head, KeyType key)//查找链表中是否存在当前要插入的元素
{
    HashElem* cur = head;
    while(cur != NULL)
    {
        if(key == cur->key)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

void HashInsert(HashTable* ht, KeyType key, ValType val)//插入
{
    if(ht == NULL)//非法输入
        return;
    //1.根据key计算插入位置offset
    size_t offset = ht->func(key);
    //2.在offset对应链表查找要插入的key
    HashElem* ret = HashBucketFind(ht->data[offset], key);
    //3.若key存在，插入失败
    if(ret != NULL)
        return;
    //4.若key不存在，可进行插入操作(头插)
    HashElem* new_node = ElemCreate(key, val);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
    //5.插入结束，++size
    ++ht->size;
    return;
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
    //2.在offset对应的链表中遍历查找当前要查找的元素
    HashElem* ret = HashBucketFind(ht->data[offset], key);
    if(ret == NULL)
        return 0;
    *val = ret->val;
    return 1;
}

//6.给定一个key,删除对应元素
int HashBucketFindEx(HashElem* head, KeyType to_find, HashElem** pre, HashElem** to_delete)//查找要删除元素及其父结点
{
    if(head == NULL || pre == NULL || to_delete == NULL)//非法输入
        return 0;
    HashElem* ret = head;
    HashElem* ex = NULL;
    for(; ret!=NULL; ret=ret->next)
    {
        if(ret->key == to_find)
            break;
    }
    if(ret == NULL)
        return 0;
    *pre = ex;
    *to_delete = ret;
    return 1;
}
void HashRemove(HashTable* ht, KeyType key)//删除操作
{
    if(ht == NULL)//非法操作
        return;
    if(ht->size == 0)//空哈希表
        return;
    //1.根据key计算offset
    size_t offset = ht->func(key);
    //2.在offset对应链表查找要删除元素
    HashElem* pre;
    HashElem* to_remove;
    int ret = HashBucketFindEx(ht->data[offset], key, &pre, &to_remove);
    //3.没找到要删除元素
    if(ret == 0)
        return;
    //4.要删除元素为链表首元素结点
    if(pre == NULL)
        ht->data[offset] = to_remove->next;
    //5.要删除元素为链表中一个结点
    else
        pre->next = to_remove->next;
    ElemDestroy(to_remove);
    //6.删除操作结束后--size
    --ht->size;
    return;
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
