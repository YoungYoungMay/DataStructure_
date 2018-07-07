#include "DLinklist.h"

DLinkNode* CreateDLinkNode(DLinkType value)//创建一个新的结点
{
    DLinkNode* new_node = (DLinkNode*)malloc(sizeof(DLinkNode));
    new_node->data = value;
    new_node->prev = new_node;//要实现带环，这里将结点的两个指针都指向自己
    new_node->next = new_node;
    return new_node;
}

void DLinklistInit(DLinkNode** phead)//初始化
{
    if(phead == NULL)//非法操作
        return;
    *phead = CreateDLinkNode(0);//头结点中的数据无任何意义，任意置
}

void DLinklistPushBack(DLinkNode*head,DLinkType value)//尾插结点(修改四个指针)
{
    if(head == NULL)//非法操作
        return;
    //不用考虑链表为空的情况，它可以合并到以下代码
    DLinkNode* new_node = CreateDLinkNode(value);
    DLinkNode* tail = head->prev;
    head->prev = new_node;//head与new_node
    new_node->next = head;
    tail->next = new_node;//tail与new_node
    new_node->prev = tail;
    return;
}

void DestroyNode(DLinkNode* node)//销毁结点
{
    free(node);
}

void DLinklistPopBack(DLinkNode* head)//尾删(修改两个指针)
{
    if(head == NULL)//非法操作
        return;
    if(head->prev == head)//空链表
    //if(head->next == head)
        return;
    DLinkNode* to_delete = head->prev;
    DLinkNode* tail = to_delete->prev;
    head->prev = tail;
    tail->next = head;
    DestroyNode(to_delete);
    return;
}

void DLinklistPushFront(DLinkNode* head,DLinkType value)//头插(修改四个指针)
{
    if(head == NULL)//非法操作
        return;
    DLinkNode* new_node = CreateDLinkNode(value);
    DLinkNode* next_node = head->next;
    head->next = new_node;//head与new_node
    new_node->prev = head;
    new_node->next = next_node;//next_node与new_node
    next_node->prev = new_node;
    return;
}

void DLinklistPopFront(DLinkNode* head)//头删(修改两个指针)
{
    if(head == NULL)//非法操作
        return;
    if(head->prev == head)//空链表
        return;
    DLinkNode* to_delete = head->next;
    DLinkNode* next_node = to_delete->next;
    head->next = next_node;
    next_node->prev = head;
    DestroyNode(to_delete);
    return;
}

void DLinklistPrint(DLinkNode* head,const char* msg)//打印链表
{
    printf("[%s]\n",msg);
    DLinkNode* cur = head->next;
    for(; cur!=head; cur=cur->next)//正向打印，判断所有的next指针指向是否正确
    {
        printf("[%c|%p] ",cur->data,cur);
    }
    printf("\n");
    for(cur=head->prev; cur!=head; cur=cur->prev)//逆向打印，判断所有的prev指向是否正确
    {
        printf("[%c|%p] ",cur->data,cur);
    }
    printf("\n");
}

DLinkNode* DLinklistFind(DLinkNode* head,DLinkType value)//查找值为value的结点
{
    if(head == NULL)//非法操作
        return NULL;
    DLinkNode* cur = head->next;
    while(cur != head)
    {
        if(cur->data == value)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

void DLinklistInsertBefore(DLinkNode* head,DLinkNode* pos,DLinkType value)//向pos位置前插入元素
{
    if(head == NULL || pos == NULL)//非法操作 
        return;
    DLinkNode* new_node = CreateDLinkNode(value);
    DLinkNode* pre = pos->prev;
    pre->next = new_node;
    new_node->prev = pre;
    new_node->next = pos;
    pos->prev = new_node;
    return;
}

void DLinklistInsertAfter(DLinkNode* head,DLinkNode* pos,DLinkType value)//向pos位置后插入元素
{
    if(head == NULL || pos == NULL)//非法操作 
        return;
    DLinkNode* new_node = CreateDLinkNode(value);
    DLinkNode* next_node = pos->next;
    pos->next = new_node;
    new_node->prev = pos;
    new_node->next = next_node;
    next_node->prev = new_node;
    return;
}

void DLinklistErase(DLinkNode* head,DLinkNode* pos)//删除pos位置的结点
{
    if(head == NULL || pos == NULL)//非法操作
        return;
    if(head == pos)//非法操作,head指向的元素不能释放，除非在销毁整个链表
        return;
    DLinkNode* pre = pos->prev;
    DLinkNode* nex = pos->next;
    pre->next = nex;
    nex->prev = pre;
    DestroyNode(pos);
    return;
}

void DLinklistRemove(DLinkNode* head,DLinkType value)//删除值为value的结点
{
    if(head == NULL)
        return;
    DLinkNode* cur = head->next;
    while(cur != head)
    {
        if(cur->data == value)
        {
            DLinkNode* pre = cur->prev;
            DLinkNode* nex = cur->next;
            pre->next = nex;
            nex->prev = pre;
            DestroyNode(cur);
            return;
        }
        cur = cur->next;
    }
    return;
   // DLinkNode* to_delete = DLinklistFind(head,value);
   // if(to_delete == NULL)
   //     return;
   // DLinklistErase(head,to_delete);
   // return;
}

void DLinklistRemoveAll(DLinkNode* head,DLinkType value)//删除值为value的所有结点
{
    if(head == NULL)
        return;
    DLinkNode* cur = head->next;
    while(cur != head)
    {
        if(cur->data == value)
        {
            DLinkNode* pre = cur->prev;
            DLinkNode* nex = cur->next;
            pre->next = nex;
            nex->prev = pre;
            DestroyNode(cur);
        }
        cur = cur->next;
    }
    return;
}

void DLinklistDestroy(DLinkNode** phead)//销毁整个链表
{
    if(phead == NULL)
        return;
    DLinkNode* cur = (*phead)->next;
    while(cur != *phead)
    {
        DLinkNode* nex = cur->next;
        DestroyNode(cur);
        cur = nex;
    }
    DestroyNode(*phead);//要将头结点也销毁
    *phead = NULL;//置空，避免成为野指针
}

void TestInit()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    printf("excepted is 0,actual is %d\n",(int)head->data);//初始化中的0用%c打印不出来，这里用%d,且要进行强转为int，防止发生错误
}

void TestPushBack()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushBack(head,'a');
    DLinklistPushBack(head,'b');
    DLinklistPushBack(head,'c');
    DLinklistPushBack(head,'d');
    DLinklistPushBack(head,'e');
    DLinklistPrint(head,"尾插五个元素");
}

