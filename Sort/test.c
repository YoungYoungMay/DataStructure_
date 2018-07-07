//实现各种排序算法
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "SeqStack.c"

void Swap(int* a, int* b)//交换函数
{
    int ret = *a;
    *a = *b;
    *b = ret;
    return;
}

//1.冒泡排序:从后向前冒，每次把最小的放在前面
void BubbleSort(int arr[], size_t size)
{
    if(size <= 1)//元素个数不用排序
        return;
    //[0,bound)表示有序元素，[bound,size)表示待排序元素
    size_t bound = 0;
    for(; bound<size; ++bound)
    {
        size_t cur = size - 1;
        for(; cur>bound; --cur)
        {
            if(arr[cur] < arr[cur-1])
                Swap(&arr[cur], &arr[cur-1]);
        }

    }
}

//2.选择排序:升序
void SelectSort(int arr[], size_t size)
{
    if(size <= 1)
        return;
    size_t bound = 0;
    for(; bound<size; ++bound)
    {
        size_t cur = bound + 1;
        for(; cur < size; ++cur)
        {
            if(arr[bound] > arr[cur])
                Swap(&arr[bound], &arr[cur]);
        }
    }
}

//3.插入排序
//把有序区间当作线性表，把bound所指元素插入到这个有序的线性表中
void InsertSort(int arr[], size_t size)
{
    if(size <= 1)
        return;
    //1.定义好边界，[0,bound)表示有序的线性表
    size_t bound = 1;
    for(; bound<size; ++bound)
    {
        //2.保存当前bound所指的元素
        int value = arr[bound];//保存是为了搬运
        size_t cur = bound;//cur辅助搬运，
        //3.从后向前去找一个合适的放置当前bound所指的元素
        for(; cur>0; --cur)
        {
            if(arr[cur-1] > value)//搬运
            {
                arr[cur] = arr[cur-1];
            }
            else//已找到合适位置
                break;
        }
        //该句不能写在else控制的语句中
        //因为若当前bound所指元素前面所以有都比它大，此时要插入到数组的第一个元素，但是此时循环结束了，执行不了该句赋值
        arr[cur] = value;//插入bound所指元素
    }
}

//4.堆排序
void AdjustDown(int arr[], size_t size, size_t index)//下沉式调整函数
{
    size_t parent = index;
    size_t child = 2*parent + 1;
    while(child < size)
    {//建大堆
        if(child+1 < size && arr[child] < arr[child+1])
            child = child + 1;
        //此时child指向左右子树较大的一个
        if(arr[parent] < arr[child])
            Swap(&arr[parent], &arr[child]);
        parent = child;
        child = 2*parent + 1;
    }       
}

void AdjustUp(int arr[], size_t size, size_t index)//上浮式调整函数
{
    size_t child = index;
    size_t parent = (child-1)/2;
    while(child > 0)
    {//建大堆
        if(arr[parent] < arr[child])
            Swap(&arr[parent], &arr[child]);
        child = parent;
        parent = (child-1)/2;
    }       
}
void HeapCreate(int arr[], size_t size)//创建堆
{//大堆->升序
    if(size <= 1)
        return;
    //下沉式调整
    //从后向前遍历，起始位置是堆从后向前第一个非叶子结点
    size_t i = (size-1-1)/2;//最后一个元素的父结点就是起始位置
    for(; i>0; --i)
    {
        AdjustDown(arr, size, i);
    }
    AdjustDown(arr, size, 0);//该句不能写在循环当中
    //上浮式调整
    //从前向后遍历，起始位置为数组首元素
    //for(i=0; i<size;++i)
    //{
    //    AdjustUp(arr, i+1,i);
    //}
}

void HeapPop(int arr[], size_t size)//删除堆顶元素
{
    if(size <= 1)
        return;
    Swap(&arr[0], &arr[size-1]);
    AdjustDown(arr, size-1, 0);
}

