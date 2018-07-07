//带头结点的链表：创建一个新结点表示空链表，该结点即为头结点，且头结点中的数据无任何意义
//不带头结点的链表：用NULL表示空链表
//头结点的好处：不用考虑头指针的指向问题，只要头指针初始化完成，就永远指向头结点，仅在要销毁整个链表时考虑

//带头结点、带环、双向链表
#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SHOW_NAME printf("\n===================%s=================\n",__FUNCTION__);

typedef char DLinkType;
typedef struct DLinkNode
{
    DLinkType data;
    struct DLinkNode* prev;
    struct DLinkNode* next;
}DLinkNode;

DLinkNode* CreateDLinkNode(DLinkType value);//创建一个新结点
void DLinklistInit(DLinkNode** phead);//初始化
void DLinklistPushBack(DLinkNode* head,DLinkType value);//尾插
void DestroyNode(DLinkNode* node);//销毁结点
void DLinklistPopBack(DLinkNode* head);//尾删
void DLinklistPushFront(DLinkNode* head,DLinkType value);//头插
void DLinklistPopFront(DLinkNode* head);//头插
DLinkNode* DLinklistFind(DLinkNode* head,DLinkType value);//查找值为value的结点，找到返回结点，找不到返回NULL
void DLinklistInsertBefore(DLinkNode* head,DLinkNode* pos,DLinkType value);//向pos位置前插入
void DLinklistInsertAfter(DLinkNode* head,DLinkNode* pos,DLinkType value);//向pos位置后插入
void DLinklistErase(DLinkNode* head,DLinkNode* pos);//删除pos位置结点
void DLinklistRemove(DLinkNode* head,DLinkType value);//删除值为value的结点
void DLinklistRemoveAll(DLinkNode* head,DLinkType value);//删除值为value的所有结点
void DLinklistDestroy(DLinkNode** phead);//销毁结点


