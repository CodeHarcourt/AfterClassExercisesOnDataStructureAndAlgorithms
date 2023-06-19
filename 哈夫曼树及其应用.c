///完全二叉树的路径长度最小，但这是充分不必要条件
///且每个结点从1(根)开始进行编号后的路径长度为log2K向下取整
///而整个树的路径长度就是对每个结点的路径长度求和


#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define True 0
#define False -1
#define ElemType int
#define N 20//叶子结点数目的最大值
#define M 2*N-1//所有结点的数目

typedef struct Node{
    ElemType data;//结点的权值
    int parent;//结点的双亲结点
    int LChild;//结点的左孩子结点
    int RChild;//结点的右孩子结点
}HTNode,HuffmanTree[M+1];//下标0未使用

typedef char* HuffmanCode[N+1];

void select(HuffmanTree ht,int n,int* s1,int *s2){
//    在ht[1]到ht[n]的范围内选择两个结点权值最小，且双亲结点为0的结点，并将下标序号赋值给s1,s2
    int min;
    int i;
    int temp;
    for(i=1;i<=n;i++){//寻找第一个双亲结点为0的结点，并将其位置序号赋值给min
        if(ht[i].parent==0){
            min=i;
            i=n+1;
        }
    }
    for(i=min;i<=n;i++){//寻找结点权值最小的，且双亲结点为0的结点
        if(ht[i].data<ht[min].data){
            if(ht[i].parent==0) min=i;
        }
    }
    *s1=min;
    for(i=1;i<=n;i++){//寻找第一个双亲结点为0的结点，并将其位置序号赋值给min,并且不是*s1位置的结点
        if(ht[i].parent==0&&i!=*s1){
            min=i;
            i=n+1;
        }
    }
    for(i=min;i<=n;i++){//寻找结点权值最小的，且双亲结点为0的结点,并且不是*s1位置的结点
        if(ht[i].data<ht[min].data){
            if(ht[i].parent==0&&i!=*s1) min=i;
        }
    }
    *s2=min;
    if(ht[*s1].data==ht[*s2].data&&(*s1)>(*s2)){
        temp=*s1;
        *s1=*s2;
        *s2=temp;
    }
}//在ht[1]到ht[n]的范围内选择两个结点权值最小，且双亲结点为0的结点

void CrtHuffmanTree(HuffmanTree ht,int*w,int n){//n为叶子结点数目
//    w是一个数组，存放已知的n个权值，构造哈夫曼树ht[M+1]
    int m;
    int i;
    int s1,s2;
    m=2*n-1;
    for(i=1;i<=n;i++){//1到n号单元存放叶子结点
        ht[i].data=w[i];
        ht[i].parent=0;
        ht[i].LChild=0;
        ht[i].RChild=0;
    }
    for(i=n+1;i<=2*n-1;i++){//n+1到2*n-1存放分支节点，创建出的非叶子结点，构造哈夫曼树
        select(ht,i-1,&s1,&s2);
        ht[s1].parent=i;
        ht[s2].parent=i;
        ht[i].data=ht[s1].data+ht[s2].data;
        ht[i].RChild=s2;
        ht[i].LChild=s1;
    }
}//创建哈夫曼树的算法

//哈夫曼编码：对一颗具有n个叶结点的哈夫曼树，若将向左分支记为1，向右分支记为0（也可以左0右1）
//则从根到每个叶结点的通路上，各分支构成的二进制串就称为哈夫曼编码。
//哈夫曼编码也被称作最优前缀编码
//前缀编码：一个编码系统中的任何一个编码都不是其它编码的前缀（最左子串）。

void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc,int n){
//    从叶结点到根，逆向求每个叶结点对应的哈夫曼编码，n为叶结点的数目
    char* temp;
    int p;
    int start;
    temp=(char*)malloc(n*sizeof(char));//分配当前编码的工作空间
    temp[n-1]='\0';//从右向左依次存放编码，首先存放编码结束符
    for(int j=1;j<=n;j++) {//求n个叶子结点对应的哈夫曼编码
        start=n-2;//初始化编码指示器
        p=ht[j].parent;
        while(p!=0){
            if(ht[p].LChild==j) temp[start]='1';//左分支为1
            else temp[start]='0';//右分支为0
            --start;
            p=ht[p].parent;
        }
        hc[j]=(char*)malloc((n-start)*sizeof(char));//为第i叶结点的编码分配空间
        strcpy(hc[j],&temp[start]);
    }
    free(temp);
}//求哈夫曼树的哈夫曼编码算法

