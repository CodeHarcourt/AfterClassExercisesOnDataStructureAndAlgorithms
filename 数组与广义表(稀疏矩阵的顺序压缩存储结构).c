#include<stdio.h>
#define False -1
#define True 0
#define ElemType int
#define M int//原矩阵的行数
#define N int//原矩阵的列数
#define MAXSIZE 1000//非零元素的个数最多为1000

typedef struct{
    int row;//非零元素的行下标，从1开始
    int col;//非零元素的列下标，从1开始
    ElemType value;//非零元素的值
}Triple;

typedef struct{
    Triple data[MAXSIZE+1];//非零元素的三元组表，data[0]未用
    int m;//矩阵的行数
    int n;//矩阵的列数
    int len;//矩阵中非零元素的个数
}TSMatrix;

void CreateMat(TSMatrix* T,ElemType A[M+1][N+1]){
    int i,j,k=1;
    T->m=M;
    T->n=N;
    T->len=0;
    for(i=1;i<=M;i++){
        for(j=1;j<=N;j++){
            if(A[i][j]!=0){//寻找原矩阵中不为0的元素位置以及其中存储的值
                T->len++;
                T->data[T->len].row=i;
                T->data[T->len].col=j;
                T->data[T->len].value=A[i][j];
            }
        }
    }
}//创建三元组表

int MyGetValue(TSMatrix* T,ElemType* e,int i,int j){
//    在三元组中如果找到指定的位置，将该元素的值赋值给e；否则e赋值为0
    if(i<0||i>T->m||j<0||j>T->n) return False;//先判断获取值的位置是否合理
    for(int k=1;k<=T->len;k++){
        if(T->data[k].row==i&&T->data[k].col==j){//直接对应的行和列
            *e=T->data[k].value;
            return True;
        }
    }
    *e=0;
    return False;
}//将矩阵中指定位置的元素值赋值给变量(自作)

void GetValue(TSMatrix* T,ElemType* e,int i,int j){
//      在三元组中如果找到指定的位置，将该元素的值赋值给e；否则e赋值为0
    int k=1;
    if(i<0||i>T->m||j<0||j>T->n) return ;//先判断获取值的位置是否合理
    while(k<T->len&&T->data[k].row<i) k++;//查找行
    while(k<T->len&&T->data[k].row==i&&T->data[k].col<j) k++;//查找列
    if(T->data[k].row==i&&T->data[k].col==j) *e=T->data[k].value;
    else *e=0;
    return ;
}//将矩阵中指定位置的元素值赋值给变量(教师标准代码)

int SetValue(TSMatrix* T,ElemType e,int i,int j){
    if(i<0||i>T->m||j<0||j>T->n) return False;
    for(int k=1;k<=T->len;k++) {//第一种情况，原稀疏矩阵该位置有元素，要将该元素的值改变，即重新赋值
        if (T->data[k].row == i && T->data[k].col == j)
            T->data[k].value = e;
        return True;
    }
    int k;
    while(T->data[k].row>=i&&T->data[k].col>=j) k++;
    T->len++;//在第二种情况下，矩阵中非零元素个数增加
    for(int i=T->len;i>=k;i--) {
    //第二种情况，原稀疏矩阵该位置无元素，要进行三元表数组的后移操作，腾出空间，在进行行列及数据的赋值
        T->data[i+1].row = T->data[i].row;
        T->data[i+1].col=T->data[i].col;
        T->data[i+1].value=T->data[i].value;
    }
    T->data[k].row=i;
    T->data[k].col=j;
    T->data[k].value=e;
    return True;
}//对稀疏矩阵中指定位置的元素值赋值

//////////////////////////////////////////////////////////初次编码出错//////////////////
void MyTransposeTSMatrix(TSMatrix* A,TSMatrix* B){
//    把矩阵A转置到B所指向的矩阵中去，矩阵用三元组表示
    B->m=A->n;//转置后矩阵的行
    B->n=A->m;//转置后矩阵的列
    B->len=A->len;//转置后矩阵中非零元素个数
    int j;
    int k;
    if(B->len>0) {
        j=1;
        for (int i=1; i <= B->len;) {
            for (k=1; k <= A->len; k++)
                //从头到尾扫描原三元表，找出所有列为j的三元组，并进行行列互换后放到新三元组表中
                if (A->data[k].col == j){
                    B->data[i].row=A->data[k].col;
                    B->data[i].col=A->data[k].row;
                    B->data[i].value=A->data[k].value;
                    i++;
                //每进行三元组表的转置赋值操作后，要将新三元组表的序号向后移动1，指向下一个空的三元组
                }
            j++;//每轮遍历结束后，下一次遍历时，遍历寻找的列数要加1，即寻找原矩阵的下一列中元素
            k=1;//更新循环变量，使其指向原三元组的开始位置
        }
    }
}//稀疏矩阵列序递增转置法(自作)
////////////////////////////////////////////////////////////

