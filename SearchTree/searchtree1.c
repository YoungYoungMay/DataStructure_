//实现二叉搜索树,非递归版本
#include "searchtree.h"

//1.初始化
void SearchTreeInit(SearchNode** proot)//初始化
{
    if(proot == NULL)//非法输入
        return;
    *proot = NULL;//用空指针初始化
    return;
}

//2.销毁（递归实现）
void SearchNodeDestroy(SearchNode* node)//销毁结点
{
    free(node);
}

void SearchTreeDestroy(SearchNode** proot)//销毁树
{
    if(proot == NULL)//非法操作
        return;
    if(*proot == NULL)//空树
        return;
    SearchNode* root = *proot;
    SearchTreeDestroy(&root->lchild);
    SearchTreeDestroy(&root->rchild);
    SearchNodeDestroy(root);
    *proot = NULL;
    return;
}

//3.打印函数(这里是先序遍历)
void SearchTreePrint(SearchNode* root)//打印函数，用于测试
{
    if(root == NULL)//空树,也是递归遍历结束条件
        return;
    SearchNode* cur = root;
    printf("[%c] ", root->data);
    SearchTreePrint(cur->lchild);
    SearchTreePrint(cur->rchild);
    return;
}

//4.插入结点(非递归实现)
//注意这里不能指定位置插入，因为要保证插入之后依旧满足二叉搜索树的定义
SearchNode* CreateSearchNode(SearchNodeType value)//创建一个结点
{
    SearchNode* new_node = (SearchNode*)malloc(sizeof(SearchNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

void SearchTreeInsert(SearchNode** proot, SearchNodeType to_insert)//插入一个元素
{
    if(proot == NULL)//非法输入
        return;
    //1.空树->直接插入指针所指位置
    if(*proot == NULL)//空树，也是插入位置
    {
        SearchNode* new_node = CreateSearchNode(to_insert);
        *proot = new_node;
        return;
    }
    //2.非空树->寻找插入位置
    SearchNode* pre = NULL;//记录父结点
    SearchNode* cur = *proot;//记录当前结点
    while(1)
    {
        //当前结点为空，可插入
        if(cur == NULL)
            break;
        //向左子树寻找
        if(to_insert < cur->data)
        {
            pre = cur;
            cur = cur->lchild;
        }
        //向右子树寻找
        else if(to_insert > cur->data)
        {
            pre = cur;
            cur = cur->rchild;
        }
        //有相同元素，按照约定，直接返回，插入失败
        else
        {
            return;
        }
    }
    //3.当前cur所指即为可插入位置，下面插入元素
    //这里要注意当前可插入位置为父结点的左子树还是右子树
    SearchNode* new_node = CreateSearchNode(to_insert);
    //插入左子树
    if(to_insert < pre->data)
    {
        pre->lchild = new_node;
    }
    if(to_insert > pre->data)
    {
        pre->rchild = new_node;
    }
    return;
}

//5.查找结点(非递归)：给定一个值，查找对应结点
SearchNode* SearchTreeFind(SearchNode* root, SearchNodeType to_find)//查找指定值结点
{
    if(root == NULL)//空树
        return NULL;
    SearchNode* cur = root;
    while(1)
    {
        //没找到
        if(cur == NULL)
            break;
        if(to_find < cur->data)
        {
            cur = cur->lchild;
        }
        else if(to_find > cur->data)
        {
            cur = cur->rchild;
        }
        else
        {
            break;
        }
    }
    return cur;
}

//6.删除结点(递归)：给定一个值，删除对应结点
//这里不用担心有相同元素，我们约定该二叉搜索树中不存在相同元素
void SearchTreeRemove(SearchNode** proot, SearchNodeType to_remove)//删除指定值结点
{
    if(proot == NULL)//非法输入
        return;
    if(*proot == NULL)//空树
        return;
    //1.查找要删除的结点
    SearchNode* root = *proot;
    SearchNode* pre = NULL;
    while(1)
    {
        //没找到
        if(root == NULL)
            return;
        if(to_remove < root->data)
        {
            pre = root;
            root = root->lchild;
        }
        else if(to_remove > root->data)
        {
            pre = root;
            root = root->rchild;
        }
        else
            break;
    }
    //2.当前root所指元素即为要删除的元素
    //(1)要删除的结点无左右子树
    if(root->lchild == NULL && root->rchild == NULL)
    {
        //要删除的元素为整个二叉搜索树的根节点
        if(root == *proot)
        {
            *proot = NULL;
        }
        else
        {
            //删除结点为父结点的左子树
            if(to_remove <  pre->data)
                pre->lchild = NULL;
            else
                pre->rchild = NULL;
        } 
        SearchNodeDestroy(root);
    }
    //(2)要删除的结点仅有左子树
    if(root->lchild != NULL && root->rchild == NULL)
    {
        //要删除的元素为整个二叉搜索树的根节点
        if(root == *proot)
        {
            *proot = root->lchild;
        }
        else
        {
            //删除结点为父结点的左子树
            if(to_remove <  pre->data)
                pre->lchild = root->lchild;
            //要删除结点为父结点的右子树
            else
                pre->rchild = root->lchild;
        } 
        //统一释放
        SearchNodeDestroy(root);
    }
    //(3)要删除的结点仅有右子树
    if(root->lchild == NULL && root->rchild != NULL)
    {
        //要删除的元素为整个二叉搜索树的根节点
        if(root == *proot)
        {
            *proot = root->rchild;
        }
        else
        {
            //删除结点为父结点的左子树
            if(to_remove <  pre->data)
                pre->lchild = root->rchild;
            //要删除结点为父结点的右子树
            else
                pre->rchild = root->rchild;
        } 
        //统一释放
        SearchNodeDestroy(root);
    }
    //(4)要删除的结点左右子树均在
    if(root->lchild != NULL && root->rchild != NULL)
    {
        //查找要删除结点的右子树的最小值
        SearchNode* min = root->rchild;
        SearchNode* min_pre = root;
        while(min->lchild != NULL)
        {
            min_pre = min;
            min = min->lchild;
        }
        //用最小值覆盖要删除结点的值
        root->data = min->data;
        //删除释放
        //这里不管min所指结点的右子树是否为空，都将其指向它的右子树,因为走到这里，min不可能有左子树
        if(min->data < min_pre->data)
            min_pre->lchild = min->rchild;
        else
            min_pre->rchild = min->rchild;
        SearchNodeDestroy(min);
    }
}


///////////////////////////////////////////////////////
////////////         以下为测试代码       ////////////
///////////////////////////////////////////////////////


void TestInsert()
{
    SHOW_NAME;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root, 'd');
    SearchTreeInsert(&root, 'g');
    SearchTreeInsert(&root, 'a');
    SearchTreeInsert(&root, 'r');
    SearchTreeInsert(&root, 'b');
    SearchTreeInsert(&root, 'k');
    SearchTreePrint(root);
    printf("\n");
}

void TestFind()
{
    SHOW_NAME;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root, 'd');
    SearchTreeInsert(&root, 'g');
    SearchTreeInsert(&root, 'a');
    SearchTreeInsert(&root, 'r');
    SearchTreeInsert(&root, 'b');
    SearchTreeInsert(&root, 'k');
    SearchTreePrint(root);
    printf("\n");
    SearchNode* ret = SearchTreeFind(root, 'r');
    printf("expected is r, actual is %c\n", ret->data);
    ret = SearchTreeFind(root, 'h');
    printf("expected is nil, actual is %p\n", ret);
}

void TestRemove()
{
    SHOW_NAME;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root, 'd');
    SearchTreeInsert(&root, 'g');
    SearchTreeInsert(&root, 'a');
    SearchTreeInsert(&root, 'r');
    SearchTreeInsert(&root, 'b');
    SearchTreeInsert(&root, 'k');
    SearchTreePrint(root);
    printf("\n");
    //仅有左子树
    SearchTreeRemove(&root, 'r');
    SearchTreePrint(root);

    //仅有右子树
    //SearchTreeRemove(&root, 'g');
    //SearchTreePrint(root);
    
    //无子树
    //SearchTreeRemove(&root, 'k');
    //SearchTreePrint(root);
    
    //左右子树均在
    //SearchTreeRemove(&root, 'd');
    //SearchTreePrint(root);
    printf("\n");
}


int main()
{
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
