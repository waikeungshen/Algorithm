/*************************************************************************
    * File Name: RBTree.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Thu 10 Apr 2014 18:57:41 CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define RED     1
#define BLACK   0

typedef struct RBNode
{
    int key;                // 值
    int color;              // 颜色
    struct RBNode *left;    // 左孩子
    struct RBNode *right;    // 右孩子
    struct RBNode *parent;    // 父节点
}RBTree, RBNode;

/* 哨兵节点 */
RBNode *nil;
RBNode *makeNIL()
{
    RBNode *p = malloc(sizeof(RBNode));
    p->color = BLACK;
    p->key = 0;
    p->left = p->right = p->parent = NULL;
    return p;
}

/************函数声明***************************/
/* 祖父节点 */
RBNode *grandparent(RBNode *n);
/* 叔叔节点 */
RBNode *uncle(RBNode *n);
/* 兄弟节点 */
RBNode *brother(RBNode *n);
/* 查找函数 */
RBNode *search(RBTree *T, int key);
/* 最小值 */
RBNode *minnum(RBTree *T);
/* 最大值 */
RBNode *maxnum(RBTree *T);
/* 创建一个新节点 */
RBNode *newNode(int t);
/* 插入z */
void RBinsert(RBNode **T, int n);
/* 插入后修复RBTree性质 */
void RBInsertFixup(RBNode **T, RBNode *z);
/* 删除函数 */
void RBdelete(RBTree **T, RBNode *delNode);
/* 删除后修复RBTree性质 */
void RBDeleteFixup(RBNode **T, RBNode *x);
/* 删除树 */
void DeleteTree(RBNode *T);
/* node节点的后继 */
RBNode *successor(RBNode *node);
/* 中序遍历打印 */
void printRBTree(RBTree *T);
/* 左旋转 */
void LeftRotate(RBTree **T, RBNode *x);
/* 右旋转 */
void RightRotate(RBTree **T, RBNode *y);


void insert_case1(RBNode **T, RBNode *n);
void insert_case2(RBNode **T, RBNode *n);
void insert_case3(RBNode **T, RBNode *n);
void insert_case4(RBNode **T, RBNode *n);
void insert_case5(RBNode **T, RBNode *n);
/***********************************************/

/* 祖父节点 */
RBNode *grandparent(RBNode *n)
{
    return n->parent->parent;
}

/* 叔叔节点 */
RBNode *uncle(RBNode *n)
{
    if (n->parent == grandparent(n)->left)
        return grandparent(n)->right;
    else
        return grandparent(n)->left;
}