void HeapSort(int arr[], size_t size)//堆排序
{
    if(size <= 1)
        return;
    //创建堆
    HeapCreate(arr, size);
    //循环删除堆顶元素
    size_t i = 0;
    for(; i<size; ++i)
    {
        HeapPop(arr, size-i);//第二个参数表示当前数组中哪部分满足堆的规则
        //第一次删除前，[0,size)是堆;
        //第二次删除前，[0,size-1)是堆;
        //第三次删除前，[0,size-2)是堆...
    }
    return;
}

//5.希尔排序：分组式的插入排序
//定义一个初始步长(下标间隔)gap，按步长将待排序数列分组
//将分好的组，每组插入排序,然后gap--
//重复以上步骤，直至gap=0
//N/2,N/4,N/8...希尔序列，时间复杂度为O(N)
void ShellSort(int arr[], size_t size)
{
    if(size <= 1)
        return;
    int64_t gap = size/2;//使用希尔序列
    //1.第一重循环，生成步长序列
    for(; gap>0; gap /= 2)
    {
        //2.第二重循环，进入插入排序
        //此循环的执行顺序，相当于先处理第一组的第一个
        //再处理第二组的第一个....
        //再第二组的第一个....
        int64_t bound = gap;//此处相当于插入排序中的bound=1
        for(; bound<size;++bound)
        {
            int bound_value = arr[bound];//待插入元素
            //3.第三重循环，线性表的搬运(一边找一边搬运)
            int64_t cur = bound;
            for(; cur>=gap;cur -= gap)//cur-=gap是为了找到同组元素的上一个元素
            {
                if(arr[cur-gap] > bound_value)//进行搬运
                    arr[cur] = arr[cur-gap];
                else//找到了合适的插入位置
                    break;
            }
            arr[cur] = bound_value;
        }
    }
}

//6.归并排序
//(1)递归版本
void _MergeArr(int arr[], int64_t beg, int64_t mid, int64_t end, int* tmp)
{//归并两个子区间，传入的两个子区间本身有序
    int64_t cur1 = beg;
    int64_t cur2 = mid;
    int64_t tmp_index = beg;
    while(cur1<mid && cur2<end)//有一个子区间比较结束了，循环结束，可将另一个子区间剩下的元素一次性全放进去，因为每个子区间本身有序
    {//将数据按从小到大存放到tmp空间中
        if(arr[cur1] < arr[cur2])
            tmp[tmp_index++] = arr[cur1++];
        else
            tmp[tmp_index++] = arr[cur2++];
    }
    while(cur1 < mid)
        tmp[tmp_index++] = arr[cur1++];
    while(cur2 < end)
        tmp[tmp_index++] = arr[cur2++];
    //把tmp中的内容拷贝到数组，进行归并处理时的区间是arr[beg,end)
    memcpy(arr+beg, tmp+beg, sizeof(int)*(end-beg));
    return;
}


void _MergeSort(int arr[], int64_t beg, int64_t end, int* tmp)
{//[beg,end)为当前要处理的子区间
    //size_t类型作减法很危险，所以这里用int64_t
    if(end - beg <= 1)//最多一个元素或非法区间
        return;
    int64_t mid = beg + (end-beg)/2;
    //此时有两个区间[beg,mid)、[mid,end)
    _MergeSort(arr, beg, mid, tmp);
    _MergeSort(arr, mid, end, tmp);
    _MergeArr(arr, beg, mid, end, tmp);
}

void MergeSort(int arr[], size_t size)
{
    if(size <= 1)
        return;
    //创建临时空间，用于辅助归并元素
    int* tmp = (int*)malloc(sizeof(int)*size);
    _MergeSort(arr, 0, size, tmp);
    free(tmp);
}

//(2)非递归版本
void MergeSortByLoop(int arr[], size_t size)
{
    if(size <= 1)
        return;
    int* tmp = (int*)malloc(sizeof(int)*size);
    //定义一个初始步长gap=1,相当于每次合并两个长度为gap的有效区间
    size_t gap = 1;
    for(; gap<size; gap*=2)
    {
        //在当前gap下，我们利用i辅助完成所有长度为gap的区间的合并
        size_t i = 0;
        for(; i<size; i+=2*gap)
        {//[beg,mid)、[mid,end)
            size_t beg = i;
            size_t mid = i+gap;
            if(mid > size)//防止mid超过数组最大范围
                mid = size;
            size_t end = i+2*gap;
            if(end > size)//防止end超过数组最大范围
                end = size;
            _MergeArr(arr, beg, mid, end, tmp);
        }
    }
    free(tmp);
}

