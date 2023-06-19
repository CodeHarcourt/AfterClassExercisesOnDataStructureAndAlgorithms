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

void InitLinkList(LinkList *L){
    *L=(LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;//这里必须要在*L左右两边加括号，优先级的问题必须要考虑
}//初始化链表操作

void CreateFromHead(LinkList L){
    Node*s;
    ElemType c;
    int flag=1;//标志，初值为1，当输入$时，flag为0，建表结束
    while(flag){
        c=getchar();
        if(c!='$'){
            s=(Node*)malloc(sizeof(Node));
            s->elem=c;
            s->next=L->next;//插入第一个结点时，L->next为空
            L->next=s;
        }else flag=0;
    }
}//头插法建立单链表

void CreatFromTail(LinkList L){
    Node* p;
    Node* r;
    ElemType e;
    int flag=1;
    r=L;//r指针始终指向链表的表尾
    while(flag){//标志，初值为1，当输入$时，flag为0，建表结束
        e=getchar();
        if(e!='$'){
            p=(Node*)malloc(sizeof(Node));
            p->elem=e;
            p->next=NULL;//设置尾节点为NULL
            r->next=p;
            r=r->next;
        }else flag=0;
    }
}//尾插法建立单链表

int ListLength(LinkList L){
    int length=0;//计数
    Node* p;
    p=L;
    p=p->next;  //获得首元素结点（第一个结点）
    while(p->next !=NULL){
        length++;
        p=p->next;
    }
    return length;
}//求单链表的长度

Node* GetData(LinkList L,int i){//如果找到，返回指向该结点的指针，否则返回NULL
    Node* p;
    p=L->next;//从第一个结点开始扫描
    int j=1;
    if(i<1||i> ListLength(L)) return NULL;//这里的i为要寻找的结点序号
    while(p!=NULL){
        if(i==j) return p;//找到了序号为i的结点
        p=p->next;//扫描下一个结点
        j++;//下一个被扫描的节点所在序号
    }
}//在单链表L中查找第i个结点

Node* Locate(LinkList L,ElemType e){
    Node* p;
    p=L->next;//获得第一个结点
    while(p!=NULL){
        if(p->elem==e) break;//找到结点值为e的结点
        p=p->next;
    }
    return p;
}//在单链表L中查找值为k的结点

int InsList(LinkList L,ElemType e,int i){
    if(i<1||i>(ListLength(L)+1)) return False;//先判断该序号的有效性
    Node* pre;
    Node* p;
    p=(Node*)malloc(sizeof(Node));
    p->elem=e;
    pre=L;//从头结点开始进行查找
    int j=0;
    while(pre!=NULL){//while的循环控制条件需要注意
        if(j==(i-1)){//当j==i-1时表示已经找到了第i个结点的前一个结点
            p->next=pre->next;
            pre->next=p;
        }
        pre=pre->next;
        j++;
    }
    return True;
}//单链表中插入单个节点的操作

int DelList(LinkList L,ElemType* e,int i){
    Node* pre;
    Node* R;
    pre=L->next;
    int j=1;
    if(i<1||i> ListLength(L)){
        printf("删除节点位置不合理");
        return False;
    }
    while(pre!=NULL){
        if((i-1)==j){
            *e=pre->next->elem;
            R=pre->next;//R指向当前待删除的结点
            pre->next=pre->next->next;
            free(R);//注意：删除结点的时候一定要将结点所在内存空间释放掉！！！
            return True;
        }
        pre=pre->next;
        j++;
    }
}//单链表删除，在带头结点的单链表L中删除第i个元素，并保存其值到变量*e中

LinkList MergeLinkList(LinkList LA,LinkList LB){
    LinkList LC;
    LC=LA;//新创建的链表复用LA的头结点
    Node* pA;
    Node* pB;
    Node* pC;
    pA=LA->next;
    pB=LB->next;
    pC=LC;
    pC->next=NULL;//LC初始化为一个空链表
    while(pA!=NULL&&pB!=NULL){
        if(pA->elem<=pB->elem){
            pC->next=pA;
            pA=pA->next;
            pC=pC->next;//LC的新链尾，尾插法复用LA和LB的结点不断更新链尾
        }else{
            pC->next=pB;
            pB=pB->next;
            pC=pC->next;
        }
    }
    if(pA==NULL&&pB!=NULL) pC->next=pB;//若表LA未完，将后续节点链到表LC的表尾
    if(pA!=NULL&&pB!=NULL) pC->next=pA;//否则将表LB中后续结点链到表LC表尾
    free(LB);
    return LC;
}//合并两个递增的的有序单链表，且要求使用表LA和LB中现有的节点空间来建新表LC