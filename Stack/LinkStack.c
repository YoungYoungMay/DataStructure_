#include "LinkStack.h"

LinkStack* CreateNode(LinkStackType value)//创建新结点
{
    LinkStack* new_node = (LinkStack*)malloc(sizeof(LinkStack));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void LinkStackInit(LinkStack** stack)//初始化
{
    *stack = NULL;
}

void LinkStackPush(LinkStack** stack,LinkStackType value)//元素入栈(尾插)
{
    if(stack == NULL)
        return;
    if(*stack == NULL)//空栈
    {
        *stack = CreateNode(value);
        return;
    }
    LinkStack* cur = *stack;
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    LinkStack* new_node = CreateNode(value);
    cur->next = new_node;
    new_node->next = NULL;
    return;
}

void DestroyNode(LinkStack* node)//销毁结点
{
    free(node);//每一个malloc对应一个free
}

void LinkStackPop(LinkStack** stack)//元素出栈(尾删)
{
    if(stack == NULL)//非法
        return;
    if(*stack == NULL)//空栈
        return;
    if((*stack)->next == NULL)//仅有一个元素
    {
        DestroyNode(*stack);
        *stack = NULL;
        return;
    }
    LinkStack* cur = *stack;
    LinkStack* pre = NULL;//最后一个元素出栈后，还需将其next置空
    while(cur->next != NULL)
    {
        pre = cur;
        cur = cur->next;
    }
    pre->next = NULL;//链表的最后一个元素的next一定为NULL
    DestroyNode(cur);
}

int LinkStackGetTop(LinkStack* stack,LinkStackType* top)//取栈顶元素(链表的最后一个元素)
{
    if(stack == NULL || top == NULL)//空栈
        return 0;
    LinkStack* cur = stack;
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    *top = cur->data;
    return 1;
}

void LinkStackDestroy(LinkStack** stack)//销毁栈
{
    if(stack == NULL)//非法操作
        return;
    if(*stack == NULL)
        return;
    LinkStack* cur = *stack;
    while(cur != NULL)
    {
        LinkStack* to_delete = cur;
        cur = cur->next;
        DestroyNode(to_delete);
    }
    *stack = NULL;
}

void LinkStackPrint(LinkStack* stack,const char* msg)//打印栈中元素，检测一下代码是否正确
{
    printf("[%s]\n",msg);
    LinkStack* cur = stack;
    while(cur != NULL)
    {
        printf("[%c] ",cur->data);
        cur = cur->next;
    }
    printf("\n");
    return;
}

void TestInit()
{
    SHOW_NAME;
    LinkStack* stack;
    LinkStackInit(&stack);
}

void TestPush()
{
    SHOW_NAME;
    LinkStack* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
    LinkStackPush(&stack,'c');
    LinkStackPush(&stack,'d');
    LinkStackPush(&stack,'e');
    LinkStackPrint(stack,"入栈五个元素");
}

void TestPop()
{
    SHOW_NAME;
    LinkStack* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
    LinkStackPush(&stack,'c');
    LinkStackPush(&stack,'d');
    LinkStackPrint(stack,"入栈五个元素");
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrint(stack,"出栈两个元素");
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrint(stack,"再出栈两个元素");
    LinkStackPop(&stack);
    LinkStackPrint(stack,"再出栈一个元素");
}

void TestGetTop()
{
    SHOW_NAME;
    LinkStack* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
    LinkStackPush(&stack,'c');
    LinkStackPush(&stack,'d');
    LinkStackPrint(stack,"入栈四个元素");
    int ret = 0;
    LinkStackType top;
    ret = LinkStackGetTop(stack,&top);
    if(ret == 1)
        printf("取得栈顶元素为 %c\n",top);
    else
        printf("未取得栈顶元素\n");
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrint(stack,"出栈两个元素");
    ret = LinkStackGetTop(stack,&top);
    if(ret == 1)
        printf("取得栈顶元素为 %c\n",top);
    else
        printf("未取得栈顶元素\n");
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrint(stack,"再出栈两个元素");
    ret = LinkStackGetTop(stack,&top);
    if(ret == 1)
        printf("取得栈顶元素为 %d\n",top);
    else
        printf("未取得栈顶元素\n");
}

void TestDestroy()
{
    SHOW_NAME;
    LinkStack* stack;
    LinkStackInit(&stack);
    //LinkStackPush(&stack,'a');
    //LinkStackPush(&stack,'b');
    //LinkStackPush(&stack,'c');
    //LinkStackPush(&stack,'d');
    //LinkStackPush(&stack,'e');
    //LinkStackPrint(stack,"入栈五个元素");
    LinkStackDestroy(&stack);
}

int main()
{
    TestInit();
    TestPush();
    TestPop();
    TestGetTop();
    TestDestroy();
    return 0;
}
