#include<stdio.h>
#define ElemType char
#define MAXSIZE 40//串的最大长度
#define False -1
#define True 0

typedef struct{
    ElemType ch[MAXSIZE];//存储字符串的数组
    int len;//字符串的实际长度
}SString;

int StrInsert(SString* S,SString T,int pos){
    int i;
    int j;
    if(pos<0||pos>S->len) return False;//判断插入位置是否合理
    if(S->len+T.len<=MAXSIZE){//情况1
        for(i=S->len;i>(pos+T.len-1);i--)//移动，类似顺序表的插入
            S->ch[i+T.len-1]=S->ch[i-1];
        for(i=pos;i<(pos+T.len);i++)//在指定位置插入串T
            S->ch[i]=T.ch[i-pos];
        S->len=S->len+T.len;
        return True;
    }else if(S->len+T.len>MAXSIZE&&pos+T.len<=MAXSIZE){//情况2
//        插入后串长>MAXSIZE，但串t的序列可以全部插入
//        for(i=MAXSIZE-T.len-pos;i>=0;i--)
//            S->ch[i+T.len+pos]=S->ch[pos+i-1];
//        for(i=pos;i<=pos+T.len-1;i++)
//            S->ch[i]=T.ch[i-pos];
        for(i=MAXSIZE-1;i>=pos+T.len-1;i--)//移动，类似顺序表的插入
            S->ch[i]=S->ch[i-T.len];
        for(i=0;i<T.len;i++)//在指定位置插入串T
            S->ch[i+pos]=T.ch[i];
        S->len=MAXSIZE;
        return True;
    }else{//情况3
//        插入后串长>MAXSIZE，串t的部分字符也要舍弃，此时无需移动串B
        for(i=0;i<MAXSIZE-pos;i++)
            S->ch[pos+i]=T.ch[i];// 可存入MAXSIZE-LA个T的字符
        S->len=MAXSIZE;
        return True;
    }
}//顺序串的插入

int DelStr(SString* S,int pos,int k){
    if(k<0||k>S->len) return False;//判断k的值是否合理
    if(pos<0||pos>(S->len-k)) return False;//判断pos的值是否合理
    for(int i=pos;i<=(S->len-1);i++)//移动，类似顺序表的删除操作
        S->ch[i]=S->ch[i+k];
    S->len=S->len-k;
}//顺序表的删除

int StrCompare(SString S1,SString S2){
//    若串S1和S2相等，则返回0；若S1>S2返回正数，否则返回负数
    for(int i=0;i<S1.len&&i<S2.len;i++){
        if(S1.ch[i]==S2.ch[i]) continue;
        else return (S1.ch[i]-S2.ch[i]);
    } return S1.len-S2.len;
}//顺序串的比较算法

int MyStrIndex(SString S,int pos,SString T){
    if(pos+T.len-1>S.len-1) return False;//先判断位置是否合理，即之后有没有可能会出现T字符串
    int pre,i,j=0;
    for(pre=i=pos;pre<=S.len-1&&i<=S.len-1;){
        if(T.ch[j]==S.ch[i]){//如果第一个字符匹配上，则会继续之后的字符匹配
            for(j=1;j<T.len;j++,i++){
                if(T.ch[j]!=S.ch[i]){//如果出现一个字符无法匹配，则会回溯到pre的下一个位置，重新进行匹配流程
                    j=0;
                    i=pre;
                    break;
                }
            }
            if(i!=pre) return pre;//当T中所有的字符均已完成匹配后，就返回该字符串在原字符串中的第一个位置
        }else{//第一个字符无法匹配上，继续向下移动
            pre++;
            i=pre;
        }
    }return False;
}//顺序串的简单模式匹配(自作)

int StrIndex(SString s,int pos,SString t){//0≤pos≤s.len-1
//    求从主串s的下标pos起，模式串t第一次出现的位置;
//    成功返回t的一个字符在s中的位置下标，否则返回False
    int i,j,start;
    if(t.len==0) return pos; //空串是任意串的子串
    start=pos;//主串s从下标pos开始做匹配检测
    i=start;
    j=0;//j从0开始做匹配检测
    while(i<s.len&&j<t.len){
        if(s.ch[i]==t.ch[j]){//当前对应字符相等，继续后移考察剩下字符
            i++;
            j++;
        }else{
            start++;//从主串start后一个位置开始下一趟的考察
            i=start;
            j=0;
        }
    }
    if(j>=t.len) return start;//t中字符全部匹配成功
    else return False;//返回串s中对应串t第一个字符的位置
}//顺序串的简单模式匹配(标准代码)