/*************************************************************************
    * File Name: binarySearchTree.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Sun 13 Apr 2014 14:36:39 CST
 ************************************************************************/

/* 二叉查找树，左孩子比父节点小，右孩子比父节点大 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BiNode
{
    int key;
    struct BiNode *left;
    struct BiNode *right;
    struct BiNode *parent;
} BiTree, BiNode;

/**************函数声明*********************/
/* 查找函数 */
BiNode *search(BiTree *T, int key);

/* 插入函数 */
void insert(BiTree **T, int key);

/* 删除函数 */
void delete(BiTree **T, BiNode *delNode);

/* 中序遍历 */
void printBSTree(BiTree *T);

/* 最小值 */
BiNode *minnum(BiTree *T);

/* 最大值 */
BiNode *maxnum(BiTree *T);

/* 删除树 */
void DeleteTree(BiTree *T);

/* node节点的后继 */
BiNode *successor(BiNode *node);

/****************声明结束*******************/

/* 查找函数 */
BiNode *search(BiTree *T, int key)
{
    BiNode *p = T;
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
BiNode *minnum(BiTree *T)
{
    BiNode *p = T;
    while (p->left != NULL)
        p = p->left;
    return p;
}

/* 最大值 */
BiNode *maxnum(BiTree *T)
{
    BiNode *p = T;
    while (p->right != NULL)
        p = p->right;
    return p;
}

/* 插入函数 */
void insert(BiTree **T, int key)
{
    /* 新建节点 */
    BiNode *newNode = malloc (sizeof(BiNode));
    newNode->left = newNode->right = NULL;
    newNode->key = key;

    /* 确定插入位置 */
    BiNode *p = *T;  /*遍历指针*/
    BiNode *parentP = NULL;  /* p的父节点 */
    while (p != NULL)
    {
        parentP = p;
        if (key < p->key)
            p = p->left;
        else
            p = p->right;
    }

    /* newNode的父节点 */
    newNode->parent = parentP;

    /* 插入节点 */
    if (parentP == NULL)
        *T = newNode;
    else if (key < parentP->key)
        parentP->left = newNode;
    else
        parentP->right = newNode;
}

/* 删除函数 */
void delete(BiTree **T, BiNode *delNode)
{
    /*1. 确定实际要删除的结点是Z还是Z的后继。*/
    BiNode *realDelNode;
    if (delNode->left && delNode->right)
        realDelNode = successor(delNode);
    else
        realDelNode = delNode;

    /*2. 实际删除结点的孩子，Z的左/右孩子或者后继的右孩子。*/
    BiNode *childNode;
    if (realDelNode->left)
        childNode = realDelNode->left;
    else
        childNode = realDelNode->right;

    /*3. 将实际要删除结点的父结点与其孩子关联。*/
    if (childNode)
        childNode->parent = realDelNode->parent;

    if (realDelNode->parent == NULL)
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
    
    /* 删除realDelNode */
    free(realDelNode);
}

/* 中序遍历 */
void printBSTree(BiTree *T)
{
    if (T != NULL)
    {
        printBSTree(T->left);
        printf("KEY:%d\n", T->key);
        printBSTree(T->right);
    }
}

/* node节点的后继 */
BiNode *successor(BiNode *node)
{
    /* node的右子树非空，那么后继就是右子树的最小值 */
    if (node->right != NULL)
        return minnum(node->right);
    /* 如果右子树为空 */
    BiNode *y = node->parent;
    while (y != NULL && node == y->right)
    {
        node = y;
        y = y->parent;
    }
    return y;
}

/* 删除树 */
void DeleteTree(BiTree *T)
{
    if (T != NULL)
    {
        DeleteTree(T->left);
        DeleteTree(T->right);
        free(T);
    }
}

int main()
{
    BiTree *T = NULL;

    insert(&T, 5);
    insert(&T, 6);
    insert(&T, 3);
    insert(&T, 2);
    insert(&T, 8);
    insert(&T, 9);
    insert(&T, 4);
    insert(&T, 1);
    insert(&T, 7);
    insert(&T, 0);

    printBSTree(T);

    BiNode *del = search(T, 5);
    printf("删除操作\n");
    delete(&T, del);

    printBSTree(T);

    DeleteTree(T);
    return 0;
}
