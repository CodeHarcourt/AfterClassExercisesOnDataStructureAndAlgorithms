//注意：出栈的时候相当于删除了第一个结点，需要释放结点空间
//将指向头节点的头指针作为栈顶指针
#include<stdio.h>
#include<malloc.h>
#define ElemType int
#define False -1
#define True 0

typedef struct node{
    ElemType elem;
    struct node* next;
}Node,*LinkStack;

int Push(LinkStack Top,ElemType e){
//    将数据元素x压栈，栈顶为Top
    Node* new;
    new=(Node*)malloc(sizeof(Node));
    if(new==NULL){
        printf("栈已满，无法执行入栈操作");
        return False;//判断是否分配到可用的空间
    }else{
        new->elem=e;//这三部操作同头插法建立链表
        new->next=Top->next;
        Top->next=new;
        return True;
    }
}//链栈进栈

int Pop(LinkStack Top,ElemType* e){
//    将栈顶的元素弹出，放到x所指向的存储空间
    Node* p;
    if(Top->next==NULL){
        printf("栈为空，无法执行出栈操作");
        return False;
    }else{
        p=Top->next;
        *e=Top->next->elem;
        Top->next=Top->next->next;
        free(p);//释放存储空间
        return True;
    }
}//链栈出栈