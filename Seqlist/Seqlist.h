#pragma once //防止头文件重复包含
#include <stddef.h> //size_t头文件
#include <stdio.h>
#include <stdint.h>//int64_t头文件


#define SHOW_NAME printf("\n==========%s==========\n",__FUNCTION__)
#define SeqlistMAXSIZE 100
//#define SeqlistType char
typedef char SeqlistType;
typedef int (*Cmp)(SeqlistType a,SeqlistType b);

typedef struct Seqlist
{
	SeqlistType data[SeqlistMAXSIZE];
	size_t size;
}Seqlist;

void SeqlistInit(Seqlist *seqlist);//初始化
void SeqlistPushBack(Seqlist *seqlist,SeqlistType value);//顺序表尾插
void SeqlistPopBack(Seqlist *seqlist);//尾删

void SeqlistPushFront(Seqlist *seqlist,SeqlistType value);//前插
void SeqlistPopFront(Seqlist *seqlist);//前删

SeqlistType SeqlistGet(Seqlist *seqlist,size_t pos,SeqlistType default_value);//取得任意位置的元素
size_t SeqlistSearch(Seqlist *seqlist,SeqlistType value);//查找任意元素的下标
void SeqlistSet(Seqlist *seqlist,size_t pos,SeqlistType value);// 设置任意位置的元素
void SeqlistInsert(Seqlist *seqlist,size_t pos,SeqlistType value);//向任意位置pos插入元素
void SeqlistEarse(Seqlist *seqlist,size_t pos);//删除指定位置pos的元素
void SeqlistRemove(Seqlist *seqlist,SeqlistType value);//删除指定元素(若有相同的仅删除第一个即可)
void SeqlistRemoveAll(Seqlist *seqlist,SeqlistType value);//删除指定元素(若有相同的需全部删除)
size_t SeqlistSize(Seqlist *seqlist);//获取顺序表元素个数
int SeqlistEmpty(Seqlist *seqlist);//判断顺序表是否为空，为空返回1，否则返回0
void SeqlistBubbleSort(Seqlist *seqlist);//冒泡排序
void SeqlistBubbleSortEx(Seqlist *seqlist,Cmp cmp);//冒泡排序扩展
void SeqlistSelectSort(Seqlist *seqlist);//选择排序
void SeqlistSelectSortEx(Seqlist *seqlist,Cmp cmp);//选择排序扩展

//void TestInit();
//void TestPushBack();
//void SeqlistPrint(Seqlist *seqlist,const char *message); 
