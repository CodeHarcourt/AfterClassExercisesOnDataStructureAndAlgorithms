#include<stdio.h>
#define True 0
#define False -1
typedef int KeyType;
typedef char OtherType;
typedef struct{
    KeyType key;//用于比较的关键字
    OtherType other_data;//存储的其他数据
}RecordType;//单个记录内部存储数据的结构

void SelectSort(RecordType r[],int n){
//    对记录数组r做简单选择排序，n为数组的长度
    int min;
    for(int i=1;i<=n-1;i++){// 进行n-1趟比较
        min=i;
        for(int j=i+1;j<=n;j++)// 从n-i+1个记录中找最小关键字的记录的位置
            if(r[j].key<r[min].key)
                min=j;
        if(min!=i){// i和k相等时不交换
            r[0]=r[min];
            r[min]=r[i];
            r[i]=r[0];
        }
    }
}//简单选择排序(不稳定)

void RebuildHeap(RecordType r[],int k,int n){
// 假设ｒ[k..m]是以ｒ[k]为根的完全二叉树，且分别以ｒ[2k]和ｒ[2k+1]为根的左、右子树。
// 逐步向下筛，使整个序列r[k..m]满足大根堆的性质
    RecordType temp;
    temp=r[k];// 暂存“根”记录r[k]
    int i=k;// 子树的根结点
    int j=2*i;// 该子树根结点的左孩子
    int Finish=False;
    while(j<=n&&Finish==False){
        if(j<n&&r[j].key<r[j+1].key)
            // 若存在右子树，且它的根的关键字较左子树更大，则沿右分支“筛选”，
            // 否则沿左分支“筛选”。
            j=j+1;
        if(temp.key>r[j].key)// 待调整记录的关键字不小于左右子树的关键字时
            Finish=True;
        else{
            r[i]=r[j];
            i=j;// 进入下一层子树继续筛选
            j=2*i;
        }
    }
    r[i]=temp;// r[k]填入到恰当的位置
}//堆排序(重建堆算法)

void crt_Heap(RecordType r[],int n){
    // 对记录数组r建堆，n为总的结点数
    for(int i=n/2;i>=1;i--){// 自第n/2个记录开始进行筛选建堆(归纳法证明)
        RebuildHeap(r,i,n);
    }
}//建初堆，从n/2的位置开始，对每一棵子树进行重建堆操作

void HeapSort(RecordType r[],int n){
    // 以大根堆按升序排列为例，对r[1..n]进行堆排序，排序完成后r元素从小到大
    int HeapTail;
    RecordType temp;
    crt_Heap(r,n);// 建立初始大根堆
    for(int i=1;i<=n;i++){
        temp=r[n-i+1];// 将堆顶元素r[1]与堆尾元素r[n-i+1]互换
        r[n-i+1]=r[1];
        r[1]=temp;//将当前序列最大元素放到应该在的位置r[n-i+1]
        RebuildHeap(r,1,n-i);// 剩余元素r[1..n-i]重建堆
    }
}//完整堆排序算法
