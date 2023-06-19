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

///分块查找法将列表组织成两种索引顺序结构
//①首先将列表分成若干个块（子表）
//一般情况下，块的长度均匀，最后一块可以不满。每块中元素任意排列，即块内无序，但块与块之间有序。
//②构造一个索引表
//每个索引项对应一个块，并记录相应块的起始位置和该块中的最大关键字（或最小关键字）。索引表按关键字的大小有序排列。