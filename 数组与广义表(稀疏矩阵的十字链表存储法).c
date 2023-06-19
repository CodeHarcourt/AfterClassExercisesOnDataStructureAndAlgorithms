#include<stdio.h>
#include<malloc.h>
#define ElemType int

typedef struct OLNode{
    int row;//非零元素的行下标
    int col;//非零元素的列下标
    ElemType value;
    struct OLNode* right;//非零元素所在行表的后继链域
    struct OLNode* down;//非零元素所在列表的后继链域
}OLNode,*OLink;

typedef struct{
    OLink* row_head;
    OLink* col_head;// 行、列链表的头指针数组
    int m;
    int n;
    int len;//稀疏矩阵的行数、列数、非零元素的个数
}CrossList;

void CreateCrossList(CrossList* M){
//    采用十字链表存储结构，创建稀疏矩阵M，约定输入row为0时结束
    int m,n,t;
    int i,j,e;
    OLNode* p,* q;
    scanf("%d%d%d",&m,&n,&t);//读入行、列和非零元素的个数
    M->m=m;
    M->n=n;
    M->len=t;
    if(!(M->row_head=(OLink*)malloc((m+1)*sizeof(OLink)))) exit(0);
    if(!(M->col_head=(OLink*)malloc((n+1)*sizeof(OLink)))) exit(0);
    for(i=0;i<=m;i++) M->row_head[i]=NULL;
    for(i=0;i<=n;i++) M->col_head[i]=NULL;
//    初始化各行、列链表为空的链表
    for(scanf("%d%d%d",&i,&j,&e);i!=0;scanf("%d%d%d",&i,&j,&e)){
        if(!(p=(OLNode*)malloc(sizeof(OLNode)))) exit(0);
        else{
            p->row=i;//生成结点
            p->col=j;
            p->value=e;
            p->down=NULL;
            p->right=NULL;
            if(M->row_head[p->row]==NULL) M->row_head[p->row]=p;//p成为row_head链上的第一个结点
            else{
                    if(M->row_head[p->row]->col>p->col){
                        p->right=M->row_head[p->row];
                        M->row_head[p->row]=p;
                    }else{
                        for(q=M->row_head[p->row];;q=q->right){
                            if(q->col<p->col&&q->right->col>p->col){
                                p->right=q->right;
                                q->right=p;
                            }
                        }
                    }
            }
            if(M->col_head[p->col]==NULL) M->col_head[p->col]=p;// p即将成为col_head链上第一个结点
            else{
                if(M->col_head[p->col]->row>p->row){
                    p->down=M->col_head[p->col];
                    M->col_head[p->col]=p;
                }else{
                    for(q=M->col_head[p->col];;q=q->down){
                        if(q->row<p->row&&q->down->row>p->row){
                            p->down=q->down;
                            q->down=p;
                        }
                    }
                }
            }
        }
    }
}