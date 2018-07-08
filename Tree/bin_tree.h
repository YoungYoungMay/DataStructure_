#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SHOW_NAME printf("\n=================%s=================\n",__FUNCTION__);

typedef char TreeNodeType;


typedef struct TreeNode//树的结点
{
    TreeNodeType data;//数据
    struct TreeNode* lchild;//左子树
    struct TreeNode* rchild;//右子树
}TreeNode;
