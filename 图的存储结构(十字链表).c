#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1
#define MAX_VERTEX_NUM 20//最多的顶点个数

typedef char VexData;//顶点内存储的数据类型
typedef enum{DG, DN, UDG, UDN} GraphKind; // 图的种类
typedef int ElemType;

typedef struct ArcNode{
    VexData startVex;//该弧段的起始结点
    VexData stopVex;//该弧段的终止结点
    ElemType weight;//该弧段对应的权值
    struct ArcNode* SameStartLink;//与该弧共起点的下一个弧段
    struct ArcNode* SameStopLink;//与该弧共终点的弧段
}ArcNode;//弧结点

typedef struct{
    VexData vertexData;//顶点内存储的数据
    ArcNode* FirstOut;//由该顶点作为起始点的第一个弧结点
    ArcNode* FirstIn;//由该顶点作为终点的第一个弧结点
}VertexNode;//顶点结点

typedef struct{
    VertexNode vexLink[MAX_VERTEX_NUM+1];
    int vexNum;//顶点个数
    int arcNum;//弧的个数
    GraphKind kind;//图的种类
}OrtList;//十字链表

int LocateVertex(OrtList* G,VexData data){
    int position=False;//初始化为False
    for(int i=1;i<=G->vexNum;i++)
        if(G->vexLink[i].vertexData==data){
            position=i;
            break;
        }
    return position;
}//寻找弧结点的起点和终点在顶点集中的下标

void CrtOrtList(OrtList* G){
    // 从终端输入n个顶点的信息和e条弧的信息，以建立一个有向图的十字链表
    int p1,p2;
    int weight;
    VexData start,stop;
    ArcNode* new;
    scanf("%d%d",&G->vexNum,&G->arcNum);
    for(int i=1;i<=G->vexNum;i++){
        G->vexLink[i].vertexData=getchar();
        G->vexLink[i].FirstIn=NULL;
        G->vexLink[i].FirstOut=NULL;
    }//初始化顶点集的信息
    for(int i=1;i<=G->arcNum;i++){
        start=getchar();
        stop=getchar();
        scanf("%d",&weight);
        p1=LocateVertex(G,start);
        p2=LocateVertex(G,stop);
        if(p1==False||p2==False) continue;
        //如果查找结果为False表示无该顶点，需要重新录入弧结点信息
        new=(ArcNode*)malloc(sizeof(ArcNode));
        //申请一个结点空间，用以存放新的弧结点信息
        new->startVex=start;
        new->stopVex=stop;
        new->weight=weight;
        //下面是最主要的操作
        ///思想类似于头插法建立单链表
        new->SameStartLink=G->vexLink[i].FirstOut;
        G->vexLink[i].FirstOut=new;
        new->SameStopLink=G->vexLink[i].FirstIn;
        G->vexLink[i].FirstIn=new;
    }
}