//以下数据结构的算法是针对于所有的树
#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1
#define ElemType char
#define MAXSIZE 100

typedef struct Node{//孩子链表结点的定义
    int child;//孩子结点在Tree数组中的下标
    struct Node* nextBro;//该孩子结点同双亲的兄弟节点，即孩子链的下一个结点
}ChildNode;

typedef struct PNode{//顺序表结点的定义
    ElemType data;//树中某个结点所存储的数据
    ChildNode* FirstChild;//该结点的第一个孩子结点，一般是孩子结点中从左数的第一个结点
}Node;

typedef struct{//树的定义
    Node Tree[MAXSIZE];//整棵树的定义(树的结点数组)
    int root;//根结点在树的结点数组中的位置
    int TNodeNum;//该树结点个数
}ChildTree;