//7.快速排序
//(1)递归版本

int64_t Partion(int arr[], int64_t beg, int64_t end)//1.交换法
{
    if(end-beg <= 1)
        return beg;
    int64_t left = beg;
    int64_t right = end-1;//前闭后开区间
    int key = arr[right];//最后一个元素作为基准值
    while(left < right)
    {
        //从左到右找一个大于key的元素
        while(left < right && arr[left] <= key)
            ++left;
        //从右到左找一个小于Key的元素
        while(left < right && arr[right] >= key)
            --right;
        if(left < right)
            Swap(&arr[left], &arr[right]);
    }
    Swap(&arr[left], &arr[end-1]);
    return left;
}

int64_t Partion1(int arr[], int64_t beg, int64_t end)//1.挖坑法
{
    if(end-beg <= 1)
        return beg;
    int64_t left = beg;
    int64_t right = end-1;//前闭后开区间
    int key = arr[right];//最后一个元素作为基准值
    while(left < right)
    {
        while(left < right && arr[left] <= key)
            ++left;
        //此时left指向一个大于基准值Key的元素
        //可以把该值填到right所指的坑，赋值完成后，left所指又变成一个坑
        if(left < right)
            arr[right--] = arr[left];
        while(left < right && arr[right] >= key)
            --right;
        if(left < right)
            arr[left++] = arr[right];
    }
    //left与right重合，整个区间整理完毕，只剩下left=right位置为坑，将基准值填入即可
    arr[left] = key;
    return left;
}

void _QuickSort(int arr[], int64_t beg,int64_t end)
{
    if(end-beg <= 1)//当前区间内最多只有一个元素
        return;
    //[beg,mid)左半部分区间，[mid+1, end)右半部分区间，左半部分元素一定小于等于右半部分区间元素
    //int64_t mid = Partion(arr, beg, end);
    int64_t mid = Partion1(arr, beg, end);
    _QuickSort(arr, beg, mid);
    _QuickSort(arr, mid+1, end);
    return;
}

void QuickSort(int arr[], size_t size)
{
    _QuickSort(arr, 0, size);
    return;
}


//(2)非递归版本实现
void QuickSortByLoop(int arr[], size_t size)
{
    if(size <= 1)
        return;
    SeqStack stack;
    SeqStackInit(&stack);
    int64_t beg = 0;
    int64_t end = size;
    SeqStackPush(&stack, beg);
    SeqStackPush(&stack, end);

    while(1)
    {
        int ret = SeqStackGetTop(&stack, &end);
        if(ret == 0)//栈空，说明快排结束
            break;
        SeqStackPop(&stack);
        SeqStackGetTop(&stack, &beg);
        //[beg,end)相当于即将要进行快排整理的区间
        if(end-beg <= 1)
            continue;
        //int64_t mid = Partion(arr, beg, end);
        int64_t mid = Partion1(arr, beg, end);
        
        //[beg, mid),[mid+1, end)
        SeqStackPush(&stack, beg);
        SeqStackPush(&stack, mid);
        SeqStackPush(&stack, mid+1);
        SeqStackPush(&stack, end);
    }
}

int main()
{
    int a[10] = {1,3,5,-1,-5,8,9,7,12,30};
    int size = sizeof(a)/sizeof(a[0]); 
    int i = 0;
    for(; i<size; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
   
    //BubbleSort(a, size);
    //SelectSort(a, size);
    //InsertSort(a, size);
    //HeapSort(a, size);
    //ShellSort(a, size);
    //MergeSort(a,size);
    //MergeSortByLoop(a, size);
    //QuickSort(a, size);
    QuickSortByLoop(a, size);

    for(i=0; i<size; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
