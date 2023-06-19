#include<stdio.h>
#include<malloc.h>
#define False -1
#define True 0

typedef struct{
    char* ch;//串的起始地址
    int len;//串的长度
}HString;//堆串的存储结构表示

int StrInsert(HString* S,int pos,HString *T){
    //0<=pos<=S->len
    //在串S中序号为pos的字符之前插入串t
    int i;
    char* temp;
    if(pos<0||pos>S->len||S->len==0) return False;
    temp=(char*)malloc(S->len+T->len);
    if(temp==NULL) return False;///这一步必须要有，为了判断是否在内存中有空间存放新的字符串
    for(i=0;i<pos;i++)
        temp[i]=S->ch[i];//向temp赋值串S的前pos个字符
    for(i=pos;i<pos+T->len;i++)
        temp[i]=T->ch[i-pos];//从temp的pos位置开始，复制到串t
    for(i=pos+T->len;i<S->len+T->len;i++)
        temp[i]=S->ch[i-T->len];
    S->len=S->len+T->len;//串的长度更新为串s和串t的长度之和
    free(S->ch);//释放掉串s中原有的串值空间
    S->ch=temp;//将串S的串值指针指向temp的空间
    return True;
}//堆串的插入

int StrAssign(HString* S,char* T){
    if(S->ch!=NULL) free(S->ch);//串s已有串值空间
    S->ch=NULL;
    int i=0;
    while(T[i]!='\0') i++;//计算字符串常量T的长度
    if(i) {//如果字符串常量长度不为0
        S->ch = (char *) malloc(i);//申请一段字符串常量串长大小的字符空间
        if(S->ch==NULL) return False;
        ///这一步必须要有，为了判断是否在内存空间中申请到字符串常量串长大小的字符空间
        for(i=0;T[i]!='\0';i++)//将字符串常量T的值赋值给串S
            S->ch[i]=T[i];
    }else S->ch=NULL;//如果字符串常量T的长度为0
    S->len=i;
    return True;
}//堆串的赋值

int StrDelete(HString* S,int pos,int k){
    if(pos<0||pos>(S->len-k)) return False;//判断位置是否合法
//    在串S中删除从序号pos起的k个字符
    char* temp;
    temp=(char*)malloc(S->len-k);
    if(temp==NULL) return False;
    ///这一步必须要有，为了判断是否在内存空间中申请到删除部分字符后新的字符串的字符空间
    int i;
    for(i=0;i<pos;i++)//将串S的前pos个字符复制到temp
        temp[i]=S->ch[i];
    for(i=pos+k;i<S->len;i++)
        temp[i-k]=S->ch[i];//将串S从pos+k的位置开始，复制剩余的字符到temp
    free(S->ch);//释放串s中原来的空间
    S->ch=temp;//将串s的空间更新为temp的空间
    S->len=S->len-k;//串的长度减小k
    return True;
}//堆串的删除

int StrIndex(HString* S,int pos,HString* T){//求串T在串S中的位置
    int i,j;
    if(T->len==0) return pos;//空串是任意串的子串
    if((pos+T->len)>S->len) return False;
    for(i=pos,j=0;i<S->len&&j<T->len;){
        if(S->ch[i]==T->ch[j]){
            i++;
            j++;
        }else{
            i=i-j+1;//回溯到串s下一轮考察的起始位置
            j=0;//回溯后从串T的第一个字符开始
        }
    }
    if(j==T->len) return i-j;//返回串S的第一次和串T匹配的子串的第一个字符的下标
    else return False;
}//简单模式匹配Brute-Fore（BF）算法
///这次的模式匹配算法相较于定长顺序串减少了start变量的使用，节省了部分空间