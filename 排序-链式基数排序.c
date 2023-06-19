#include<stdio.h>
#include"限定性线性表--队列(链队列).c"
#define RADIX 10
#define KEY_SIZE 6
#define LIST_SIZE 20

typedef int KeyType;
typedef char OtherType;
typedef struct {
    KeyType keys[KEY_SIZE]; // 子关键字数组
    OtherType other_data; // 其它数据项
    int next; // 静态链域，是指针类型，是记录r中的下标
}RecordType;
typedef int PVector[RADIX]; // PVector是数组类型

void Collect(RecordType r[], PVector f, PVector e) {
// 从0到RADIX-1扫描各队列，将所有非空队列首尾相接，重新链接成一个链表
    int j, t; // 补充教材
    j = 0;
    while (f[j]==0) // 找第一个非空队列
        ++j;
    r[0].next = f[j];
    t = e[j];
    while (j<RADIX-1) { // 寻找并串接所有非空队列
        ++j;
        while ((j<RADIX-1) && (f[j]==0)) // 找下一个非空队列
            ++j;
        if (f[j]!=0) { // 链接非空队列
            r[t].next = f[j];
            t = e[j];
        }
    }
    r[t].next = 0; // t指向最后一个非空队列中的最后一个结点
}

void Distribute(RecordType r[], int i, PVector f, PVector e) {
// r中已按低位关键字key[i+1]，…，key[d]进行过“低位优先”排序。
// 按第i位关键字key[i]建立RADIX个队列，同一个队列中记录的key[i]相同。
// f[j]和e[j]分别指向各队列中第一个和最后一个记录(j=0,1,…,RADIX-1)。
// f[j]==0表示相应队列为空队列
    int j, p; // 补充教材
    for (j=0;j<=RADIX-1;++j)
        f[j] = 0; // 将RADIX个队列初始化为空队列
    p = r[0].next; // p指向链表中的第一个记录
    while(p!=0) {
        j = Order(r[p].keys[i]); // 用记录中第i位关键字求相应队列号
        if (f[j]==0)
            f[j] = p; // 将p加入第j个队列的第一个记录
        else
            r[e[j]].next = p; // 如果不是该队列的第一个记录，则在该队列中形成链表
        e[j] = p; // 更新队列j的最后一个记录
        p = r[p].next; // 获得下一个待分配的记录
    }
}

void RadixSort (RecordType r[], int n, int d) {
// n个记录存放在数组r中，执行本算法进行基数排序后，
// 链表中的记录按关键字从小到大的顺序相链接。
    int i; // 补充教材
    PVector head, tail; // 补充教材
    for (i=0; i<=n-1; ++i)
        r[i].next = i+1; // 构造静态链表, r[0]为头结点，r[1]为数组r第1个记录
    r[n].next = 0; // 数组r的第n个记录的next设置为0
    for (i=d-1;i>= 0;--i ) {
// 从最低位的子关键字开始，进行d趟分配和收集
        Distribute(r, i, head, tail); // 第i趟分配
        Collect(r, head, tail); // 第i趟收集
    }
}