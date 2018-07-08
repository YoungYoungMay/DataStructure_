#include "view.h"

//1.最小栈,出栈入栈的栈顶元素一直为最小值(两种方法) 
void SeqStackInit(SeqStack* stack)
{
    if(stack == NULL)
        return;
    stack->size = 0;
    stack->capacity = 10;
    stack->data = (StackType*)malloc(sizeof(StackType) * stack->capacity);
    return;
}

void MinStackInit(MinStack* min_stack)//初始化
{
    if(min_stack == NULL)
        return;
    min_stack->stack.size = 0;
    min_stack->stack.capacity = 5;//默认初始有capacity个元素
    min_stack->stack.data = (StackType*)malloc(sizeof(StackType)*(min_stack->stack.capacity));
    return;
}

void MinStackResize(MinStack* min_stack)//扩展空间
{
    if(min_stack == NULL)
        return;
    if(min_stack->stack.size < min_stack->stack.capacity)
        return;
    min_stack->stack.capacity = min_stack->stack.capacity * 2 + 1;//扩容规则由自己定
    StackType* new_ptr = (StackType*)malloc(sizeof(StackType) * min_stack->stack.capacity);
    size_t i = 0;
    for(; i<min_stack->stack.size; ++i)//拷贝原有数据到新内存
    {
        new_ptr[i] = min_stack->stack.data[i];
    }
    free(min_stack->stack.data);
    min_stack->stack.data = new_ptr;
    return;
}

int MinStackGetTop(MinStack* min_stack,StackType* value)//取栈顶元素
{
    if(min_stack == NULL || value == NULL)
        return 0;
    if(min_stack->stack.size == 0)//空栈
        return 0;
    *value = min_stack->stack.data[min_stack->stack.size - 1];
        return 1;
}

void MinStackPush1(MinStack* min_stack, StackType value)//入栈
{//每次入栈两个元素，第一个元素为要入栈的元素，第二个元素为当前栈内的最小元素
    if(min_stack == NULL)
        return;
    if(min_stack->stack.size >= min_stack->stack.capacity)//当前栈已满
    {
        MinStackResize(min_stack);//扩大已有空间
    }
    StackType min = value;
    StackType top;
    int ret = MinStackGetTop(min_stack,&top);
    if(ret != 0)
    {
        min = top < value ? top : value;
    }
    min_stack->stack.data[(min_stack->stack.size)++] = value;
    min_stack->stack.data[(min_stack->stack.size)++] = min;
    return;
}

void MinStackPush2(MinStack* min_stack1, MinStack* min_stack2, StackType value)//入栈
{//两个栈，第一个栈依次存放要入栈的元素，另一个栈存放当前第一个栈内的最小元素
    if(min_stack1 == NULL || min_stack2 == NULL)
        return;
    if(min_stack1->stack.size >= min_stack1->stack.capacity)//当前1栈已满
    {
        MinStackResize(min_stack1);//扩大已有空间
    }
    if(min_stack2->stack.size >= min_stack2->stack.capacity)//当前2栈已满
    {
        MinStackResize(min_stack2);//扩大已有空间
    }
    StackType min = value;
    StackType top;
    int ret = MinStackGetTop(min_stack2,&top);
    if(ret != 0)
    {
        min = top < value ? top : value;
    }
    min_stack1->stack.data[(min_stack1->stack.size)++] = value;//存放入栈元素
    min_stack2->stack.data[(min_stack2->stack.size)++] = min;//存放当前最小元素
    return;
}

void MinStackPop1(MinStack* min_stack)//出栈
{//入栈时一次入栈了两个元素，所以出栈一次也要出栈两个元素
    if(min_stack == NULL)
        return;
    if(min_stack->stack.size == 0)//空栈
        return;
    --min_stack->stack.size;
    --min_stack->stack.size;
}

void MinStackPop2(MinStack* min_stack1, MinStack* min_stack2)//出栈
{//入栈一次两个栈都入栈一个元素，所以出栈一次也要两个栈都出
    if(min_stack1 == NULL || min_stack2 == NULL)
        return;
    if(min_stack1->stack.size == 0 || min_stack2->stack.size == 0)//空栈
        return;
    --min_stack1->stack.size;
    --min_stack2->stack.size;
}

