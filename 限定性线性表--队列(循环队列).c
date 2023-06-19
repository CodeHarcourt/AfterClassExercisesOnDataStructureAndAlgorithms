//循环队列判断栈为满时有以下两种方法：
//1.浪费一个元素空间，当（rear+1）% MAXSIZE == front时，队列已满
//2.不浪费队列中的元素空间，增设一个标志变量，比如tag，用来区别队列是“空”还是“满”
#include<stdio.h>
#define MAXSIZE 50//队列的最大长度
#define True 0
#define False -1
#define ElemType int

typedef struct{
    ElemType elem[MAXSIZE];//队列的元素空间
    int front;//队列头的数组下标
    int rear;//队列尾的数组下标
}SeqQueue;

void InitQueue(SeqQueue* Q){
//    将*Q初始化为一个空的循环队列
    Q->front=Q->rear=0;
}//循环队列初始化

int EnterQueue(SeqQueue* Q,ElemType e){
//    将元素e入队
    if(((Q->rear+1)%MAXSIZE)==Q->front){
        printf("队列已满，无法执行入队操作");
        return False;
    }else{
        Q->elem[Q->rear]=e;
        Q->rear=((Q->rear+1)%MAXSIZE);//更新队尾
        return True;
    }return False;
}//循环队列入队

int DeleteQueue(SeqQueue* Q,ElemType*e){
//    删除队列的队头元素，通过e输出其值
    if(Q->rear==Q->front){
        printf("队列为空，无法执行出队操作");
        return False;
    }else{
        *e=Q->elem[Q->front];
        Q->front=((Q->front+1)%MAXSIZE);//更新队头
        return True;
    }return False;
}