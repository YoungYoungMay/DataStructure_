//二叉搜索树的头文件
#pragma once

#include <stdio.h>
#include <stdlib.h>

#define SHOW_NAME printf("\n==============%s=================\n", __FUNCTION__);

typedef char SearchNodeType;
//二叉搜索树结点
//二叉搜索树的左结点一定小于根结点，根结点一定小于右结点
typedef struct SearchNode
{
    SearchNodeType data;
    struct SearchNode* lchild;
    struct SearchNode* rchild;
}SearchNode;