void MinStackPrint(MinStack* min_stack, const char* msg)
{
    printf("[%s]\n",msg);
    if(min_stack == NULL)
        return;
    size_t i = 0;
    for(; i<min_stack->stack.size; ++i)
    {
        printf("[%c] ",min_stack->stack.data[i]);
    }
    printf("\n");
    return;
}

//2.两个栈实现一个队列 
void QueueInit(QueueBy2Stack* q)
{
    if(q == NULL)
        return;
    q->input.size = 0;
    q->input.capacity = 5;//默认初始有capacity个元素
    q->input.data = (StackType*)malloc(sizeof(StackType) * (q->input.capacity));
    q->output.size = 0;
    q->output.capacity = 5;//默认初始有capacity个元素
    q->output.data = (StackType*)malloc(sizeof(StackType) * (q->output.capacity));
    return;
}

void SeqStackResize(SeqStack* stack)//扩容
{
    if(stack == NULL)
        return;
    if(stack->size < stack->capacity)
        return;
    stack->capacity = stack->capacity * 2 + 1;
    StackType* new_ptr = (StackType*)malloc(sizeof(StackType) * (stack->capacity));
    size_t i = 0;
    for(; i<stack->size; ++i)
    {
        new_ptr[i] = stack->data[i];
    }
    free(stack->data);
    stack->data = new_ptr;
    return;
}

void SeqStackPush(SeqStack* stack, StackType value)//入栈
{
    if(stack == NULL)
        return;
    if(stack->size >= stack->capacity)
        SeqStackResize(stack);
    stack->data[stack->size++] = value;
    return;
}

void SeqStackPop(SeqStack* stack)//出栈
{
    if(stack == NULL)
        return;
    if(stack->size == 0)
        return;
    --stack->size;
    return;
}

int SeqStackGetTop(SeqStack* stack, StackType* value)
{
    if(stack == NULL)
        return 0;
    if(stack->size == 0)
        return 0;
    *value = stack->data[stack->size - 1];
    return 1;
}

void QueuePush(QueueBy2Stack* q, StackType value)//入队
{//入队要向非空栈内入,
    if(q == NULL)
        return;
    while(1)//将output栈中的元素全部导入input栈中，再向input栈中入元素实现入队
    {
        StackType top;
        int ret = SeqStackGetTop(&q->output,&top);
        if(ret == 0)//output为空栈
            break;
        SeqStackPush(&q->input,top);
        SeqStackPop(&q->output);
    }
    SeqStackPush(&q->input,value);
    return;
}

void QueuePop(QueueBy2Stack* q)//出队
{//先将input栈内元素导入output栈内，再用出栈实现出队
    if(q == NULL)
        return;
    while(1)//将input全部元素导入output
    {
        StackType top;
        int ret = SeqStackGetTop(&q->input, &top);
        if(ret == 0)//input已空
            break;
        SeqStackPush(&q->output,top);
        SeqStackPop(&q->input);
    }
    SeqStackPop(&q->output);
    return;
}

int QueueGetTop(QueueBy2Stack* q, StackType* value)//取队首元素
{//取output栈顶元素实现取队首元素
    if(q == NULL)
        return;
    while(1)//将input全部元素导入output
    {
        StackType top;
        int ret = SeqStackGetTop(&q->input, &top);
        if(ret == 0)//input已空
            break;
        SeqStackPush(&q->output,top);
        SeqStackPop(&q->input);
    }
    int ret = SeqStackGetTop(&q->output, value);
    return ret;
}

void QueuePrint(QueueBy2Stack* q, const char* msg)//打印
{//将所有元素导入input栈内，打印input栈内元素以观察以上操作是否正确
    printf("[%s]\n",msg);
    if(q == NULL)
        return;
    while(1)//将output全部元素导入input
    {
        StackType top;
        int ret = SeqStackGetTop(&q->output, &top);
        if(ret == 0)//input已空
            break;
        SeqStackPush(&q->input,top);
        SeqStackPop(&q->output);
    }
    size_t i = 0;
    for(; i<q->input.size; ++i)
    {
        printf("[%c] ",q->input.data[i]);
    }
    printf("\n");
    return;
}

//3.两个队列实现一个栈(队列要注意头删尾插多次之后，元素的期待内位置到终点位置的变化)
void SeqQueueInit(SeqQueue* q)
{
    if(q == NULL)
        return;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
    return;
}

