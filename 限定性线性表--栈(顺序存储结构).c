//注：在这里通常设置空栈时栈顶指示器top=-1，top指示器指向当前栈顶的位置
// 在top执行自增操作后，才能执行入栈操作时（才会有空间存放下一个元素）
//当执行出栈操作后，出栈后，top执行自减操作，以此来指向执行出栈操作后的栈的栈顶
#include<stdio.h>

#define Stack_Size 50
#define ElemType int
#define True 0
#define False -1

typedef struct{
    ElemType elem[Stack_Size];//存放栈中的元素
    int top;//栈顶元素的下标，为0时是第一个元素，为-1时表示空栈
}SeqStack;//传值调用时形式参数无需设置为指针，传址调用时需要将形式参数设置为指针

void InitStack(SeqStack* S){
    S->top=-1;
}//构造一个空栈

int IsEmpty(SeqStack* S){
    if(S->top==-1) return True;
    return False;
//    更高级更简洁的实现
//    return ((S->top==-1)?True:False);
}//判断栈是否为空

int IsFull(SeqStack* S){
    if(S->top==(Stack_Size-1)) return True;
    return False;
//    更高级更简洁的实现
//    return ((S->top==(Stack_Size-1))?True:False);
}//判断栈是否为满

int Push(SeqStack* S,ElemType e){
    if(IsFull(S)==True){
        printf("栈已满，无法执行压栈操作");
        return False;
    }else{
        S->top++;//top从指向当前的栈顶移动到下一个可用位置
        S->elem[S->top]=e;//再存放该元素
        return True;
    }
}//顺序栈进栈操作

int Pop(SeqStack* S,ElemType* e){
    if(IsEmpty(S)==True){
        printf("栈为空，无法执行出栈操作");
        return False;
    }else{
        *e=S->elem[S->top];
        S->top--;//由于执行了出栈操作，栈顶指示器位置移动到出栈操作执行后新的栈顶位置
        return True;
    }
}//顺序栈出栈操作

int GetTop(SeqStack* S,ElemType* e){
//    只是将栈顶的元素值传出，无需改变栈顶位置（与出栈操作最大的不同）
    if(IsFull(S)==True){
        printf("栈为空，无法执行出栈操作");
        return False;
    }else *e=S->elem[S->top];
    return True;
}//顺序栈读取栈顶元素的操作