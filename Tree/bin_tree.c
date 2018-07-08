#include "bin_tree.h"
#include "seqqueue.c"
#include "seqstack.c"

void TreeInit(TreeNode** proot)//初始化
{
    if(proot == NULL)//非法输入
        return;
    *proot = NULL;
    return;
}

TreeNode* CreateTreeNode(TreeNodeType value)//创造一个新结点
{
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

void DestroyTreeNode(TreeNode* node)//销毁结点
{
    free(node);
    return;
}

void TreePreOrder(TreeNode* root)//先序遍历
{//根左右
    //树为空也是遍历结束的条件
    if(root == NULL)//空树
    {
        printf("[%c] ",'#');
        return;
    }
    //访问根结点
    printf("[%c] ",root->data);
    //递归访问左子树
    TreePreOrder(root->lchild);
    //递归访问右子树
    TreePreOrder(root->rchild);
    return;
}

void TreeInOrder(TreeNode* root)//中序遍历
{//左根右
    //树为空也是遍历结束的条件
    if(root == NULL)//空树
        return;
    //递归访问左子树
    TreeInOrder(root->lchild);
    //访问根结点
    printf("[%c] ",root->data);
    //递归访问右子树
    TreeInOrder(root->rchild);
    return;
}

void TreePostOrder(TreeNode* root)//后序遍历
{//左右根
    //树为空也是遍历结束的条件
    if(root == NULL)//空树
        return;
    //递归访问左子树
    TreePostOrder(root->lchild);
    //递归访问右子树
    TreePostOrder(root->rchild);
    //访问根结点
    printf("[%c] ",root->data);
    return;
}

void TreeLevelOrder(TreeNode* root)//层序遍历
{//1.建一个队列，若根结点非空，先将根结点入队
//2.打印当前队列的首元素结点的data值，并将其出队
//3.若刚刚出队元素的左/右子树不为空，就将其入列，再重复23步骤，直至队列为空即遍历结束
    //树空也作为遍历结束的条件
    if(root == NULL)//空树
        return;
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,root);
    while(1)
    {
        SeqQueueType front;
        int ret = SeqQueueGetFront(&queue,&front);
        //队首元素为空说明遍历结束
        if(ret == 0)
            break;
        //访问当前元素结点，并打印其值
        printf("[%c] ",front->data);
        //将当前结点出队
        SeqQueuePop(&queue);
        //将当前结点的左右子树（若非空）则入队
        if(front->lchild != NULL)
            SeqQueuePush(&queue,front->lchild);
        if(front->rchild != NULL)
            SeqQueuePush(&queue,front->rchild);
    }
    printf("\n");
    return;
}

TreeNode* _TreeCreate(TreeNodeType data[],size_t size,size_t* index,TreeNodeType null_node)//真正实现构建二叉树的代码
{
    if(index == NULL)//非法输入
        return NULL;
    if(*index >= size)//访问数组越界
        return NULL;
    if(data[*index] == null_node)//当前是空子树
        return NULL;
    TreeNode* new_node = CreateTreeNode(data[*index]);//2.
    ++(*index);//3.
    new_node->lchild = _TreeCreate(data,size,index,null_node);
    ++(*index);//4.
    new_node->rchild = _TreeCreate(data,size,index,null_node);
    return new_node;//返回当前子树的根结点
}

TreeNode* TreeCreate(TreeNodeType data[],size_t size,TreeNodeType null_node)//根据数组所给内容构建一颗二叉树
{//数组所给内容（这里给的是先序遍历结果）包括空子树，即参数null_node所代表的，第二个参数size表示树的大小
    //1.index用来标记当前元素为数组的哪个元素的下标
    //2.根据index所指内容创建一个结点
    //3.先++index，然后递归构建新结点的左子树
    //4.再++index,然后构建新结点的右子树
    size_t index = 0;
    return _TreeCreate(data,size,&index,null_node);
}

TreeNode* TreeClone(TreeNode* root)//树的深拷贝
{
    if(root == NULL)//空树
        return NULL;
    //按先序来拷贝
    TreeNode* new_node = CreateTreeNode(root->data);
    new_node->lchild = TreeClone(root->lchild);
    new_node->rchild = TreeClone(root->rchild);
    return new_node;
}

void TreeDestroy1(TreeNode** root)//树的销毁1
{//基于后序来遍历销毁，防止根结点销毁之后找不到子树，造成没有全部销毁
    if(root == NULL)//非法输入
        return;
    if(*root == NULL)//空树
        return;
    TreeDestroy1(&((*root)->lchild));
    TreeDestroy1(&((*root)->rchild));
    DestroyTreeNode(*root);
    *root = NULL;
    return;
}