void TransposeTSMatrix(TSMatrix A, TSMatrix * B) {
    //这里不如用传址调用A，因为传址会比传值节省时间和空间
// 把矩阵A转置到B所指向的矩阵中去。矩阵用三元组表表示
    int i, j, k;
    B->m = A.n;
    B->n = A.m;
    B->len = A.len;
    if (B->len > 0) {
        j = 1;
        for (k = 1; k <= A.n; k++)
            for (i = 1; i <= A.len; i++)
                if (A.data[i].col == k) {
                    B->data[j].row = A.data[i].col;
                    B->data[j].col = A.data[i].row;
                    B->data[j].value = A.data[i].value;
                    j++;
                }
    }
}//稀疏矩阵列序递增转置法(教师标准代码)

void MyFastTransposeTSMatrix(TSMatrix* A,TSMatrix* B){
    //基于矩阵的三元组表，采用快速转置法，将矩阵A转置后赋给矩阵B
    B->m=A->n;
    B->n=A->m;
    B->len=A->len;
    int NumCol[A->n+1];
    int PosCol[A->n+1];
    for(int i=0;i<A->n+1;i++) {//初始化NumCol和PosCol数组
        NumCol[i] = 0;
        PosCol[i] = 0;
    }
    PosCol[1]=1;
    for(int i=1;i<=A->len;i++)
        NumCol[A->data[i].col]++;//计算每一列的非零元素的个数，data[0]未使用
    for(int i=2;i<=A->n;i++)
        PosCol[i]=PosCol[i-1]+NumCol[i-1];//求第i列的第一个非0元素在B->data[]中的正确位置
    for(int i=1;i<=A->len;i++){
    //将被转置矩阵的三元组表A从头到尾扫描一次，实现矩阵转置
    //当i列的元素第一次出现时，PosCol[A->data[i].col]是他转置后在新三元组表出现的起始位置
        B->data[PosCol[A->data[i].col]].value=A->data[i].value;//行列互换，元素赋值
        B->data[PosCol[A->data[i].col]].col=A->data[i].row;
        B->data[PosCol[A->data[i].col]].row=A->data[i].col;
        PosCol[A->data[i].col]++;//指向下一个列号为i的非零元素在三元组表B中存放的位置
    }
}// 稀疏矩阵一次定位快速转置算法(自作)

void FastTransposeTSMatrix (TSMatrix A, TSMatrix * B) {
// 基于矩阵的三元组表示，采用快速转置法，将矩阵A转置为B所指的矩阵
    int col, t, p, q;
    int num[MAXSIZE+1], position[MAXSIZE+1]; // 纠正教材
    B->len= A.len ;
    B->n= A.m ;
    B->m= A.n ;
    if(B->len) {
        for(col=1; col<=A.n; col++) //初始化num数组
            num[col]=0;
        for(t=1; t<=A.len; t++)
            num[A.data[t].col]++; // 计算每一列的非零元素的个数，data[0]未用
        position[1] = 1;
        for(col=2; col<=A.n; col++)
// 求col列中第一个非零元素在B.data[ ]中的正确位置
            position[col] = position[col-1]+num[col-1];
        for(p=1;p<=A.len;p++) {
// 将被转置矩阵的三元组表A从头到尾扫描一次，实现矩阵转置
            col = A.data[p].col;
            q = position[col]; // 当col是第一次出现，则q为该col转置后对应的起始位置
            B->data[q].row = A.data[p].col;
            B->data[q].col=A.data[p].row;
            B->data[q].value=A.data[p].value;
            position[col]++; // 指向下一个列号为col的非零元素在三元组表B中存放的位置
        }
    }
}//稀疏矩阵一次定位快速转置算法(教师标准代码)