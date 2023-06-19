#include<stdio.h>
#include"限定性线性表--队列(链队列).c"
#define True 0
#define False -1
typedef int KeyType;
typedef char OtherType;
typedef struct{
    KeyType key;//用于比较的关键字
    OtherType other_data;//存储的其他数据
}RecordType;//单个记录内部存储数据的结构