void TreeDestroy2(TreeNode** root)//树的销毁2
{//基于先序来遍历销毁，在销毁当前子树的根结点时，先保存左右子树，避免找不到而没删除
    if(root == NULL)//非法输入
        return;
    if(*root == NULL)//空树
        return;
    TreeNode* lchild = (*root)->lchild;
    TreeNode* rchild = (*root)->rchild;
    DestroyTreeNode(*root);
    TreeDestroy2(&lchild);
    TreeDestroy2(&rchild);
    *root = NULL;
    return;
}

void _TreeSize(TreeNode* root,size_t* size)//真正用来计算树的结点
{
    if(root == NULL)//空树
        return;
    ++(*size);
    _TreeSize(root->lchild,size);
    _TreeSize(root->rchild,size);
}

size_t TreeSize(TreeNode* root)//求树的结点(不计算空结点)
{//用一个计数器，依次遍历结点，不为空就加1
    size_t size = 0;
    _TreeSize(root,&size);
    return size;
}

size_t TreeSize1(TreeNode* root)//求树的结点
{//根结点加左右子树的结点树
    if(root == NULL)//空树
        return 0;
    return 1+TreeSize(root->lchild)+TreeSize(root->rchild);
}

size_t TreeLeafSize(TreeNode* root)//求叶子结点的个数
{//左子树的叶子结点和右子树的叶子结点的和
    if(root == NULL)//空树
        return 0;
    //当前结点是叶子结点
    if(root->lchild == NULL && root->rchild == NULL)
        return 1;
    //当前结点不是叶子结点
    return TreeLeafSize(root->lchild) + TreeLeafSize(root->rchild);
}

size_t TreeKlevelSize(TreeNode* root,int K)//求第K层结点的个数(这里从第一层开始数)
{//求树的第K层结点数即求树的第K-1层结点子树的第一层结点数之和
    if(root == NULL || K < 1)//非法输入
        return 0;
    if(K == 1)
        return 1;
    return TreeKlevelSize(root->lchild,K-1)+TreeKlevelSize(root->rchild,K-1);
}

size_t TreeHeight(TreeNode* root)//求树的高度
{//根结点左右子树的高度较高者加1
    if(root == NULL)
        return 0;
    //当前结点无子树
    if(root->lchild==NULL && root->rchild==NULL)
        return 1;
    //当前结点有子树
    size_t lchild = TreeHeight(root->lchild);
    size_t rchild = TreeHeight(root->rchild);
    return 1+(lchild > rchild ? lchild : rchild);
}

TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find)//查找结点
{//给出一个数值，求对应结点的指针（假设无重复的数值结点)
    if(root == NULL)
        return NULL;
    //按照先序遍历访问
    if(root->data == to_find)
        return root;
    TreeNode* lresult = TreeFind(root->lchild,to_find);
    TreeNode* rresult = TreeFind(root->rchild,to_find);
    return lresult != NULL ? lresult :rresult;
}

TreeNode* Parent(TreeNode* root,TreeNode* child)//求结点的父结点
{
    if(root == NULL || child == NULL)//非法输入
        return NULL;
    //当前结点的左或右子树是输入参数孩子结点
    if(root->lchild==child || root->rchild==child)
        return root;
    TreeNode* lresult = Parent(root->lchild,child);
    TreeNode* rresult = Parent(root->rchild,child);
    return lresult != NULL ? lresult : rresult;
}

TreeNode* Lchild(TreeNode* root)//求当前结点的左子树
{
    if(root == NULL)
        return NULL;
    return root->lchild;
}

TreeNode* Rchild(TreeNode* root)//求当前结点的右子树
{
    if(root == NULL)
        return NULL;
    return root->rchild;
}

////////////////////////////////////////////////////
////////         以下为常见面试题           ////////
////////////////////////////////////////////////////
void TreePreOrderByLoop(TreeNode* root)//1.非递归先序遍历
{//利用栈辅助实现
    if(root == NULL)
        return;
    //1.先将根结点入栈
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,root);
    //2.循环开始
    while(1)
    {
        //取栈顶元素为当前元素
        TreeNode* cur = NULL;
        int ret = SeqStackGetTop(&stack,&cur);
        //栈空代表遍历结束
        if(ret == 0)
            break;
        //出栈当前元素，并访问当前元素
        SeqStackPop(&stack);
        printf("[%c] ",cur->data);
        //把当前元素的右子树入栈，再将当前元素的左子树入栈（为空不入栈）
        if(cur->rchild != NULL)
            SeqStackPush(&stack,cur->rchild);
        if(cur->lchild != NULL)
            SeqStackPush(&stack,cur->lchild);
    }
    printf("\n");
}

