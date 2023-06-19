#include<stdio.h>
typedef int KeyType;
typedef char OtherType;
typedef struct{
    KeyType key;//用于比较的关键字
    OtherType other_data;//存储的其他数据
}RecordType;//单个记录内部存储数据的结构

void InsSort(RecordType r[],int n){//对记录数组进行直接插入排序，n为数组的长度
    int j;
    for(int i=2;i<=n;i++){//比较插入第i个记录
        r[0]=r[i];//r[0]用于存放当前待插入的记录
        j=i-1;
        while(r[j].key>r[0].key){// r[0].key更小才移动，等于或大于都不动
            r[j+1]=r[j]; // 向后移动一个位置
            j--;// 继续向前查找
        }
        r[j+1]=r[0];
    }
}//直接插入排序(while循环体的控制条件保证该排序算法是稳定的)

void BinSort(RecordType r[],int n){
//    对记录数组r[1...length]进行折半插入排序，n为数组的长度
    int low,high,mid;
    for(int i=2;i<=n;i++){
        low=1;
        high=i-1;
        r[0]=r[i];
        while(high>=low){//确定插入的位置
            mid=(high+low)/2;
            if(r[mid].key>r[0].key)
                high=mid-1;
            if(r[mid].key<r[0].key)
                low=mid+1;
        }
        for(int j=i-1;j>=low;j--){
            r[j+1]=r[j];//记录依次向后移动
        }
        r[low]=r[0];//插入记录
    }
}//折半插入排序(稳定)
///个人理解：折半查找的优化在于对原有简单插入排序寻找插入位置时的依次查找插入进行优化，改为类似二分查找

void ShellInsert(RecordType r[],int n,int delta){
//    对n个记录数据的数组，按照增量为delta进行一次希尔排序
    int j;
    for(int i=1;i+delta<=n;i++){
//    i+delta为第i个子序列第二个元素的下标，即待插入的元素的下标
        if(r[i+delta].key<r[i].key){//相当于完成直接插入排序中的后移，寻找正确的插入位置
            r[0]=r[i+delta];//备份待插入的元素数据，这一步必不可少，如果没有，则会被后续后移操作覆盖
            for(j=i;j>0&&r[j].key>r[0].key;j-=delta)
                r[j+delta]=r[j];// 将r[j]移动到r[j+delta]位置
            r[j]=r[0];
        }
    }
}//增量为delta时的一趟希尔排序

void ShellSort(RecordType r[], int n, int delta[], int m) {
// 对数组r希尔排序，n为r的长度，delta为增量数组，m为数组delta的长度
    for (int i=0;i<=m-1;++i)
        ShellInsert(r, n, delta[i]);
}//希尔排序算法(不稳定)