void TestPopBack()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushBack(head,'a');
    DLinklistPushBack(head,'b');
    DLinklistPushBack(head,'c');
    DLinklistPushBack(head,'d');
    DLinklistPrint(head,"尾插四个元素");
    DLinklistPopBack(head);
    DLinklistPopBack(head);
    DLinklistPrint(head,"尾删两个元素");
    DLinklistPopBack(head);
    DLinklistPopBack(head);
    DLinklistPrint(head,"再尾删两个元素");
}

void TestPushFront()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushFront(head,'a');
    DLinklistPushFront(head,'b');
    DLinklistPushFront(head,'c');
    DLinklistPushFront(head,'d');
    DLinklistPushFront(head,'e');
    DLinklistPrint(head,"头插五个元素");
}

void TestPopFront()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushFront(head,'a');
    DLinklistPushFront(head,'b');
    DLinklistPushFront(head,'c');
    DLinklistPushFront(head,'d');
    DLinklistPrint(head,"头插五个元素");
    DLinklistPopFront(head);
    DLinklistPopFront(head);
    DLinklistPrint(head,"头删两个元素");
    DLinklistPopFront(head);
    DLinklistPopFront(head);
    DLinklistPrint(head,"再头删两个元素");
} 

void TestFind()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushFront(head,'a');
    DLinklistPushFront(head,'b');
    DLinklistPushFront(head,'c');
    DLinklistPushFront(head,'d');
    DLinklistPushFront(head,'e');
    DLinklistPrint(head,"头插五个元素");
    DLinkNode* ret = DLinklistFind(head,'c');
    printf("[%c|%p]\n",ret->data,ret);
    DLinkNode* ret1 = DLinklistFind(head,'h');
    if(ret1 == NULL)
        printf("没找到\n");
    else
        printf("[%c|%p]\n",ret1->data,ret1);
}

void TestInsert()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushBack(head,'a');
    DLinklistPushBack(head,'b');
    DLinklistPushBack(head,'c');
    DLinklistPushBack(head,'d');
    DLinklistPrint(head,"尾插五个元素");
    DLinkNode* pos = head->next;
    DLinklistInsertBefore(head,pos,'h');
    DLinklistPrint(head,"向a前插入h");
    pos = head;
    DLinklistInsertBefore(head,pos,'z');
    DLinklistPrint(head,"向head前插入z");
    pos = head->prev;
    DLinklistInsertAfter(head,pos,'l');
    DLinklistPrint(head,"在最后一个结点之后插入l");
} 

void TestErase()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushFront(head,'a');
    DLinklistPushFront(head,'b');
    DLinklistPushFront(head,'c');
    DLinklistPushFront(head,'d');
    DLinklistPrint(head,"头插五个元素");
    DLinkNode* pos = head;
    DLinklistErase(head,pos);
    DLinklistPrint(head,"删除head");
    pos = head->next->next;
    DLinklistErase(head,pos);
    DLinklistPrint(head,"删除c");
    pos = head->prev;
    DLinklistErase(head,pos);
    DLinklistPrint(head,"删除a");
}   

void TestRemove()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushFront(head,'a');
    DLinklistPushFront(head,'b');
    DLinklistPushFront(head,'c');
    DLinklistPushFront(head,'d');
    DLinklistPrint(head,"头插五个元素");
    DLinklistRemove(head,0);
    DLinklistPrint(head,"删除0");
    DLinklistRemove(head,'a');
    DLinklistPrint(head,"删除a");
    DLinklistRemove(head,'d');
    DLinklistPrint(head,"删除d");
}   

void TestRemoveAll()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushFront(head,'a');
    DLinklistPushFront(head,'a');
    DLinklistPushFront(head,'c');
    DLinklistPushFront(head,'a');
    DLinklistPrint(head,"头插五个元素");
    DLinklistRemoveAll(head,'a');
    DLinklistPrint(head,"删除a");
}

void TestDestroy()
{
    SHOW_NAME;
    DLinkNode* head;
    DLinklistInit(&head);
    DLinklistPushFront(head,'a');
    DLinklistPushFront(head,'b');
    DLinklistPushFront(head,'c');
    DLinklistPushFront(head,'d');
    DLinklistPushFront(head,'e');
    DLinklistPrint(head,"头插五个元素");
    DLinklistDestroy(&head);
}

int main()
{
    TestInit();
    TestPushBack();
    TestPopBack();
    TestPushFront();
    TestPopFront();
    TestFind();
    TestInsert();
    TestErase();
    TestRemove();
    TestRemoveAll();
    TestDestroy();
    return 0;
}
