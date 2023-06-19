#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1
typedef int KeyType;
typedef char OtherType;
typedef struct{
    KeyType key;//用于比较的关键字
    OtherType other_data;//存储的其他数据
}RecordType;//单个记录内部存储数据的结构

///每次将2个有序子序列合并成一个有序子序列的方法称为2路归并排序。

void Merge(RecordType r[],int low,int mid,int high){
    ///类似有序线性表合并
// 已知r[low..mid]和r[mid+1..high]分别按关键字有序排列，
// 将它们合并成一个有序序列，存放在r[low..high]
    int i,j,k;
    RecordType* A=(RecordType*)malloc(sizeof(RecordType)*(high-low+1));
    for(i=low,j=mid+1,k=0;i<=mid&&j<=high&&k<=(high-low+1);){
        if(r[i].key<=r[j].key){//if条件句中只有是小于等于的时候才能使该算法成为稳定排序算法
            A[k]=r[i];
            i++;
            k++;
        }else{
            A[k]=r[j];
            j++;
            k++;
        }
    }
    if(i<=mid){// 如果r[low..mid]还有剩余
        for(i,k;i<=mid&&k<=high-low+1;i++,k++)
            A[k]=r[i];
    }
    if(j<=high){// 如果r[mid+1..high]还有剩余
        for(j,k;j<=high&&k<=high-low+1;j++,k++)
            A[k]=r[j];
    }
    for(i=low,k=0;i<=high;i++,k++)// 用A更新r
        r[i]=A[k];
    free(A);
}//相邻两个有序子序列的合并算法

void MergeSort(RecordType r[],int low,int high){
    int mid;
    if(low<high){
        mid=(low+high)/2;
        MergeSort(r,low,mid);
        MergeSort(r,mid+1,high);
        Merge(r,low,mid,high);
    }
}//2路归并的递归算法(稳定)