#include "Seqlist.h"

void SeqlistInit(Seqlist *seqlist)
{
	if(seqlist == NULL)//非法操作
		return;
	seqlist->size = 0;
}

void SeqlistPushBack(Seqlist *seqlist,SeqlistType value)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size >= SeqlistMAXSIZE) //顺序表已满
		return;
	seqlist->data[seqlist->size] = value;
	++seqlist->size;
	return;
} 

void SeqlistPopBack(Seqlist *seqlist)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size == 0)//空顺序表
		return;
	--seqlist->size;
}

void SeqlistPushFront(Seqlist *seqlist,SeqlistType value)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size >= SeqlistMAXSIZE)
		return;
	++seqlist->size;//给插入元素一个位置
	size_t i = seqlist->size - 1;
	for(i=seqlist->size-1; i>0; --i)
	{
		seqlist->data[i] = seqlist->data[i-1];
	}
	seqlist->data[0] = value;
	return;
}

void SeqlistPopFront(Seqlist *seqlist)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size == 0)
		return;
	size_t i = 0;
	for(i=0; i<seqlist->size-1; ++i)
	{
		seqlist->data[i] = seqlist->data[i+1];
	}
	--seqlist->size;
}

SeqlistType SeqlistGet(Seqlist *seqlist,size_t pos,SeqlistType default_value)
{
	if(seqlist == NULL)
		return default_value;
	if(seqlist->size == 0)//空表
		return default_value;
	if(pos >= seqlist->size)//pos越界
		return default_value;
	return seqlist->data[pos];
}

size_t SeqlistSearch(Seqlist *seqlist,SeqlistType value)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size == 0)
		return;
	size_t i =0;
	for(i=0; i<seqlist->size; ++i)
	{
		if(seqlist->data[i] == value)
		{
			return i;
		}
	}
	return -1;
}

void SeqlistSet(Seqlist *seqlist,size_t pos,SeqlistType value)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size == 0)
		return;
	if(pos >= seqlist->size)
		return;
	seqlist->data[pos] = value;
}

void SeqlistInsert(Seqlist *seqlist,size_t pos,SeqlistType value)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size >= SeqlistMAXSIZE)
		return;
	//if(pos == 0)
	//{
	//	SeqlistPushFront(value);
	//	return;
	//}
	++seqlist->size;
	size_t i = seqlist->size - 1;
	for(i=seqlist->size-1; i>pos; --i)
	{
		seqlist->data[i] = seqlist->data[i-1];
	}
	seqlist->data[pos] = value;
	return;
}

void SeqlistEarse(Seqlist *seqlist,size_t pos)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size == 0)
		return;
	if(pos >= seqlist->size)//pos越界
		return;
	size_t i = pos;
	for(i=pos; i<seqlist->size-1; ++i)
	{
		seqlist->data[i] = seqlist->data[i+1];
	}
	--seqlist->size;
	return;
}

void SeqlistRemove(Seqlist *seqlist,SeqlistType value)
{
	if(seqlist == NULL)
		return;
	size_t pos = SeqlistSearch(seqlist,value);
	if(pos == (size_t)-1)
		return;
	SeqlistEarse(seqlist,pos);
	return;
}

void SeqlistRemoveAll(Seqlist *seqlist,SeqlistType value)
{
	if(seqlist == NULL)
		return;
	while(1)
	{
		size_t pos = SeqlistSearch(seqlist,value);
		if(pos == (size_t)-1)
			return;
		SeqlistEarse(seqlist,pos);
	}
}

size_t SeqlistSize(Seqlist *seqlist)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size == 0)
		return 0;
	return seqlist->size;
}

int SeqlistEmpty(Seqlist *seqlist)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size == 0)
		return 1;
	return 0;
}

void Swap(SeqlistType *a,SeqlistType *b)//交换函数
{
	SeqlistType ret = *a;
	*a = *b;
	*b = ret;
}

void SeqlistBubbleSort(Seqlist *seqlist)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size <= 1)
		return;
	size_t count = 0;
	for(count=0; count<seqlist->size; ++count)
	{
		size_t cur = 0;
		for(cur=0; cur<seqlist->size-1-count; ++cur)
		{
			if(seqlist->data[cur] > seqlist->data[cur+1])
				Swap(&seqlist->data[cur],&seqlist->data[cur+1]);
		}
	}
}

int Greater(SeqlistType a,SeqlistType b)//降序实现
{
	return a>b?1:0;
}

int Lesser(SeqlistType a,SeqlistType b)//升序实现
{
	return a<b?1:0;
}