void SeqQueuePush(SeqQueue* q, StackType value)
{
    if(q == NULL)
        return;
    if(q->size >= MAX_SIZE)
        return;
    q->data[q->tail++] = value;
    if(q->tail >= MAX_SIZE)
        q->tail = 0;
    //q->tail %= MAX_SIZE;
    ++q->size;
    return;
}

void SeqQueuePop(SeqQueue* q)
{
    if(q == NULL)
        return;
    if(q->size == 0)
        return;
    ++q->head;
    if(q->head >= MAX_SIZE)
        q->head = 0;
    --q->size;
    return;
}

int SeqQueueGetFront(SeqQueue* q, StackType* value)
{
    if(q == NULL)
        return 0;
    if(q->size == 0)
        return 0;
    *value = q->data[q->head];
    return 1;
}

void StackInit(StackBy2Queue* q)
{
    if(q == NULL)
        return;
    SeqQueueInit(&q->queue1);
    SeqQueueInit(&q->queue2);
    return;
}

void StackPush(StackBy2Queue* q, StackType value)//入栈
{//向不为空的队列入，实现入栈
    if(q == NULL)
        return;
    if(q->queue1.size != 0)
        SeqQueuePush(&q->queue1,value);
    else
        SeqQueuePush(&q->queue2,value);
}

void StackPop(StackBy2Queue* q)//出栈
{//先将非空队列元素导入空队列至只剩一个，将剩下的一个元素出队实现出栈操做，其他元素依旧保持正确顺序
    if(q == NULL)
        return;
    if(q->queue1.size == 0 && q->queue2.size==0)//两个队列都空，即无元素
        return;
    SeqQueue* from = NULL;
    SeqQueue* to = NULL;
    //弄清楚谁向谁倒腾
    if(q->queue1.size != 0)
    {
        from = &q->queue1;
        to = &q->queue2;
    }
    else
    {
        from = &q->queue2;
        to = &q->queue1;
    }
    while(1)//倒腾一遍元素到空队列
    {
        if(from->size == 1)
            break;
        StackType front;
        SeqQueueGetFront(from,&front);
        SeqQueuePush(to,front);
        SeqQueuePop(from);
    }
    SeqQueuePop(from);
    return;
}

int StackGetTop(StackBy2Queue* q, StackType* value)//取栈顶元素
{//通过取队列中最后一个元素实现取栈顶元素
    if(q == NULL)
        return 0;
    if(q->queue1.size == 0 && q->queue2.size == 0)
        return 0 ;
    if(q->queue1.size != 0)
    {
        *value = q->queue1.data[q->queue1.tail - 1];
    }
    if(q->queue2.size != 0)
    {
        *value = q->queue2.data[q->queue2.tail - 1];
    }
    return 1;
}

void StackPrint(StackBy2Queue* q,const char* msg)
{
    printf("[%s]\n",msg);
    if(q == NULL)
        return;
    SeqQueue* p = NULL;
    if(q->queue1.size==0 && q->queue2.size==0)
    {
        printf("\n");
        return;
    }
    if(q->queue1.size != 0)
        p = &q->queue1;
    else
        p = &q->queue2;
    if(p->head < p->tail)
    {
        size_t i = p->head;
        for(; i<p->tail; ++i)
            printf("[%c] ",p->data[i]);
        printf("\n");
    }
    else
    {   
        size_t i = p->head;
        for(; i<MAX_SIZE; ++i)
            printf("[%c] ",p->data[i]);
        for(i = 0; i<p->tail; ++i)
            printf("[%c] ",p->data[i]);
        printf("\n");
    }
    return;
}


//4.判定字符串是否按照出栈顺序(根据入栈序列判断出栈序列的合法性)
int StackOrder(char input[], size_t isize, char output[], size_t osize)
{
    assert(input);
    assert(output);
    assert(isize == osize);//防止出入栈元素个数不同
    SeqStack stack;
    SeqStackInit(&stack);
    size_t i = 0;
    size_t j = 0;
    for(; i<isize; ++i)
    {
        SeqStackPush(&stack,input[i]);
        StackType top;
        int ret = SeqStackGetTop(&stack,&top);
        if(ret == 0)//栈空，进行最后判断
            break;
        while(1)
        {
            SeqStackGetTop(&stack,&top);
            if(j >= osize)//出栈序列已遍空，进行最后判断
                break;
            if(top != output[j])
            {
                break;
            }
            j++;
            SeqStackPop(&stack);
        }
    }
    if(stack.size == 0 && j == osize)
        return 1;
    return 0;
}

