//一维数组是在x轴上的展开，二维数组新增的一维是在y轴上的展开
// 三维数组新增的一维是在z轴上的展开
///注意：这里定义的数组下标从1开始
///注意：loc[i,j]是元素a(i,j)在一维数组中对应的下标
///而loc(A[i][j])是元素a(i,j)的存储空间地址
//一般来说在广义数组中loc[i,j]是从下标1开始的，这也将会导致在c语言中会浪费一个空间

#include<stdio.h>
#define True 0
#define False -1

///////////////////特殊三角矩阵的压缩存储///////////////////////////////
//下三角矩阵原二维数组下标a(i,j)与一维数组的对应公式：
//使用该公式的前提条件为：当i<j时a(i,j)=c一般来说c为0，当i>j时a(i,j)不全为同一常数
// loc[i,j]=loc[1,1]+i*(i-1)/2+j-1

//上三角矩阵原二维数组下标a(i,j)与一维数组的对应公式：
//使用该公式的前提条件为：当i>j时a(i,j)=c一般来说c为0，当i<j时a(i,j)不全为同一常数
//loc[i,j]=loc[1,1]+(2n-i+2)(i-1)/2+j-i

//对称矩阵的压缩存储原则:对称矩阵的元素满足a(i,j)=a(j,i)
// 因而只需利用上三角或下三角矩阵压缩存储法则存一半即可
///////////////////////////////////////////////////////////////////

/////////////////////带状矩阵的压缩存储////////////////////////////////
//三对角带状矩阵原二维数组下标a(i,j)与一维数组的对应公式：
//Loc[i, j] = Loc[1, 1] + 3(i -1)-1 + j-i+1
//使用该公式的前提条件为：当i=1，j=1,2时
//                   当1<i<n，j=i-1, i, i+1时
//                   当i=n，j=n-1, n时
///////////////////////////////////////////////////////////////////
