//单向不带环不带头结点链表实现

#pragma once

#include <stdio.h>
#include <stdlib.h>//malloc头文件
#include <stddef.h>//sizeof

#define SHOW_NAME printf("\n==========%s==========\n",__FUNCTION__)

typedef char LinkNodeType;

typedef struct LinkNode
{
	LinkNodeType data;
	struct LinkNode* next;
}LinkNode;//*pLinkNode;
typedef int (*Cmp)(LinkNodeType a, LinkNodeType b);

typedef struct ComplexNode//复杂链表
{
    LinkNodeType data;
    struct ComplexNode* next;
    struct ComplexNode* random;//该指针指向任意
}ComplexNode;

void LinklistInit(LinkNode**);//初始化
LinkNode* CreateNode(LinkNodeType);//创建新结点
void LinklistPushBack(LinkNode**,LinkNodeType);//尾插一个结点
void LinklistPrintChar(LinkNode*,const char*);
void LinklistPopBack(LinkNode**);//尾删一个结点
void LinklistPushFront(LinkNode**,LinkNodeType);//头插一个结点
void LinklistPopFront(LinkNode**);//头删一个结点
LinkNode* LinklistFind(LinkNode*,LinkNodeType);//查找元素在链表中的位置（返回结点的地址）
void LinklistInsertAfter(LinkNode*,LinkNodeType);//在pos位置之后插入元素
void LinklistInsertBefore(LinkNode**,LinkNode*,LinkNodeType);//在pos位置之前插入元素,时间复杂度为O(n)
void LinklistInsertBefore1(LinkNode*,LinkNodeType);//在pos前插入元素，使得时间复杂度为O(1)
void LinklistErase(LinkNode**,LinkNode*);//删除pos结点,时间复杂度为O(n)
void LinklistErase1(LinkNode**,LinkNode*);//删除pos结点，时间复杂度为O(1)
void LinklistRemove(LinkNode**,LinkNodeType);//删除指定元素(如有相同值，只删除第一个)
void LinklistRemoveAll(LinkNode**,LinkNodeType);//删除指定元素(如有相同值，删除所有)
int LinklistEmpty(LinkNode* head);//判断链表是否为空，为空返回1，否则返回0
size_t LinklistSize(LinkNode* head);//统计链表中元素个数

///////////////                常见链表面试题                  ///////////////////////
void LinklistReversePrint(LinkNode* head);//逆序打印单链表
void LinklistInsertBefore1(LinkNode*,LinkNodeType);//在pos前插入元素，使得时间复杂度为O(1)
void LinklistReverse1(LinkNode**);//逆置单链表
void LinklistReverse2(LinkNode**);//逆置单链表
void LinklistBubbleSort(LinkNode*,Cmp);//冒泡排序
LinkNode* LinklistMerge(LinkNode* head1, LinkNode* head2);//将两个有序链表合成一个有序链表
LinkNode* LinklistFindLastKNode(LinkNode* head,size_t K);//找倒数第K个结点
void LinklistEraseLastKNode(LinkNode** head,size_t K);//删除倒数第K个结点
LinkNode* HasCycle(LinkNode* head);//判断链表是否带环，带环返回1
size_t LinklistGetCycleLen(LinkNode* head);//若链表带环，求环的长度
LinkNode* LinklistGetCycleEnter(LinkNode* head);//若链表带环，求环的入口
int LinklistHasCross(LinkNode* head1,LinkNode* head2);//两链表是否有交点，有则返回1(假设两链表均不带环)
LinkNode* LinklistHasCross1(LinkNode* head1,LinkNode* head2);//两链表是否有交点，有则求出交点(假设两链表均不带环)
int HasCrossWithCycle(LinkNode* head1,LinkNode* head2);//求两链表是否相交(链表可能有环),相交返回1
LinkNode* HasCrossWithCycle1(LinkNode* head1,LinkNode* head2);//求两链表的交点(可能有环)
LinkNode* UnionSet(LinkNode* head1,LinkNode* head2);//求两个有序链表的交集
ComplexNode* CopyComplex(ComplexNode* head);//拷贝复杂链表
ComplexNode* CopyComplex1(ComplexNode* head);//拷贝复杂链表

