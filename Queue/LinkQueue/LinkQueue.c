#include "LinkQueue.h"

void LinkQueueInit(LinkQueue* q)//初始化
{
    if(q == NULL)//非法输入
        return;
    q->head = NULL;
    q->tail =NULL;
}

void LinkQueueDestroy(LinkQueue* q)//销毁队列
{
    if(q == NULL)
        return;
    LinkNode* cur = q->head;
    while(cur != NULL)
    {
        LinkNode* to_delete = cur;
        cur = cur->next;
        free(to_delete);
    }
    q->head = q->tail = NULL;
    return;
}

LinkNode* CreateNode(LinkNodeType value)//新建一个结点
{
    LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void LinkQueuePush(LinkQueue* q,LinkNodeType value)//入队列(尾插)
{
    if(q == NULL)//非法操作
        return;
    if(q->head==NULL)//空队列
    {
        q->head = q->tail = CreateNode(value);
        return;
    }
    LinkNode* p = CreateNode(value);
    q->tail->next = p;
    q->tail = q->tail->next;
    return;
}

void LinkQueuePop(LinkQueue* q)//出列队(头删)
{
    if(q == NULL)//非法操作
        return;
    if(q->tail == NULL)//空队
        return;
    if(q->head->next == NULL)//只剩一个元素
    {
        q->head = q->tail = NULL;
        return;
    }
    LinkNode* ret = q->head->next;
    q->head = ret;
    return;
}

int LinkQueueGetFront(LinkQueue* q,LinkNodeType* value)//取队首元素
{
    if(q == NULL)
        return 0;
    if(q->tail == NULL)
        return 0;
    *value = q->head->data;
    return 1;
}

void LinkQueuePrint(LinkQueue* q,const char* msg)//打印
{
    printf("[%s]\n",msg);
    LinkNode* cur = q->head;
    for(; cur!=NULL; cur=cur->next)
    {
        printf("[%c] ",cur->data);
    }
    printf("\n");
    return;
}

void TestInit()
{
    SHOW_NAME;
    LinkQueue q;
    LinkQueueInit(&q);
}

void TestDestroy()
{
    SHOW_NAME;
    LinkQueue q;
    LinkQueueInit(&q);
    LinkQueueDestroy(&q);
}

void TestPush()
{
    SHOW_NAME;
    LinkQueue q;
    LinkQueueInit(&q);
    LinkQueuePush(&q,'a');
    LinkQueuePush(&q,'b');
    LinkQueuePush(&q,'c');
    LinkQueuePush(&q,'d');
    LinkQueuePush(&q,'e');
    LinkQueuePrint(&q,"入队五个元素");
}

void TestPop()
{
    SHOW_NAME;
    LinkQueue q;
    LinkQueueInit(&q);
    LinkQueuePush(&q,'a');
    LinkQueuePush(&q,'b');
    LinkQueuePush(&q,'c');
    LinkQueuePush(&q,'d');
    LinkQueuePush(&q,'e');
    LinkQueuePrint(&q,"入队五个元素");
    LinkQueuePop(&q);
    LinkQueuePop(&q);
    LinkQueuePop(&q);
    LinkQueuePrint(&q,"出队三个元素");
    LinkQueuePush(&q,'f');
    LinkQueuePush(&q,'g');
    LinkQueuePush(&q,'h');
    LinkQueuePrint(&q,"入队三个元素");
    LinkQueuePop(&q);
    LinkQueuePop(&q);
    LinkQueuePop(&q);
    LinkQueuePrint(&q,"出队三个元素");
    LinkQueuePop(&q);
    LinkQueuePop(&q);
    LinkQueuePrint(&q,"出队两个元素");
}

void TestGetFront()
{
    SHOW_NAME;
    LinkQueue q;
    LinkQueueInit(&q);
    LinkQueuePush(&q,'a');
    LinkQueuePush(&q,'b');
    LinkQueuePush(&q,'c');
    LinkQueuePrint(&q,"入队三个元素");
    int ret;
    LinkNodeType value;
    ret = LinkQueueGetFront(&q,&value);
    if(ret == 1)
        printf("取得队首元素为 %c\n",value);
    else
        printf("未取得队首元素\n");
    LinkQueuePop(&q);
    LinkQueuePop(&q);
    LinkQueuePop(&q);
    LinkQueuePrint(&q,"出队三个元素");
    ret = LinkQueueGetFront(&q,&value);
    if(ret == 1)
        printf("取得队首元素为 %c\n",value);
    else
        printf("未取得队首元素\n");
}

int main()
{   
    TestInit();
    TestDestroy();
    TestPush();
    TestPop();
    TestGetFront();
    return 0;
}
