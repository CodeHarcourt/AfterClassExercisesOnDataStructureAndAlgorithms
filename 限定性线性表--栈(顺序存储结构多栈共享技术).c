#include<stdio.h>

#define Stack_Size 100
#define ElemType int
#define True 0
#define False -1

typedef struct{
    ElemType elem[Stack_Size];//栈区
    int top[2];
//    top[0]和top[1]分别是两个栈顶指示器
}DqStack;

void InitStack(DqStack* S){
    S->top[0]=-1;
    S->top[1]=Stack_Size;
}//双端顺序栈初始化

int Push(DqStack* S,int i,ElemType e){
//    把数据元素e压入第i号栈，i可取0或1
    if((S->top[0]+1)==S->top[1]){
        printf("栈已满，无法执行压栈操作");
        return False;
    }else{
        switch(i){
            case 0:{
                S->top[0]++;
                S->elem[S->top[0]]=e;
                return True;
            }break;
            case 1:{
                S->top[1]--;//注意：此时双端栈右边的栈的栈顶要往左边即数组下标减小的方向移动
                S->elem[S->top[1]]=e;
                return True;
            }break;
            default :
                return False;
        }
    }
}//双端顺序栈进栈操作
//注意事项：进栈时top[0]向右端移动，top[1]向左端移动

int Pop(DqStack* S,int i,ElemType* e){
//    从i号栈中弹出栈顶元素，并由e输出该元素，i可取0或1
    switch(i){
        case 0:{
            if(S->top[0]==-1){
                printf("左端栈已满，无法执行出栈操作");
                return False;
            }else{
                *e=S->elem[S->top[0]];
                S->top[0]--;//0号栈出栈时减1
                return True;
            }
        }break;
        case 1:{
            if(S->top==Stack_Size){
                printf("右端栈为空，无法执行出栈操作");
                return False;
            }else{
                *e=S->elem[S->top[1]];//出栈时top[1]向右运动
                S->top[1]++;//1号栈出栈是加1，指向新的栈顶
                return True;
            }
        }break;
        default:
            return False;
    }
}//双端顺序栈出栈操作