void SeqlistBubbleSortEx(Seqlist *seqlist,Cmp cmp)//运用函数指针
{
	if(seqlist == NULL)
		return;
	if(seqlist->size <= 1)
		return;
	size_t count = 0;
	for(count=0; count<seqlist->size; ++count)
	{
		size_t cur = 0;
		for(cur=0; cur<seqlist->size-1-count; ++cur)
		{
			if(cmp(seqlist->data[cur],seqlist->data[cur+1]))
			{
				Swap(&seqlist->data[cur],&seqlist->data[cur+1]);
			}
		}
	}
}

void SeqlistSelectSort(Seqlist *seqlist)
{
	if(seqlist == NULL)//非法操作
		return;
	if(seqlist->size <= 1)//最多有一个元素时，可以不排序
		return;
	size_t bound = 0;
	for(; bound < seqlist->size-1; ++bound)
	{
		size_t cur = bound +1;
		for(; cur<seqlist->size; ++cur)
		{
			if(seqlist->data[cur] < seqlist->data[bound])
				Swap(&seqlist->data[cur],&seqlist->data[bound]);
		}
	}
}

void SeqlistSelectSortEx(Seqlist *seqlist,Cmp cmp)
{
	if(seqlist == NULL)
		return;
	if(seqlist->size <= 1)
		return;
	size_t bound = 0;
	for(; bound < seqlist->size-1; ++bound)
	{
		size_t cur = bound +1;
		for(; cur<seqlist->size; ++cur)
		{
			if(cmp(seqlist->data[cur],seqlist->data[bound]))
				Swap(&seqlist->data[cur],&seqlist->data[bound]);
		}
	}
}

void SeqlistPrint(Seqlist *seqlist,const char *message)
{
	if(seqlist == NULL)
	{
		printf("非法操作\n");
		return;
	}
	printf("%s\n",message);
    size_t i = 0;
    for(i=0; i<seqlist->size; ++i)
        printf("[%c] ",seqlist->data[i]);
	printf("\n");
}





/////////////////////////////////////////////////////////////////////
///////////////          测试代码             //////////////////////
////////////////////////////////////////////////////////////////////





void TestInit()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	printf("期望为0，实际为%u\n",seqlist.size); 
} 

void TestPushBack()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushBack(&seqlist,'a'); 
	SeqlistPushBack(&seqlist,'b');
	SeqlistPushBack(&seqlist,'c'); 
	SeqlistPushBack(&seqlist,'d'); 
	SeqlistPrint(&seqlist,"尾部插入四个元素");
} 

void TestPopBack()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushBack(&seqlist,'a');
	SeqlistPushBack(&seqlist,'b');
	SeqlistPushBack(&seqlist,'c');
	SeqlistPushBack(&seqlist,'d');
	SeqlistPrint(&seqlist,"尾插四个元素");
	SeqlistPopBack(&seqlist);
	SeqlistPrint(&seqlist,"尾删一个元素");
}

void TestPushFront()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'a');
	SeqlistPushFront(&seqlist,'b');
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPrint(&seqlist,"前插四个元素");
}

void TestPopFront()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'a');	
	SeqlistPushFront(&seqlist,'b');
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPrint(&seqlist,"前插四个元素");
	SeqlistPopFront(&seqlist);
	SeqlistPopFront(&seqlist);
	SeqlistPrint(&seqlist,"前删两个元素");
}

void TestGet()
{
	SHOW_NAME;
	SeqlistType ret = 0;
	size_t key = 3;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushBack(&seqlist,'a');
	SeqlistPushBack(&seqlist,'b');
	SeqlistPushBack(&seqlist,'c');
	SeqlistPushBack(&seqlist,'d');
	SeqlistPrint(&seqlist,"尾插四个元素");
	ret = SeqlistGet(&seqlist,key,'x');
	if(ret == 'x')
		printf("未能成功取得该元素的值\n");
	else
		printf("下标值为%d的元素值为%c\n",key,ret);
}

void TestSearch()
{
	SHOW_NAME;
	size_t ret = 0;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushBack(&seqlist,'a');
	SeqlistPushBack(&seqlist,'b');
	SeqlistPushBack(&seqlist,'c');
	SeqlistPushBack(&seqlist,'d');
	SeqlistPrint(&seqlist,"尾插四个元素");
	ret = SeqlistSearch(&seqlist,'d');
	printf("pos respected 3,actual %ld\n",(int64_t)ret);
	ret = SeqlistSearch(&seqlist,'x');
	printf("pos respected -1,actual %ld\n",(int64_t)ret);
}

