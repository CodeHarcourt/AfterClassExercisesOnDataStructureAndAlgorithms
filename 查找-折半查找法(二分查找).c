///折半查找对查找列表的要求：1.必须采用顺序存储结构(数组)2.必须按关键字大小有序排列
#include<stdio.h>
#define LIST_SIZE 20
#define True 0
#define False -1

typedef int KeyType;
typedef char OtherType;
typedef struct {
    KeyType key;
    OtherType other_data;
}RecordType;
typedef struct{
    RecordType r[LIST_SIZE+1];//顺序表从下标1开始用
    int length;
}RecordList;

int BinSearch(RecordList* L,KeyType k){
//   在有序表L中折半查找其关键字等于k的元素，若找到，返回该元素在表中的位置
    int low=1,mid,high=L->length;
    while(low<=high){
        mid=(low+high)/2;
        if(low==high) return mid;
        else {
            if (L->r[mid].key > k)// 在前一子表查找
                high = mid - 1;
            if (L->r[mid].key < k)// 在后一子表进行查找
                low = mid + 1;
        }
    }
     return False;// 未找到
}//折半查找(二分查找)(logn)
///折半查找法适用于不需经常变动，但需频繁查找的有序列表。