//5.共享栈(一个数组实现两个栈)
void SharedStackInit(SharedStack* stack)
{//[0,top1)表示1栈，[top2,MAX_SIZE)表示2栈
    if(stack == NULL)
        return;
    stack->top1 = 0;
    stack->top2 = MAX_SIZE;
}

void SharedStackPush1(SharedStack* stack, StackType value)//入1栈
{
    if(stack == NULL)
        return;
    if(stack->top1 >= stack->top2)//栈满
        return;
    stack->data[stack->top1++] = value;
    return;
}

void SharedStackPush2(SharedStack* stack, StackType value)//入2栈
{
    if(stack == NULL)
        return;
    if(stack->top1 >= stack->top2)//栈满
        return;
    stack->data[--stack->top2] = value;
    return;
}

void SharedStackPop1(SharedStack* stack)//出1栈
{
    if(stack == NULL)
        return;
    if(stack->top1 == 0)//1栈为空
        return;
    --stack->top1;
    return;
}

void SharedStackPop2(SharedStack* stack)//出2栈
{
    if(stack == NULL)
        return;
    if(stack->top2 == MAX_SIZE)//1栈为空
        return;
    ++stack->top2;
    return;
}

int SharedStackGetTop1(SharedStack* stack, StackType* value)//取1栈栈顶元素
{
    if(stack == NULL || value == NULL)
        return 0;
    if(stack->top1 == 0)//空栈
        return 0;
    *value = stack->data[stack->top1 - 1];
    return 1;
}

int SharedStackGetTop2(SharedStack* stack, StackType* value)//取1栈栈顶元素
{
    if(stack == NULL || value == NULL)
        return 0;
    if(stack->top2 == MAX_SIZE)//空栈
        return 0;
    *value = stack->data[stack->top2];
    return 1;
}

void SharedStackPrint(SharedStack* stack,const char* msg)
{
    printf("[%s]\n",msg);
    if(stack == NULL)
        return;
    size_t i = 0;
    for(; i<stack->top1; ++i)
    {
        printf("[%c] ",stack->data[i]);
    }
    printf("\n");
    i = MAX_SIZE-1;
    for(; i>=stack->top2; --i)
    {
        printf("[%c] ",stack->data[i]);
    }
    printf("\n");
    return;
}

/////////////////////////////////////////////////////////////////
//////////                 测试函数             ////////////////
////////////////////////////////////////////////////////////////


void MinStack1()
{
    SHOW_NAME;
    MinStack min_stack;
    MinStackInit(&min_stack);
    MinStackPush1(&min_stack,'a');
    MinStackPush1(&min_stack,'f');
    MinStackPush1(&min_stack,'c');
    MinStackPush1(&min_stack,'b');
    MinStackPrint(&min_stack,"入栈4个元素");
    MinStackPop1(&min_stack);
    MinStackPop1(&min_stack);
    MinStackPrint(&min_stack,"出栈两个元素");
}

void MinStack2()
{
    SHOW_NAME;
    MinStack min_stack1;
    MinStack min_stack2;
    MinStackInit(&min_stack1);
    MinStackInit(&min_stack2);
    MinStackPush2(&min_stack1, &min_stack2, 'a');
    MinStackPush2(&min_stack1, &min_stack2, 'f');
    MinStackPush2(&min_stack1, &min_stack2, 'c');
    MinStackPush2(&min_stack1, &min_stack2, 'b');
    MinStackPrint(&min_stack1,"入栈的4个元素");
    MinStackPrint(&min_stack2,"当前栈内最小元素");
    MinStackPop2(&min_stack1,&min_stack2);
    MinStackPop2(&min_stack1,&min_stack2);
    MinStackPop2(&min_stack1,&min_stack2);
    MinStackPrint(&min_stack1,"入栈的4个元素");
    MinStackPrint(&min_stack2,"当前栈内最小元素");
}

void Queue()
{
    SHOW_NAME;
    QueueBy2Stack q;
    QueueInit(&q);
    QueuePush(&q,'a');
    QueuePush(&q,'d');
    QueuePush(&q,'c');
    QueuePush(&q,'g');
    QueuePrint(&q,"入队四个元素");
    StackType top;
    int ret = QueueGetTop(&q,&top);
    if(ret == 0)
        printf("没取到当前队首元素\n");
    else
        printf("取得的队首元素为%c\n",top);
    QueuePop(&q);
    QueuePop(&q);
    QueuePrint(&q,"出队两个元素");
    ret = QueueGetTop(&q,&top);
    if(ret == 0)
        printf("没取到当前队首元素\n");
    else
        printf("取得的队首元素为%c\n",top);
    
    QueuePop(&q);
    QueuePop(&q);
    QueuePrint(&q,"出队两个元素");
    ret = QueueGetTop(&q,&top);
    if(ret == 0)
        printf("没取到当前队首元素\n");
    else
        printf("取得的队首元素为%c\n",top);
    
}