void TestSet()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushBack(&seqlist,'a');
	SeqlistPushBack(&seqlist,'b');
	SeqlistPushBack(&seqlist,'c');
	SeqlistPushBack(&seqlist,'d');
	SeqlistPrint(&seqlist,"尾插四个元素");
	SeqlistSet(&seqlist,2,'e');
	SeqlistPrint(&seqlist,"将pos=2位置的元素修改为e");
}

void TestInsert()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushBack(&seqlist,'a');
	SeqlistPushBack(&seqlist,'b');
	SeqlistPushBack(&seqlist,'c');
	SeqlistPushBack(&seqlist,'d');
	SeqlistPrint(&seqlist,"尾插四个元素");
	SeqlistInsert(&seqlist,0,'e');
	SeqlistPrint(&seqlist,"向pos=0的位置插入元素");
}

void TestEarse()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'a');
	SeqlistPushFront(&seqlist,'b');
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPrint(&seqlist,"前插四个元素");
	SeqlistEarse(&seqlist,1);
	SeqlistPrint(&seqlist,"删除pos=1位置的元素");
}

void TestRemove()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'a');
	SeqlistPushFront(&seqlist,'b');
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPrint(&seqlist,"前插五个元素");
	SeqlistRemove(&seqlist,'a');
	SeqlistRemove(&seqlist,'x');
	SeqlistPrint(&seqlist,"删除元素'a''x'顺序表变为");
}

void TestRemoveAll()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'a');
	SeqlistPushFront(&seqlist,'b');
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPrint(&seqlist,"前插五个元素");
	SeqlistRemoveAll(&seqlist,'c');
	SeqlistPrint(&seqlist,"删除元素'c'顺序表变为");
}

void TestSize()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'c');
	SeqlistPrint(&seqlist,"前插了两个元素");
	size_t ret = SeqlistSize(&seqlist);
	if(ret == 0)
		printf("顺序表为空\n");
	else
		printf("顺序表里有%u个元素\n",ret);
}

void TestEmpty()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'c');
	SeqlistPrint(&seqlist,"前插一个元素");
	int ret = SeqlistEmpty(&seqlist);
	if(ret == 1)
		printf("顺序表为空\n");
	else
		printf("顺序表不为空\n");
}

void TestBubbleSort()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'f');
	SeqlistPushFront(&seqlist,'a');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPushFront(&seqlist,'j');
	SeqlistPrint(&seqlist,"前插五个元素");
	SeqlistBubbleSort(&seqlist);
	SeqlistPrint(&seqlist,"排序后顺序表为");
}

void TestBubbleSortEx()
{
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'f');
	SeqlistPushFront(&seqlist,'a');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPushFront(&seqlist,'j');
	SeqlistPrint(&seqlist,"前插五个元素");
	SeqlistBubbleSortEx(&seqlist,Greater);
	SeqlistPrint(&seqlist,"升序排序");
	SeqlistBubbleSortEx(&seqlist,Lesser);
	SeqlistPrint(&seqlist,"降序排序");
}

void TestSelectSort()
{	
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'f');
	SeqlistPushFront(&seqlist,'a');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPushFront(&seqlist,'j');
	SeqlistPrint(&seqlist,"前插五个元素");
	SeqlistSelectSort(&seqlist);
	SeqlistPrint(&seqlist,"选择排序");
}

void TestSelectSortEx()
{	
	SHOW_NAME;
	Seqlist seqlist;
	SeqlistInit(&seqlist);
	SeqlistPushFront(&seqlist,'c');
	SeqlistPushFront(&seqlist,'f');
	SeqlistPushFront(&seqlist,'a');
	SeqlistPushFront(&seqlist,'d');
	SeqlistPushFront(&seqlist,'j');
	SeqlistPrint(&seqlist,"前插五个元素");
	SeqlistSelectSortEx(&seqlist,Greater);
	SeqlistPrint(&seqlist,"选择排序降序");
	SeqlistSelectSortEx(&seqlist,Lesser);
	SeqlistPrint(&seqlist,"选择排序升序");
}

int main()
{
	TestInit();
	TestPushBack();
	TestPopBack();
	TestPushFront();
	TestPopFront();
	TestGet();
	TestSearch();
	TestSet();
	TestInsert();
	TestEarse();
	TestRemove();
	TestRemoveAll();
	TestSize();
	TestEmpty();
	TestBubbleSort();
	TestBubbleSortEx();
	TestSelectSort();
	TestSelectSortEx();
	return 0;
}
