//树的孩子兄弟表示法，也叫做树的二叉链表表示法
#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1
#define ElemType char
#define MAXSIZE 100

typedef struct Node{
    ElemType data;//结点的数据信息
    struct Node* FirstChild;//该节点的第一个孩子结点
    struct Node* NextSibling;//该节点的下一个兄弟节点
}CSNode,*CSTree;

void visit(ElemType data){
    ;
}//访问结点数据域的操作，待补充

///森林的先序遍历和树的先根遍历与其转化所得二叉树的先序遍历所得顺序一致
///森林的后序遍历与其转化所得二叉树的后序遍历所得顺序一致
///森林的中序遍历与树的后根遍历与其转化所得二叉树的中序遍历所得顺序一致
void RootFirst(CSTree root){
    if(root!=NULL){
        visit(root->data);//访问根结点
        RootFirst(root->FirstChild);//遍历左子树
        RootFirst(root->NextSibling);//遍历下一个以兄弟结点为根的子树
    }
}//基于孩子兄弟表示法的树的先根遍历(方法一)

void rootFirst(CSTree root){
    CSNode* p;
    if(root!=NULL){
        visit(root->data);//访问根结点的数据域
        while(root->FirstChild!=NULL){
            p=root->FirstChild;
            rootFirst(p);//访问以p为根的子树
            p=root->NextSibling;
        }
    }
}//基于孩子兄弟表示法的树的先根遍历(方法二)
