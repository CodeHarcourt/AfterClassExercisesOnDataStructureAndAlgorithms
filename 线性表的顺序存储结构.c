#include<stdio.h>
#define MAXSIZE 100//线性表的最大长度
#define False -1
#define True 0;
#define ElemType int
#define OrderNum int//数据元素的序号

typedef struct{
    ElemType elem[MAXSIZE];//线性表占用的数组空间
    int last;//记录数组elem[]最后一个元素的下标
}SeqList;
//当函数的形参要影响实参时要将元素设置为SeqList类型的结构指针变量：SeqList*L;
//注：线性表的元素序号要从1开始，与C语言数组下标有1的偏差

ElemType GetData(SeqList L,int i){
    if(i<0&&i>(L.last+1))
        return False;
    else return L.elem[i-1];
}//查找线性表L中的第i个元素

OrderNum Locate(SeqList L,int e){
    int i;
    for(i=0;i<(L.last+1);i++){
        if(L.elem[i]==e)
            return i+1;
    }
    return False;
}//顺序表的按元素内容查找元素序号的算法

int InsList(SeqList *L,int i,ElemType e){
    //i代表将要插入的序号位置，其大小在1<=i<=(L.last+1+1)
    int k;
    if(i<1||i>(L->last+1+1)) {//判断插入位置是否合法
        printf("插入位置i值不合法");
        return False;
    }
    if((L->last+1)==MAXSIZE){
        printf("该线性表已满，无法执行插入操作");
        return False;
    }
    for(k=L->last;k>=i-1;k--){
        L->elem[k+1]=L->elem[k];
    }
    L->elem[i-1]=e;//数组第i个元素的下标为i-1
    L->last++;
    return True;
}//线性表的插入操作，在第i个位置前插入一个元素

int Delete(SeqList *L,int i, ElemType *e){
    int k;
    if(i<1||i>(L->last+1)){
        printf("需要进行删除操作的元素不存在");
        return False;
    }
    *e=L->elem[i-1];
    for(k=i;k<(L->last+1);k++){
        L->elem[k-1]=L->elem[k];//将后面的元素依次向前移动
    }
    L->last--;
    return True;
}//线性表的删除操作，删除第i个位置上的元素

void mergeList(SeqList* L,SeqList A,SeqList B){
    int i=0,j=0,k=0;
    for(i,j,k;i<=A.last&&j<=B.last;){
        if(A.elem[i]<=B.elem[j]) {
            L->elem[k] = A.elem[i];
            k++;
            i++;
        }else{
            L->elem[k]=B.elem[j];
            k++;
            j++;
        }
    }
    if(i<A.last&&j==B.last){
        for(i;i<=A.last;i++){
            L->elem[k]=A.elem[i];
            i++;
            k++;
        }
    }else if(j<B.last&&i==A.last){
        for(j;j<=B.last;j++){
            L->elem[k]=B.elem[j];
            j++;
            k++;
        }
    }
    L->last=A.last+B.last+1;
}//对两个非递减有序的顺序表进行合并操作