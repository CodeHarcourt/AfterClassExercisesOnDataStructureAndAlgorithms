//以下数据结构的算法是针对于所有的树
#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1
#define ElemType char
#define MAXSIZE 100

typedef struct Node{
    ElemType data;//结点内部存储的数据
    int parent;//双亲结点的序号下标
}TNode;

typedef struct {
    TNode Tree[MAXSIZE];//整棵树用一维数组实现
    int nodeNum;//结点数目
}ParentTree;