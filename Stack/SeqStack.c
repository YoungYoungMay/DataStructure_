#include "SeqStack.h"

void SeqStackInit(SeqStack* stack)//初始化
{
    if(stack == NULL)
    {
        return;
    }
    stack->size = 0;
    stack->capacity = 1000;//元素个数，而非内存字节数
    stack->data = (SeqStackType*)malloc(stack->capacity * sizeof(SeqStackType));
    return;
}

void SeqStackDestroy(SeqStack* stack)//销毁
{
    free(stack->data);
    stack->size = 0;
    stack->capacity = 0;
    return;
}

void SeqStackResize(SeqStack* stack)//扩容函数
{
    if(stack == NULL)//双重保证
    {
        return;
    }
    if(stack->size < stack->capacity)
    {
        return;
    }
    stack->capacity = stack->capacity *2 +1;//扩容规则根据自己喜好定,这里+1是避免传入的capacity为0
    //申请新内存
    SeqStackType* new_ptr = (SeqStackType*)malloc(stack->capacity * sizeof(SeqStackType));
    //将原来数据拷贝到新申请空间里(不推荐使用realloc)
    size_t i = 0;
    for(; i<stack->size; ++i)
    {
        new_ptr[i] = stack->data[i];
    }
    free(stack->data);//释放旧内存
    stack->data = new_ptr;
    return;
}

void SeqStackPush(SeqStack* stack, SeqStackType value)//元素进栈
{
    if(stack == NULL)
    {
        return;
    }
    if(stack->size >= stack->capacity)//栈已满，需要扩容
    {
        SeqStackResize(stack);//调用扩容函数
    }
    stack->data[stack->size++] = value;
    return;
}

void SeqStackPop(SeqStack* stack)//元素出栈
{
    if(stack == NULL)
        return;
    if(stack->size == 0)//空栈
        return;
    stack->size--;//把最后一个元素置为无效即可
    return;
}

int SeqStackGetTop(SeqStack* stack, SeqStackType* top)//取栈顶元素,返回两信息：是否取成功;用输出型参数top返回取得的栈顶元素
{
    if(stack == NULL || top == NULL)
        return 0;
    if(stack->size == 0)
        return 0;
    *top = stack->data[stack->size-1];//这里不能写stack->size--，会改变size值
    return 1;
}

void SeqStackPrint(SeqStack* stack,const char* msg)//打印栈内元素，为了检测释放入栈、出栈，实际上是不能打印栈的
{
    printf("%s\n",msg);
    if(stack == NULL)
        return;
    size_t i = 0;
    for(; i<stack->size; ++i)
    {
        printf("[%c] ",stack->data[i]);
    }
    printf("\n");
    return;
}

void TestInit()
{
    SHOW_NAME;
    SeqStack stack;
    SeqStackInit(&stack);
    printf("size : excepted is 0,actual is %d\n",stack.size);
    printf("capacity : excepted is 1000,actual is %d\n",stack.capacity);
    return;
}

void TestDestroy()
{
    SHOW_NAME;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackDestroy(&stack);
    return;
}

void TestPush()
{
    SHOW_NAME;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackPush(&stack,'e');
    SeqStackPush(&stack,'f');
    SeqStackPrint(&stack,"入栈六个元素");
    return;
}

void TestPop()
{
    SHOW_NAME;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackPrint(&stack,"入栈六个元素");
    SeqStackPop(&stack);
    SeqStackPop(&stack);
    SeqStackPrint(&stack,"出栈两个元素");
    SeqStackPop(&stack);
    SeqStackPop(&stack);
    SeqStackPrint(&stack,"再出栈两个元素");
    SeqStackPop(&stack);
    SeqStackPrint(&stack,"再出栈一个元素");
    return;
}

void TestGetTop()
{
    SHOW_NAME;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackPush(&stack,'e');
    SeqStackPush(&stack,'f');
    SeqStackPrint(&stack,"入栈六个元素");
    SeqStackType top;
    int ret = SeqStackGetTop(&stack,&top);
    if(ret == 1)
    {
        printf("获取栈顶元素成功，栈顶元素为 %c\n",top);
    }
    else
    {
        printf("获取栈顶元素失败\n");
    }
    return;
}

int main()
{
    TestInit();
    TestDestroy();
    TestPush();
    TestPop();
    TestGetTop();
    return 0;
}
