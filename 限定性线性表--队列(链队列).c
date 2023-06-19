//采用带头结点的链表结构，并设置一个队头指针front和一个队尾指针rear
#include<stdio.h>
#include<malloc.h>
#define ElemType int
#define True 0
#define False -1

typedef struct Node{
    ElemType elem;
    struct Node* next;
}LinkQueueNode;

typedef struct{
    LinkQueueNode* front;
    LinkQueueNode* rear;
}LinkQueue;

int InitQueue(LinkQueue* Q){//将Q初始化为一个空的链队列
    Q->front=(LinkQueueNode*)malloc(sizeof(LinkQueueNode));
    if(Q->front!=NULL){
        Q->front->next=NULL;
        Q->rear=Q->front;//Q->front和Q->rear均指向头结点
        return True;
    }return False;
}//链队列初始化

int EnterQueue(LinkQueue* Q,ElemType e){
//    将数据元素e插入到队列Q中
    LinkQueueNode* new;
    new=(LinkQueueNode*)malloc(sizeof (LinkQueueNode));
    if(new!=NULL){
        new->elem=e;
        new->next=NULL;
        Q->rear->next=new;//新结点入队尾
        Q->rear=new;//更新rear，指向入队后新的队尾结点
        return True;
    }return False;
}//链队列入队

int DeleteQueue(LinkQueue* Q,ElemType* e){
//    将队列Q的队头元素出队，并存放到e所指向的存储空间
    if(Q->rear==Q->front){
        printf("链队列为空，无法执行出队操作");
        return False;
    }else{
        LinkQueueNode* p;
        p=Q->front->next;
        *e=p->elem;
        Q->front->next=p->next;//队头出队
        if(Q->rear==p) Q->rear=Q->front;
//        这一步很关键，很容易忽视，当队列中仅有一个结点的时候，在出队后，要将尾指针指向头结点，即将队列设置为空队列
        free(p);
        return True;
    }return False;
}