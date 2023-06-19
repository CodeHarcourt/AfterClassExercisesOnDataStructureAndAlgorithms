#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1

typedef int KeyType;
typedef struct node{
    KeyType key;
    struct node* LChild;
    struct node* RChild;
}BSTNode,*BSTree;

void InsertBST(BSTree* bst,KeyType key){
    // 若在二叉排序树中不存在关键字等于key的元素，插入该元素
    BSTree S;
    if(*bst==NULL){// 递归结束条件
        S=(BSTree)malloc(sizeof(BSTNode));// 申请新的结点s
        S->key=key;
        S->LChild=NULL;
        S->RChild=NULL;
        *bst=S;
    }else if((*bst)->key>key)
        InsertBST(&((*bst)->LChild),key);//将s插入左子树
    else if((*bst)->key<key)
        InsertBST(&((*bst)->RChild),key);//将s插入右子树
}//二叉排序树插入的递归算法

void CreateBSTree(BSTree* bst){
    // 从键盘输入元素的值，创建相应的二叉排序树
    KeyType key;
    *bst=NULL;
    scanf("%d",&key);
    while(key!=False){
        InsertBST(bst,key);
        scanf("%d",&key);
    }
}//创建二叉排序树

BSTree SearchBST(BSTree bst,KeyType key){
    // 在根指针bst所指二叉排序树中，递归查找某关键字等于key的元素
    if(!bst) return NULL;//未查找到该元素，返回空指针
    if(bst->key==key)//查找成功，返回地址
        return bst;
    else if(bst->key>key)
        return SearchBST(bst->LChild,key);//在左子树继续查找
    else
        return SearchBST(bst->RChild,key);//在右子树继续查找
}//二叉排序树查找的递归算法

BSTree ChangeSearchBST(BSTree bst,KeyType key){
    // 在根指针bst所指二叉排序树bst上，查找关键字等于key的结点，
    // 若查找成功，返回指向该元素结点指针，否则返回空指针。
    if(!bst) return NULL;
    BSTree p;
    p=bst;
    while(p!=NULL){
        if(p->key==key)
            return p;
        if(p->key>key)// 在左子树中查找
            p=p->LChild;
        if(p->key<key)
            p=p->RChild; // 在右子树中查找
    }
    return NULL;
}//二叉排序树的非递归算法
///二叉排序树适用于需经常变动的有序列表的查找。
