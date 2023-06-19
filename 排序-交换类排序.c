#include<stdio.h>
#define True 0
#define False -1
typedef int KeyType;
typedef char OtherType;
typedef struct{
    KeyType key;//用于比较的关键字
    OtherType other_data;//存储的其他数据
}RecordType;//单个记录内部存储数据的结构

void BubbleSort(RecordType r[],int n){
    RecordType temp;
    int flag;
    flag=True;
    for(int i=1;i<=n-1&&flag==True;i++){
        flag=False;
        for(int j=1;j<=n-i;j++){//一趟冒泡
            if(r[j].key>r[j+1].key){
                temp=r[j+1];
                r[j+1]=r[j];
                r[j]=temp;
                flag=True;//有逆序数
            }
        }
    }
}//冒泡排序

void BubbleSortFromTail(RecordType r[],int n){
    RecordType temp;
    int flag=True;
    for(int i=n;i>=2&&flag==True;i--){
        flag=False;
        for(int j=n;j>=n-i+1;j--){
            if(r[j].key>r[j+1].key){
                temp=r[j+1];
                r[j+1]=r[j];
                r[j]=temp;
                flag=True;//有逆序
            }
        }
    }
}//向前冒泡排序

int QKPass(RecordType r[],int low,int high){
    //对记录数组r[low..high]进行一趟快速排序，得到基准记录的正确位置
    RecordType temp;
    temp=r[low];//选择基准记录
    while(low<high){
        while(r[high].key>=temp.key)// high从右到左找小于x.key的记录
            high--;
        if(low<high){
            r[low]=r[high];
            low++;
        }
        while(r[low].key<=temp.key)// low从左到右找大于等于x.key的记录
            low++;
        if(low<high){
            r[high]=r[low];
            high--;
        }
    }
    r[low]=temp;// 将基准记录保存到low==high的位置
    return low;// 基准记录的正确位置
}

void QKSort(RecordType r[],int low,int high){
    //对记录数组r[low..high]用快速排序算法进行排序
    int pos;
    if(low<high){
        pos= QKPass(r,low,high);//一趟快速排序，以枢轴元素为界划分为两个子表
        QKSort(r,low,pos-1);//对左部子表进行排序
        QKSort(r,pos+1,high);//对右部子表进行排序
    }
}//快速排序算法