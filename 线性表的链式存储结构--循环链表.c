#include<stdio.h>
#include<malloc.h>

#define ElemType int
#define False -1
#define True 0

typedef struct Node{
    ElemType elem;
    struct Node* next;
}Node,*LinkList;//LinkList为结构指针类型
//LinkList L;这种语句一般使用于声明头指针变量，指向头结点或者是第一个结点
//当声明指向其他节点的变量时 一般使用Node *p;
//注意，在循环单链表中一般会存在头结点，且以下程序均是在有头结点的情况下进行的操作
//但是尾指针是可有可无的存在

void InitCLinkList(LinkList* CL){
//    CL为待初始化的循环单链表的头指针的地址
    (*CL)=(LinkList)malloc(sizeof(Node));//建立头结点
    (*CL)->next=(*CL);//建立空的循环单链表
}//初始化循环单链表

void CreateCLinkList(LinkList CL){
    ElemType e;
    Node* p;
    Node* new;
    p=CL;
    e=getchar();
    while(e!='$'){//规定以输入的'$'作为输出结束标志
        new=(Node*)malloc(sizeof(Node));
        new->elem=e;
        p->next=new;
        p=p->next;
        e=getchar();
    }
    new->next=CL;//尾节点的next指向头节点，实现首尾相接
}//利用尾插法建立循环单链表

LinkList merge_1(LinkList LA,LinkList LB){
    Node* LAr;
    Node* LBr;
    Node* LC;
    LC=LA;
    LAr=LA->next;
    LBr=LB->next;
    while(LAr->next!=LA){
        LAr=LAr->next;//找到表LA的尾结点
    }
    while(LBr->next!=LA){
        LBr=LBr->next;//找到表LB的尾结点
    }
    LAr->next=LB->next;//修改表LA的尾指针，使之指向表LA的头结点
    LBr->next=LA;//修改表LB的尾指针，使之指向表LA的头结点
    free(LB);
    return LC;
}//循环单链表的合并算法（不设置尾指针，只有头结点）

LinkList merge_2(LinkList RA,LinkList RB){
    Node* p;
    p=RB->next;//保存RB的头结点信息，如果不保存的话无法形成一个环
    RB->next=RA->next->next;//将A链的第一个结点链到B链之后，为了形成一条B在前A在后的链
    free(RA->next);//释放掉LA的头结点，因为它被夹在两个链之间弃用了
    RA->next=p;//将A链的尾结点与B链的头结点相连，形成链环
    return RA;//返回A的尾结点
}//循环单链表的合成算法（设置尾指针，无需遍历寻找尾结点）