void TestPreOrderByLoop()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrderByLoop(new_node);
}

void TreeInOrderByLoop(TreeNode* root)//2.非递归中序遍历
{//利用栈辅助实现
    if(root == NULL)
        return;
    SeqStack stack;
    SeqStackInit(&stack);
    //1.定义cur指针，指向根节点，根节点不为空时，将根节点入栈，且cur=cur->lchild
    TreeNode* cur = root;
    //2.循环开始
    while(1)
    {
        //直至左子树为空时才结束循环，因为中序遍历是先访问左子树
        while(cur != NULL)
        {
            SeqStackPush(&stack,cur);
            cur = cur->lchild;
        }
        //取栈顶元素为当前元素
        TreeNode* top = NULL;
        int ret = SeqStackGetTop(&stack,&top);
        //栈空表示访问结束
        if(ret == 0)
            break;
        //访问当前元素，并出栈
        printf("[%c] ",top->data);
        SeqStackPop(&stack);
        //3.让cur指向栈顶元素的右子树，重复2的判断过程
        cur = top->rchild;
    }
    printf("\n");
}

void TestInOrderByLoop()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreeInOrderByLoop(new_node);
}

void TreePostOrderByLoop(TreeNode* root)//3.非递归后序遍历
{//利用栈辅助实现
    if(root == NULL)
        return;
    SeqStack stack;
    SeqStackInit(&stack);
    //1.定义cur指针，指向根节点，根节点不为空时，将根节点入栈，且cur=cur->lchild
    TreeNode* cur = root;
    TreeNode* pre = NULL;//用来保存上一个访问的元素
    //2.循环开始
    while(1)
    {
        //直至左子树为空时才结束循环，因为中序遍历是先访问左子树
        while(cur != NULL)
        {
            SeqStackPush(&stack,cur);
            cur = cur->lchild;
        }
        //取栈顶元素为当前元素
        TreeNode* top = NULL;
        int ret = SeqStackGetTop(&stack,&top);
        //栈空表示访问结束
        if(ret == 0)
            break;
        //判断当前元素，若当前元素的右子树为空或刚刚已访问过，则可以访问当前元素并出栈
        if(top->rchild==NULL || top->rchild==pre)
        {
            printf("[%c] ",top->data);
            SeqStackPop(&stack);
            //要注意更新pre指针
            pre = top;
        }
        //3.当前元素不符合刚刚判断当前元素的规则，则让cur指向栈顶元素的右子树，重复2的判断过程
        else
            cur = top->rchild;
    }
    printf("\n");
}

void TestPostOrderByLoop()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePostOrderByLoop(new_node);
}

void Swap(TreeNode** a, TreeNode** b)//4.树的镜像实现的交换函数
{
    TreeNode* tmp = *a;
    *a = *b;
    *b = tmp;
}

void TreeMirror1(TreeNode* root)//树的镜像(方法1)
{//树的镜像即将树对称的画出来，即左右子树都交换
    if(root == NULL)
        return;
    //访问动作即交换左右子树
    Swap(&root->lchild,&root->rchild);
    TreeMirror1(root->lchild);
    TreeMirror1(root->rchild);
    return;
}

void TreeMirror2(TreeNode* root)//树的镜像(方法2)
{//层序遍历、利用队列实现
    if(root == NULL)
        return;
    SeqQueue q;
    SeqQueueInit(&q);
    //1.将根节点入队
    SeqQueuePush(&q,root);
    TreeNode* front = NULL;
    //2.循环开始，若当前队首元素不为空，交换当前元素的左右子树并出队
    while(SeqQueueGetFront(&q,&front))
    {
        //此处的访问即交换左右子树
        Swap(&front->lchild,&front->rchild);
        SeqQueuePop(&q);
        //3.若当前元素的左右子树不为空，则入队，继续循环判断
        if(front->lchild != NULL)
            SeqQueuePush(&q,front->lchild);
        if(front->rchild != NULL)
            SeqQueuePush(&q,front->rchild);
    }
    return;
}

void TestMirror()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrderByLoop(new_node);
    TreeMirror1(new_node);
    TreePreOrderByLoop(new_node);
    TreeMirror2(new_node);
    TreePreOrderByLoop(new_node);
}