/* 兄弟节点 */
RBNode *brother(RBNode *n)
{
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

/* 查找函数 */
RBNode *search(RBTree *T, int key)
{
    RBNode *p = T;
    if (p && key != p->key)
    {
        if (key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    return p;
}

/* 最小值 */
RBNode *minnum(RBTree *T)
{
    RBNode *p = T;
    while (p->left != NULL)
        p = p->left;
    return p;
}

/* 最大值 */
RBNode *maxnum(RBTree *T)
{
    RBNode *p = T;
    while (p->right != NULL)
        p = p->right;
    return p;
}

/* 创建一个新节点 */
RBNode *newNode(int t)
{
    RBNode *p = malloc(sizeof(RBNode));
    p->key = t;
    p->color = RED;
    p->left = p->right = p->parent = NULL;
    return p;
}

/* 插入z */
void RBinsert(RBNode **T, int n)
{
    /* 创建节点 */
    RBNode *z = newNode(n);

    RBNode *parentP = nil;
    RBNode *p = *T;

    /* 确定插入位置 */
    while (p != nil)   // p到达叶子节点
    {
        parentP = p;
        if (z->key < p->key)
            p = p->left;
        else
            p = p->right;
    }

    /* z的父节点 */
    z->parent = parentP;

    /* 插入节点 */
    if (parentP == nil)
        *T = z;   //树为空时
    else
    {
        if (z->key < parentP->key)
            parentP->left = z;
        else
            parentP->right = z;
    }
    z->color = RED;
    z->left = nil;
    z->right = nil;
    //RBInsertFixup(T, z);
    printf("%d插入ok\n",n);
}

/* 插入后修复RBTree性质 */
void RBInsertFixup(RBNode **T, RBNode *z)
{
    //insert_case1(T, z);
    while (z->parent->color == RED)
    {
        if (z->parent == grandparent(z)->left)  /* z的双亲是其祖父的左节点 */
        {
            if (uncle(z) != nil && uncle(z)->color == RED)  /* z的父节点，z的叔叔节点都为红色 */    /*case 1 */
            {
                z->parent->color = BLACK;
                uncle(z)->color = BLACK;
                grandparent(z)->color = RED;
                z = grandparent(z);
            }
            else
            {
                if (z == z->parent->right)   /* case 2 */
                {
                    z = z->parent;
                    LeftRotate(T, z);
                }
                else    /* case 3 */
                {
                    z->parent->color = BLACK;
                    grandparent(z)->color = RED;
                    RightRotate(T, grandparent(z));
                }
            }
        }
        else
        {
            if (uncle(z) != nil && uncle(z)->color == RED)
            {
                z->parent->color = BLACK;
                uncle(z)->color = BLACK;
                grandparent(z)->color = RED;
                z = grandparent(z);
            }
            else
            {
                if (z == z->parent->left )
                {
                    z = z->parent;
                    LeftRotate(T, z);
                }
                else
                {
                    z->parent->color = BLACK;
                    grandparent(z)->color = RED;
                    RightRotate(T, grandparent(z));
                }

            }
        }
    }
    *T->color = BLACK;  //根为黑色
}

/* 新节点n位于树的根上，没有父节点 */
void insert_case1(RBNode **T, RBNode *n)
{
    if (n->parent == nil)
        n->color = BLACK;
    else
        insert_case2(T, n);
}

/* 新节点的父节点P是黑色 */
void insert_case2(RBNode **T, RBNode *n)
{
    if (n->parent->color == BLACK)
        return;
    else
        insert_case3(T, n);
}

/* 父节点P、叔叔节点U都为红色 */
void insert_case3(RBNode **T, RBNode *n)
{
    if (uncle(n) != nil && uncle(n)->color == RED)
    {
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandparent(n)->color = RED;
        insert_case1(T, grandparent(n));
    }
    else
        insert_case4(T, n);
}

/* 父节点P是红色，叔叔节点U是黑色或nil */
void insert_case4(RBNode **T, RBNode *n)
{
    /* 插入节点n是其父节点P的右孩子，而父节点P又是其父节点的左孩子 */
    if(n == n->parent->right && n->parent == grandparent(n)->left)
    {
        LeftRotate(T, n->parent);
        n = n->left;
    }
    else if (n == n->parent->left && n->parent == grandparent(n)->right)
    {
        RightRotate(T, n->parent);
        n = n->right;
    }
    insert_case5(T, n);
}

/* 父节点P是红色，而叔叔节点U是黑色或nil */
void insert_case5(RBNode **T, RBNode *n)
{
    n->parent->color = BLACK;
    grandparent(n)->color = RED;
    if (n == n->parent->left && n->parent == grandparent(n)->left)
    {
        RightRotate(T, grandparent(n));
    }
    else
    {
        /* 反情况，n是其父节点的右孩子，而父节点P又是其父节点G的右孩子 */
        LeftRotate(T, grandparent(n));
    }
}

/* 删除函数 */
void RBdelete(RBTree **T, RBNode *delNode)
{
    /*1. 确定实际要删除的结点是Z还是Z的后继。*/
    RBNode *realDelNode;
    if (delNode->left && delNode->right)
        realDelNode = successor(delNode);
    else
        realDelNode = delNode;

    /*2. 实际删除结点的孩子，Z的左/右孩子或者后继的右孩子。*/
    RBNode *childNode;
    if (realDelNode->left)
        childNode = realDelNode->left;
    else
        childNode = realDelNode->right;

    /*3. 将实际要删除结点的父结点与其孩子关联。*/
    childNode->parent = realDelNode->parent;

    if (realDelNode->parent == nil)
        *T = childNode;
    else if (realDelNode == realDelNode->parent->left)
        realDelNode->parent->left = childNode;  
    else  
        realDelNode->parent->right = childNode; 

    /*4. 如果实际删除的是后继，则把后继中的数据拷贝到Z，替换它。*/
    if (realDelNode != delNode)
    {
        delNode->key = realDelNode->key;
    }
    
    if (realDelNode->color == BLACK)
        RBDeleteFixup(T, childNode);

    /* 删除realDelNode */
    free(realDelNode);
}
/* 删除后修复RBTree性质 */
void RBDeleteFixup(RBNode **T, RBNode *x)
{

}

/* 删除树 */
void DeleteTree(RBNode *T)
{
    if (T != nil)
    {
        DeleteTree(T->left);
        DeleteTree(T->right);
        free(T);
    }
}

/* node节点的后继 */
RBNode *successor(RBNode *node)
{
    /* node的右子树非空，那么后继就是右子树的最小值 */
    if (node->right != NULL)
        return minnum(node->right);
    /* 如果右子树为空 */
    RBNode *y = node->parent;
    while (y != NULL && node == y->right)
    {
        node = y;
        y = y->parent;
    }
    return y;
}

/* 中序遍历打印 */
void printRBTree(RBTree *T)
{
    if (T != nil)
    {
        printRBTree(T->left);
        printf("KEY:%d COLOR:", T->key);
        if (T->color == RED)
            printf("Red\n");
        else
            printf("Black\n");
        printRBTree(T->right);
    }
}

/* 左旋转 */
void LeftRotate(RBTree **T, RBNode *x)
{
    RBNode *y = x->right;
    x->right = y->left;
    y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        *T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

/* 右旋转 */
void RightRotate(RBTree **T, RBNode *y)
{
    RBNode *x = y->left;
    y->right = x->right;
    x->parent = y->parent;
    if (y->parent == nil)
        *T = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

int main()
{
    /* 哨兵 */
    nil = makeNIL();
    RBTree *T = nil;

    RBinsert(&T, 5);
    RBinsert(&T, 6);
    RBinsert(&T, 3);
    RBinsert(&T, 2);
    RBinsert(&T, 8);
    RBinsert(&T, 9);
    RBinsert(&T, 4);
    RBinsert(&T, 1);
    RBinsert(&T, 7);
    RBinsert(&T, 0);

    printRBTree(T);
    /* 释放树的空间 */
    DeleteTree(T);
    /* 释放哨兵的空间 */
    free(nil);
    return 0;
}
