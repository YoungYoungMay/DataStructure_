#include "heap.h"

//1.初始化，决定是大堆还是小堆

int Greater(HeapType a, HeapType b)//大堆控制函数
{
    return a > b ? 1 : 0;
}

int Less(HeapType a, HeapType b)//小堆控制函数
{
    return a < b ? 1 : 0;
}

void HeapInit(Heap* heap, Compare cmp)//初始化
{
    if(heap == NULL)//非法输入
        return;
    heap->size = 0;//不用初始化data,因为size控制着data是否有效
    heap->cmp = cmp;
    return;
}

//2.销毁堆
void HeapDestroy(Heap* heap)//销毁
{
    if(heap == NULL)
        return;
    heap->size = 0;
    heap->cmp = NULL;
    return;
}

//3.打印函数
void HeapPrint(Heap heap)
{
    size_t i = 0;
    for(; i<heap.size; ++i)
    {
        printf("[%c|%p] ",heap.data[i]);
    }
    printf("\n");
    return;
}


//4.向堆内插入一个元素,要注意插入元素后继续保持堆的定义
void Swap(HeapType* a, HeapType* b)//交换函数
{
    HeapType tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void AdjustUp(Heap* heap, size_t index)//上浮式调整函数
{
    if(heap == NULL)
        return;
    size_t child = index;//尽量保证每个变量只做一件事
    size_t parent = (child-1)/2;
    //调整的最大限度就是将传入的调整元素调整至整个堆的根结点，即下标为0
    while(child > 0)
    {
        //不满足堆的定义
        if(!heap->cmp(heap->data[parent], heap->data[child]))
        {
            Swap(&heap->data[parent], &heap->data[child]);
        }
        //若发现某一位置，child与parent已满足堆的定义，就停止调整，因为上面的必定满足堆的定义
        else
            break;
        child = parent;
        parent = (parent-1)/2;
    }
    return;
}

void HeapInsert(Heap* heap, HeapType to_insert)//给定一个值，插入堆中
{//这里不能指定位置插入，因为要保证插入后它依旧是一个堆
    if(heap == NULL)//非法输入
        return;
    if(heap->size >= MAXSIZE)//堆已满
        return;
    //插入堆中
    heap->data[heap->size++] = to_insert;
    //对该堆进行上浮式的调整，调整的起始位置为size-1
    AdjustUp(heap, heap->size-1);
    return;
}

//5.取堆顶元素
int HeapRoot(Heap heap, HeapType* root)//取到返回1，且元素在root中，取不到返回0
{
    if(heap.size == 0)//空堆
        return 0;
    *root = heap.data[0];//下标为0的元素即堆顶元素
    return 1;
}

//6.删除堆顶元素,要注意保证删除后依旧满足堆的定义
void AdjustDown(Heap* heap, size_t index)//下沉式调整堆
{
    if(heap == NULL)
        return;
    size_t parent = index;
    size_t child = parent*2 + 1;
    while(child < heap->size)
    {
        //若右子树存在，且比左子树更符合堆的要求
        //则让child指向右子树
        if((child+1 < heap->size) && (heap->cmp(heap->data[child+1], heap->data[child])))
        {
            child = child + 1;
        }
        //不满足堆的定义时,继续下沉
        if(heap->cmp(heap->data[child], heap->data[parent]))
        {
            Swap(&heap->data[child], & heap->data[parent]);
        }
        //在某点时已满足堆的定义了，即可停止调整
        else
            break;
        parent = child;
        child = child*2 + 1;
    }
    return;
}

void HeapEarseRoot(Heap* heap)//删除堆顶元素
{
    if(heap == NULL)//非法输入
        return;
    if(heap->size == 0)//空堆
        return;
    //将堆顶元素与最后一个元素交换
    Swap(&heap->data[0], &heap->data[heap->size-1]);
    //再让size--即实现对堆顶元素的删除
    --heap->size;
    //再下浮式调整堆，使其依旧满足堆的定义,调整起始位置为0
    AdjustDown(heap,0);
}

//7.给定一个数组内容，依此创建堆
void HeapCreate(Heap* heap, HeapType arr[], size_t size)//给定数组，依据内容创建堆
{
    if(heap == NULL)
        return;
    //遍历数组，调用之前的插入函数即可
    size_t i = 0;
    for(; i<size; ++i)
    {
        HeapInsert(heap, arr[i]);
    }
    return;
}

//8.对堆进行排序
void HeapSort(HeapType arr[], size_t size)
{
    //将数组构成堆
    Heap heap;
    HeapInit(&heap, Greater);
    HeapCreate(&heap, arr, size);
    ////这里打印一下建立好的堆
    //HeapPrint(heap);
    //循环对堆进行删除堆顶元素操作，直到删完，排序就完成
    //虽然删完之后堆为空，但是数据还在，只是置为无效了而已
    while(heap.size > 0)
    {
        HeapEarseRoot(&heap);
    }
    //再将排序好的数据拷贝回数组
    memcpy(arr, heap.data, size*sizeof(HeapType));
    return;
}


////////////////////////////////////////////////////////////////////
////////////           以下为测试代码                   ////////////
///////////////////////////////////////////////////////////////////


void TestInit()
{
    SHOW_NAME;
    Heap heap;
    HeapInit(&heap,Greater);//这里我们实现大堆
    printf("size: expected is 0,actual is %d\n", heap.size); 
    printf("cmp is %p\n",heap.cmp);
}

void TestDestroy()
{
    SHOW_NAME;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("size: expected is 0,actual is %d\n", heap.size); 
    printf("cmp is %p\n",heap.cmp);
    HeapDestroy(&heap);
    printf("size: expected is 0,actual is %d\n", heap.size); 
    printf("cmp: expected is nil,actual is %p\n",heap.cmp);
}

void TestInsert()
{
    SHOW_NAME;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap, 's');
    HeapInsert(&heap, 'v');
    HeapInsert(&heap, 'b');
    HeapInsert(&heap, 'n');
    HeapInsert(&heap, 'a');
    HeapInsert(&heap, 'l');
    HeapPrint(heap);
}

void TestRoot()
{
    SHOW_NAME;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap, 's');
    HeapInsert(&heap, 'v');
    HeapInsert(&heap, 'b');
    HeapInsert(&heap, 'n');
    HeapInsert(&heap, 'a');
    HeapInsert(&heap, 'l');
    HeapPrint(heap);
    HeapType root;
    int ret = HeapRoot(heap, &root);
    printf("expected is v, actual is %c\n", root);
}

void TestEarse()
{
    SHOW_NAME;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap, 's');
    HeapInsert(&heap, 'v');
    HeapInsert(&heap, 'b');
    HeapInsert(&heap, 'n');
    HeapInsert(&heap, 'a');
    HeapInsert(&heap, 'l');
    HeapPrint(heap);
    HeapEarseRoot(&heap);
    HeapPrint(heap);
}

void TestCreate()
{
    SHOW_NAME;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapType arr[] = "augondlr";
    printf("%s\n", arr);
    size_t size = sizeof(arr) - 1;
    HeapCreate(&heap, arr, size);
    HeapPrint(heap);
}

void TestSort()
{
    SHOW_NAME;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapType arr[] = "augondlr";
    printf("%s\n", arr);
    size_t size = sizeof(arr) - 1;
    HeapSort(arr, size);
    printf("%s\n", arr);
}

int main()
{
    TestInit();
    TestDestroy();
    TestInsert();
    TestRoot();
    TestEarse();
    TestCreate();    
    TestSort();
    return 0;
}