int IsCompleteTree(TreeNode* root)//5.判断当前树是否为完全二叉树
{
    if(root == NULL)//空树
        return 0;
    SeqQueue q;
    SeqQueueInit(&q);
    SeqQueuePush(&q,root);
    int if_start_step_two_flag = 0;//是否开始第二阶段的标志
    TreeNode* cur = NULL;
    while(SeqQueueGetFront(&q,&cur))
    {
        SeqQueuePop(&q);
        //一.第一阶段
        if(if_start_step_two_flag == 0)
        {
            //1.当前结点同时具有左右子树，将左右子树入队
            if(cur->lchild!=NULL && cur->rchild!=NULL)
            {
                SeqQueuePush(&q,cur->lchild);
                SeqQueuePush(&q,cur->rchild);
            }
            //2.当前结点只有右子树，但无左子树，说明不是完全二叉树，直接返回
            else if(cur->lchild==NULL && cur->rchild!=NULL)
            {
                return 0;
            }
            //3.当前结点只有左子树无右子树，将左子树入队，进入第二阶段
            else if(cur->lchild!=NULL && cur->rchild==NULL)
            {
                if_start_step_two_flag = 1;
                SeqQueuePush(&q,cur->lchild);
            }
            //4.当前结点无左右子树，进入第二阶段
            else
            {
                if_start_step_two_flag = 1;
            }
        }

        //二.第二阶段
        else
        {
            //任何一个结点都应该没有子树，否则不是完全二叉树
            if(cur->lchild==NULL && cur->rchild==NULL)
                ;
            else
                return 0;
        }
    }
    //所有条件都满足，时一个完全二叉树
    return 1;
}

void TestIsCompleteTree()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    int ret = IsCompleteTree(new_node);
    printf("expected is 0, actual is %d\n",ret);
    TreeNode* root1;
    TreeInit(&root1);
    TreeNodeType data1[] = "abd##e##cf###";
    size_t size1 = sizeof(data1) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node1 = '#';
    TreeNode* new_node1 = TreeCreate(data1,size1,null_node1);
    int ret1 = IsCompleteTree(new_node1);
    printf("expected is 1, actual is %d\n",ret1);
}

size_t Find(TreeNodeType arr[], size_t left, size_t right, TreeNodeType to_find)//6.还原一棵树的查找当前结点在中序序列中的位置
{
    size_t i = 0;
    for(i=left; i<right; i++)
    {
        if(arr[i] == to_find)
            return i;
    }
    return -1;
}

TreeNode* _TreeReBulid(TreeNodeType pre_order[], size_t pre_order_size, size_t* pre_order_index,\
        TreeNodeType in_order[], size_t in_order_left, size_t in_order_right)//真正还原一棵树的代码
{
    if(in_order_left >= in_order_right)//无效区间
        return NULL;
    if(pre_order_index == NULL)//非法输入
        return NULL;
    if(*pre_order_index >= pre_order_size)//遍历结束
        return NULL;
    //根据先序遍历结果取出当前值，基于该值构建一个结点
    TreeNode* new_node = CreateTreeNode(pre_order[*pre_order_index]);
    //查找当前结点在中序遍历序列中的位置
    size_t cur_root_in_order_index = Find(in_order,in_order_left,in_order_right,new_node->data);
    //避免找不到当前结点在中序序列中的位置
    assert(cur_root_in_order_index != (size_t)-1);
    //左子树区间 [in_order_left, cur_root_in_order_index);
    //右子树区间 [cur_root_in_order_index+1, in_order_right);
    ++(*pre_order_index);
    new_node->lchild = _TreeReBulid(pre_order, pre_order_size, pre_order_index, in_order, in_order_left,cur_root_in_order_index);
    new_node->rchild = _TreeReBulid(pre_order, pre_order_size, pre_order_index, in_order, cur_root_in_order_index+1, in_order_right);
    return new_node;
}

TreeNode* TreeReBulid(TreeNodeType pre_order[], TreeNodeType in_order[], size_t size)//给定先序和中序遍历结果，还原一棵树
{
    size_t pre_order_index = 0;
    //前闭后开区间,用来表示对当前子树中序遍历的结果
    size_t in_order_left = 0;
    size_t in_order_right = size;
    return _TreeReBulid(pre_order,size,&pre_order_index,in_order,in_order_left,in_order_right);
}

void TestReBuild()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType pre_order[] = "abdegcf";
    TreeNodeType in_order[] = "dbgeacf";
    size_t size = sizeof(pre_order) - 1;//这里用sizeof比strlen效率高一点
    TreeNode* new_node = TreeReBulid(pre_order, in_order, size);
    printf("pre_order# %s\n", pre_order);
    TreePreOrderByLoop(new_node);
    printf("in_order# %s\n", in_order);
    TreeInOrderByLoop(new_node);
}

////////////////////////////////////////////////////
////////         以下为测试代码             ////////
////////////////////////////////////////////////////


void TestInit()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    printf("expected is nil,extual is %p\n",root);
}