void Stack()
{
    SHOW_NAME;
    StackBy2Queue q;
    StackInit(&q);
    StackPush(&q,'c');
    StackPush(&q,'s');
    StackPush(&q,'r');
    StackPush(&q,'g');
    StackPrint(&q,"入栈四个元素");
    StackType top;
    int ret = StackGetTop(&q,&top);
    if(ret == 0)
        printf("未取得栈顶元素\n");
    else
        printf("取得的栈顶元素为%c\n",top);
    StackPop(&q);
    StackPop(&q);
    StackPrint(&q,"出栈两个元素");
    ret = StackGetTop(&q,&top);
    if(ret == 0)
        printf("未取得栈顶元素\n");
    else
        printf("取得的栈顶元素为%c\n",top);
    StackPop(&q);
    StackPrint(&q,"再出栈一个元素");
    ret = StackGetTop(&q,&top);
    if(ret == 0)
        printf("未取得栈顶元素\n");
    else
        printf("取得的栈顶元素为%c\n",top);   
    StackPop(&q);
    StackPrint(&q,"再出栈两个元素");
    ret = StackGetTop(&q,&top);
    if(ret == 0)
        printf("未取得栈顶元素\n");
    else
        printf("取得的栈顶元素为%c\n",top);    
}

void StackIsOrder()
{
    SHOW_NAME;
    char input[] = {'a','b','c','d','e'};
    char output[] = {'a','b','d','e','c'};
    size_t isize = sizeof(input);
    size_t osize = sizeof(output);
    int ret = StackOrder(input,isize,output,osize);
    if(ret == 1)
        printf("该出栈顺序合法\n");
    else
        printf("该出栈顺序不合法\n");
}

void ShareStack()
{
    SHOW_NAME;
    SharedStack stack;
    SharedStackInit(&stack);
    SharedStackPush1(&stack,'a'); 
    SharedStackPush1(&stack,'b');
    SharedStackPush1(&stack,'c');
    SharedStackPush1(&stack,'d');
    SharedStackPrint(&stack,"1栈入栈四个元素");
    StackType top;
    int ret = SharedStackGetTop1(&stack,&top);
    if(ret == 0)
        printf("未取得1栈顶元素\n");
    else
        printf("取得的1栈顶元素为%c\n",top);
    SharedStackPush2(&stack,'d');
    SharedStackPush2(&stack,'c');
    SharedStackPush2(&stack,'b');
    SharedStackPush2(&stack,'a');
    SharedStackPrint(&stack,"2栈入栈四个元素");
    ret = SharedStackGetTop2(&stack,&top);
    if(ret == 0)
        printf("未取得2栈顶元素\n");
    else
        printf("取得的2栈顶元素为%c\n",top);
    SharedStackPop1(&stack); 
    SharedStackPop1(&stack);
    SharedStackPrint(&stack,"1栈出栈两个元素");
    ret = SharedStackGetTop1(&stack,&top);
    if(ret == 0)
        printf("未取得1栈顶元素\n");
    else
        printf("取得的1栈顶元素为%c\n",top);
    SharedStackPop1(&stack);
    SharedStackPop1(&stack);
    SharedStackPrint(&stack,"1栈再出栈两个元素");
    ret = SharedStackGetTop1(&stack,&top);
    if(ret == 0)
        printf("未取得1栈顶元素\n");
    else
        printf("取得的1栈顶元素为%c\n",top);
    SharedStackPop2(&stack); 
    SharedStackPop2(&stack);
    SharedStackPrint(&stack,"2栈出栈两个元素");
    ret = SharedStackGetTop2(&stack,&top);
    if(ret == 0)
        printf("未取得2栈顶元素\n");
    else
        printf("取得的2栈顶元素为%c\n",top);
}

int main()
{
    MinStack1();
    MinStack2();
    Queue();
    Stack();
    StackIsOrder();
    ShareStack();
    return 0;
}
