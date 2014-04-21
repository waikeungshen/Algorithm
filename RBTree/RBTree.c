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

RBTree *T;    /* 根节点 */

/************函数声明***************************/
/* 祖父节点 */
RBNode *grandparent(RBNode *n);
/* 叔叔节点 */
RBNode *uncle(RBNode *n);
/* 兄弟节点 */
RBNode *brother(RBNode *n);
/* 查找函数 */
RBNode *search(int key);
/* 最小值 */
RBNode *minnum(RBTree *T);
/* 最大值 */
RBNode *maxnum(RBTree *T);
/* 创建一个新节点 */
RBNode *newNode(int t);
/* 插入z */
void RBinsert(int n);
/* 插入后修复RBTree性质 */
void RBInsertFixup(RBNode *z);
/* 删除函数 */
void RBdelete(RBNode *delNode);
/* 删除后修复RBTree性质 */
void RBDeleteFixup(RBNode *x);
/* 删除树 */
void DeleteTree(RBTree *T);
/* node节点的后继 */
RBNode *successor(RBNode *node);
/* 中序遍历打印 */
void printRBTree(RBTree *T);
/* 左旋转 */
void LeftRotate(RBNode *x);
/* 右旋转 */
void RightRotate(RBNode *y);

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
RBNode *search(int key)
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
void RBinsert(int n)
{
    /* 创建节点 */
    RBNode *z = newNode(n);

    RBNode *parentP = nil;
    RBNode *p = T;

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
        T = z;   //树为空时
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
    RBInsertFixup(z);
    printf("%d插入ok\n",n);
}

/* 插入后修复RBTree性质 */
void RBInsertFixup(RBNode *z)
{
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
                    LeftRotate(z);
                }
                else    /* case 3 */
                {
                    z->parent->color = BLACK;
                    grandparent(z)->color = RED;
                    RightRotate(grandparent(z));
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
                    RightRotate(z);
                }
                else
                {
                    z->parent->color = BLACK;
                    grandparent(z)->color = RED;
                    LeftRotate(grandparent(z));
                }

            }
        }
    }
    T->color = BLACK;  //根为黑色
}

/* 删除函数 */
void RBdelete(RBNode *delNode)
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
        T = childNode;
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
        RBDeleteFixup(childNode);

    /* 删除realDelNode */
    free(realDelNode);
}
/* 删除后修复RBTree性质 */
void RBDeleteFixup(RBNode *x)
{

}

/* 删除树 */
void DeleteTree(RBTree *T)
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
void printRBTree(RBTree *t)
{
    if (t != nil)
    {
        printRBTree(t->left);
        printf("KEY:%d COLOR:", t->key);
        if (t->color == RED)
            printf("Red\n");
        else
            printf("Black\n");
        printRBTree(t->right);
    }
}

/* 左旋转 */
void LeftRotate(RBNode *x)
{
    RBNode *y = x->right;
    x->right = y->left;
    //if (y->left != nil)
    y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

/* 右旋转 */
void RightRotate(RBNode *y)
{
    RBNode *x = y->left;
    y->left = x->right;
    //if (x->right != nil)
    x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nil)
        T = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

int main()
{
    /* 哨兵 */
    nil = makeNIL();
    T = nil;    /* 根节点 */

    RBinsert(5);
    RBinsert(6);
    RBinsert(3);
    RBinsert(2);
    RBinsert(8);
    RBinsert(9);
    RBinsert(4);
    RBinsert(1);
    RBinsert(7);
    RBinsert(0);

    printRBTree(T);
    /* 释放树的空间 */
    DeleteTree(T);
    /* 释放哨兵的空间 */
    free(nil);
    return 0;
}
