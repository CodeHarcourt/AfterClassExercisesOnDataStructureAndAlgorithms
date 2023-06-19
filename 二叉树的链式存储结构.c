#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1
#define ElemType int

int LeafCount=0;
int maxDepth=0;
//int high=1;

typedef struct Node{
    ElemType data;
    struct Node* LChild;
    struct Node* RChild;
}BiTNode,*BiTree;

void visit(ElemType* data){
    ;
}//访问结点数据域的操作，待补充

void PreOrder(BiTree root){
    //root为指向二叉树(或某一子树)根节点的指针
    BiTNode* p;
    p=root;
    if(p!=NULL) {
        visit(&p->data);//访问根节点
        PreOrder(p->LChild);//先序遍历左子树
        PreOrder(p->LChild);//先序遍历右子树
    }
}//先序遍历二叉树(头左右的顺序)即第一次访问到头结点时对其进行visit操作

void InOrder(BiTree root){
//    root为指向二叉树(或某一子树)根结点的指针
    BiTNode* p;
    p=root;
    if(p!=NULL){
        InOrder(p->LChild);//中序遍历左子树
        visit(&(p->data));//访问根节点
        InOrder(p->RChild);//中序遍历右子树
    }
}//中序遍历二叉树(左头右的顺序)//即第二次访问到头结点时对其进行visit操作

void PostOrder(BiTree root){
//    root为指向二叉树(或某一子树)根结点的指针
    BiTNode* p;
    p=root;
    if(p!=NULL){
        PostOrder(p->LChild);//后序遍历左子树
        PostOrder(p->RChild);//后序遍历右子树
        visit(&(p->data));//访问根节点
    }
}//后序遍历二叉树(左右头的顺序)即最后一次访问到头结点的时候对其进行visit操作

/////////////////////第一次实现出错的(主要问题还是在形参双指针的上)////////////////////////////
void CreatBiTree(BiTree* bt){
    //*bt是一个还未初始化的指针，即此时的指针还是悬空的
    // 当对其进行赋值为NULL和malloc开辟空间操作后都可以实现“落地”
    //使用二重指针即指向指针的指针的原因如下：
    //一重指针指向的是一个未初始化内存空间
    // 二重指针指向的是一重指针的内存空间(里面储存的是上述未初始化内存空间的地址)
    //通过*bt=NULL操作可以将一重指针指向空的内存空间(此时已经对一重指针原来的指向进行了修改为NULL)
    //通过malloc函数可以申请一个BiTNode大小的内存空间，返回值是一重指针
    //     进行赋值即为对一重指针原来的指向进行了修改，使其指向一块新的可用的内存空间
    char ch;
    ch=getchar();
    if(ch=='.')
        *bt=NULL;
    else{
        BiTNode* p=(BiTNode*)malloc(sizeof(BiTNode));
        p->data=ch;//创建根节点
        *bt=p;
        CreatBiTree(&(p->LChild));//创建左子树
        CreatBiTree(&(p->RChild));//创建右子树
    }
}//用拓展先序遍历创建二叉链表
//////////////////////////////////////////////////////////////

void MyLeafNum(BiTree root,int* leafCount){
//    LeafCount为声明在main函数里的int变量，在main函数里调用该函数时，要对LeafCount变量&取地址操作
    if(root!=NULL){
        MyLeafNum(root->LChild,leafCount);
        MyLeafNum(root->RChild,leafCount);
        if(root->LChild==NULL&&root->RChild==NULL)
            (*leafCount)++;
    }
}//后序遍历统计叶子结点数目(法1自作)

void leafNum(BiTree root){
//    LeafCount为全局变量，保存叶子结点数目，调用前初始化为0
    if(root!=NULL){
        leafNum(root->LChild);
        leafNum(root->RChild);
        if(root->LChild==NULL&&root->RChild==NULL)
            LeafCount++;
    }
}//后序遍历统计叶子节点数目(法1标准代码)

int LeafNum(BiTree root){
    int leafNum;//leafNum在每次递归时是一个局部变量
    if(root==NULL)
        return 0;
    else if(root->LChild==NULL&&root->RChild==NULL)
        return 1;
    else
        leafNum=LeafNum(root->LChild)+LeafNum(root->RChild);
//    叶子数为左右子树的叶子数目之和
    return leafNum;
}//后序遍历统计叶子节点数目(法2)

void PreOrderCount(BiTree root,int* m){
//    先序遍历输出二叉树结点，root为指向二叉树(子树)根节点的指针
    if(root!=NULL) {
        (*m)++;//结点个数加1
        PreOrderCount(root->RChild,m);//先序遍历左子树
        PreOrderCount(root->LChild,m);//先序遍历右子树
    }
}//先序遍历统计二叉树中结点个数

int PostTreeDepth(BiTree bt){
    int hL,hR,h;
    if(bt==NULL) return 0;//如果是空树的话，返回高度为0
    else{
        hL=PostTreeDepth(bt->LChild);//求左子树的深度
        hR=PostTreeDepth(bt->RChild);//求右子树的深度
        h=hL>hR?hL:hR;//得到左右子树的较大者
        return h+1;//注意返回树的深度的时候要＋1，
    }
}//后序遍历求二叉树高度(法1)递归算法

void PreTreeDepth(BiTree bt,int high){
//    h为bt指向结点所在层次，初值为1，即在main函数中调用该函数的时候要提前声明该变量，并将其初始化为1
//    depth全局变量，初值为0，为当前求得的最大层次
    if(bt!=NULL){
         if(high>maxDepth){
             maxDepth=high;
             PreTreeDepth( bt->LChild,high+1);//遍历左子树
             PreTreeDepth(bt->RChild,high+1);//遍历右子树
         }
    }
}//先序遍历求二叉树高度(法2)递归算法

void PrintTree(BiTree bt,int nlayer){
//    将一棵树逆时针打印，并通过每个结点打印输出时的空格数来显示该结点所在深度
//    输出的顺序是逆中序，即打印顺序为右头左
    int i=0;
    if(bt!=NULL){
        i++;//i变量用于指示当前结点所在深度
        PrintTree(bt->RChild,i);
        for(int j=0;j<nlayer;i++)
            putchar(' ');//结点所在的层数越深，前面的空格数越多
        printf("%d",bt->data);
        PrintTree(bt->LChild,i);
    }
}//按树状横向(即原二叉树逆时针旋转90度)打印二叉树