void TestPreOrder()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNode* new_node = CreateTreeNode('a');
    root = new_node;
    TreeNode* node1 = CreateTreeNode('b');
    root->lchild = node1;
    TreeNode* node2 = CreateTreeNode('c');
    root->rchild = node2;
    TreeNode* node3 = CreateTreeNode('d');
    node1->rchild = node3;
    TreeNode* node4 = CreateTreeNode('e');
    node2->lchild = node4;
    TreePreOrder(root);
    printf("\n");
}

void TestInOrder()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNode* new_node = CreateTreeNode('a');
    root = new_node;
    TreeNode* node1 = CreateTreeNode('b');
    root->lchild = node1;
    TreeNode* node2 = CreateTreeNode('c');
    root->rchild = node2;
    TreeNode* node3 = CreateTreeNode('d');
    node1->rchild = node3;
    TreeNode* node4 = CreateTreeNode('e');
    node2->lchild = node4;
    TreeInOrder(root);
    printf("\n");
}

void TestPostOrder()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNode* new_node = CreateTreeNode('a');
    root = new_node;
    TreeNode* node1 = CreateTreeNode('b');
    root->lchild = node1;
    TreeNode* node2 = CreateTreeNode('c');
    root->rchild = node2;
    TreeNode* node3 = CreateTreeNode('d');
    node1->rchild = node3;
    TreeNode* node4 = CreateTreeNode('e');
    node2->lchild = node4;
    TreePostOrder(root);
    printf("\n");
}

void TestLevelOrder()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNode* new_node = CreateTreeNode('a');
    root = new_node;
    TreeNode* node1 = CreateTreeNode('b');
    root->lchild = node1;
    TreeNode* node2 = CreateTreeNode('c');
    root->rchild = node2;
    TreeNode* node3 = CreateTreeNode('d');
    node1->rchild = node3;
    TreeNode* node4 = CreateTreeNode('e');
    node2->lchild = node4;
    TreeLevelOrder(root);
    printf("\n");
}

void TestCreate()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = strlen(data);
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
}

void TestClone()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    TreeNode* cp = TreeClone(new_node);
    TreePreOrder(cp);
    printf("\n");
}

void TestDestroy()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = strlen(data);
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    //TreeDestroy1(&new_node);
    TreeDestroy2(&new_node);
    TreePreOrder(new_node);//这里遍历出来会打印一个#号，因为我们的先序遍历将空子树也表示出来了
    printf("\n");
}

void TestSize()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    size_t ret = TreeSize(new_node);
    printf("size is %d\n",ret);
    size_t ret1 = TreeSize1(new_node);
    printf("size is %d\n",ret1);
}

void TestLeafSize()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    size_t ret = TreeLeafSize(new_node);
    printf("size is %d\n",ret);
    //size_t ret1 = TreeSize1(new_node);
    //printf("size is %d\n",ret1);
}

void TestKlevelSize()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    int K = 3;
    size_t ret = TreeKlevelSize(new_node,K);
    printf("expected is 3,actual is %d\n",ret);
}

void TestHeight()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    size_t ret = TreeHeight(new_node);
    printf("expected is 4,actual is %d\n",ret);
}

void TestFind()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    TreeNode* result = TreeFind(new_node,'e');
    printf("expected is e,find is %c\n",*result);
}

void TestParent()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    TreeNode* child = new_node->lchild->rchild->lchild;
    TreeNode* result = Parent(new_node,child);
    printf("expected is e,find is %c\n",result->data);
}

void TestLRchild()
{
    SHOW_NAME;
    TreeNode* root;
    TreeInit(&root);
    TreeNodeType data[] = "abd##eg###c#f##";
    size_t size = sizeof(data) - 1;//这里用sizeof比strlen效率高一点
    TreeNodeType null_node = '#';
    TreeNode* new_node = TreeCreate(data,size,null_node);
    TreePreOrder(new_node);
    printf("\n");
    TreeNode* ret = new_node->rchild;
    TreeNode* result1 = Lchild(ret);
    TreeNode* result2 = Rchild(ret);
    printf("lchild: expected is NULL,find is %p\n",result1);
    printf("rchild: expected is f,find is %c\n",result2->data);
}

int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    TestCreate();
    TestClone();
    TestDestroy();
    TestSize();
    TestLeafSize();
    TestKlevelSize();
    TestHeight();
    TestFind();
    TestParent();
    TestLRchild();
    
    TestPreOrderByLoop();
    TestInOrderByLoop();
    TestPostOrderByLoop();
    TestMirror();
    TestIsCompleteTree();
    TestReBuild();
    return 0;
}
