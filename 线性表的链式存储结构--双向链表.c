#include<stdio.h>
#include<malloc.h>

#define ElemType int
#define False -1
#define True 0

typedef struct node{
    ElemType elem;
    struct node* pre;//前驱指针域
    struct node* next;//后继指针域
}DNode,*DoubleList;

int DLinkIns(DoubleList L,int i,ElemType e){
    DNode* p;
    p=L;
    DNode* new;
    new=(DNode*)malloc(sizeof(DNode));
    new->elem=e;
    int j=0;
//中间可以加一步，判断插入位置的合法性
    while(p!=NULL){//定位，若位置i合法，则让指针p指向它
        if(j==i){//当找到要求的插入位置之后，执行插入操作
            p->pre->next=new;
            new->pre=p->pre;
            p->pre=new;
            new->next=p;
            return True;
        }
        p=p->next;
        j++;
    }return False;
}//双向链表的插入操作

int DLinkDel(DoubleList L,int i,ElemType* e){
    int j=0;
    DNode* p;
    p=L;
    while(p!=NULL){//查找需要删除的位置的结点
        if(i==j) break;
        p=p->next;
        j++;
    }
    if(i==j){//当位置合理，且找到该位置后p指针指向该位置，并进行如下操作实现删除结点
        *e=p->elem;
        p->next->pre=p->pre;
        p->pre->next=p->next;
        free(p);
        return True;
    }else return False;
}//双向链表的删除操作