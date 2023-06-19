#include<stdio.h>
#include"限定性线性表--栈(顺序存储结构).c"
#include<malloc.h>
#define True 0
#define False -1
#define MAX_VERTEX_NUM 20//最多的顶点个数

///连通图的深度优先搜索树是该连通图的一颗生成树。

typedef char VexData;
typedef enum{DG, DN, UDG, UDN} GraphKind; // 图的种类
typedef int elemType;
typedef struct Node{
    VexData adjVex;//与顶点相邻接的顶点的位置，为弧的时候，是弧的终止点
    elemType weight;//与弧或边相关的信息，例如权重
    struct Node* nextArc;//指向与该邻接点共起点的其余邻接点，即指向下一条弧/边的指针
}AdjNode;

typedef struct {
    VexData headVex;//顶点数据
    AdjNode* firstArc;//指向该顶点的第一个邻接点的指针
}VertexNode;

struct{
    int LowCost;
    int AdjVexNum;
}PrimTree[MAX_VERTEX_NUM+1];

int visited[MAX_VERTEX_NUM+1];//访问的标志数组
int ve[MAX_VERTEX_NUM+1];//每个顶点的最早发生时间,求解关键路径问题时使用

typedef struct{
    VertexNode vertex[MAX_VERTEX_NUM+1];
    int vexNum;//图的顶点数
    int arcNum;//图的边或者弧的个数
    GraphKind kind;//图的种类
}AdjList;// 基于邻接表的图Adjacency List Graph

//正向邻接表求顶点的出度，逆邻接表求顶点的入度。

void visit(int n){
    //visit函数根据对顶点操作的需要进行补充
    ;
}

int LocateSearch(AdjList* G,VexData data){
    int position=False;
    for(int i=1;i<=G->vexNum;i++){
        if(G->vertex[i].headVex==data){
            position=i;
            break;
        }
    }return position;
}//查找顶点的所在下标位置

void DepthFirstSearch(AdjList* G,int v0){//v0未顶点的序号
    AdjNode* p;
    int p_pos;
    visit(v0);
    visited[v0]=True;
    p=G->vertex[v0].firstArc;//v0对应的边链表
    while(p!=NULL){
        p_pos= LocateSearch(G,p->adjVex);
        if(visited[p_pos]!=True){//该结点未被访问时，对该结点进行深度优先搜索
            //这一步添加一个打印v0到p_pos边的操作，可以获得一个生成树，原理在于对于未访问的结点进行访问，访问过的进行回溯
            DepthFirstSearch(G,p_pos);
        }
        p=p->nextArc;
        //创建图时边
        // 链表的结点顺序会影响遍历顺序
    }
}//采用邻接表的深度优先搜索算法

void TraverseGraph(AdjList * G){
    for(int i=1;i<=G->vexNum;i++)
        visited[i]=False;//初始化访问标志数组
    for(int j=1;j<=G->vexNum;j++){
        if(!(visited[j])){//连通图或者是强连通图，DFS函数只会调用一次
            DepthFirstSearch(G,j);
        }
    }
}//深度优先遍历图G

///AOV网：用顶点表示活动，用弧表示活动间的优先关系的有向无环图，称为顶点表示活动的网
//拓扑序列需要包含图中所有结点，求拓扑序列即为拓扑排序

void FindID(AdjList* G,int inDegree[MAX_VERTEX_NUM+1]){//求各顶点的入度
    AdjNode* p;
    for(int i=1;i<=MAX_VERTEX_NUM;i++)//顶点序号从1开始
        inDegree[i]=0;
    for(int i=1;i<=G->vexNum;i++){
        p=G->vertex[i].firstArc;
        while(p!=NULL){
            inDegree[LocateSearch(G,p->adjVex)]++;
            p=p->nextArc;
        }
    }
}//求个顶点的入度(用于拓扑排序算法)(AOV网)

int TopoSort(AdjList* G){
    int inDegree[MAX_VERTEX_NUM+1];
    int count=0;
    int v;
    AdjNode* p;
    FindID(G,inDegree);//求各顶点的入度
    SeqStack S;
    InitStack(&S);//初始化栈
    for(int i=1;i<=G->vexNum;i++)
        if(inDegree[i]==0)
            Push(&S,i);//将入度为0的顶点入栈
    while(!IsEmpty(&S)){
        Pop(&S,&v);
        printf("%c",G->vertex[v].headVex);//输出v号顶点的信息
        count++;//排序好的结点集中结点数＋1
        p=G->vertex[v].firstArc;
        while(p!=NULL){//边链表中结点的插入顺序会影响拓扑排序的结果
            inDegree[LocateSearch(G,p->adjVex)]--;//顶点v的每个邻接点的入度减少1
            if(inDegree[LocateSearch(G,p->adjVex)]==0)
                Push(&S,LocateSearch(G,p->adjVex));//某一个结点入度减少为0，压栈
            p=p->nextArc;
        }
    }
    if(count<G->vexNum)
        return False;//该有向图中含有回路
    return True;
}//拓扑排序算法(AOV网)

///AOE网：用弧表示活动，顶点表示事件，弧的权值表示活动所需时间的有向无环图，称为边表示活动的网
///关键路径：从源点到汇点路径长度最长的路径(时间耗费最长的路径，完成所有工程的最短时间)称为关键路径
///事件Vi的最早发生时间：从源点到顶点V0的最长路径长度，从顶点开始以拓扑顺序向后递推，每一步的时间取最大
///事件Vi的最晚发生时间：在确保汇点按其最早发生时间发生这一前提下，在求出汇点最早发生时间的基础上，从汇点开始，按逆拓扑顺序向源点递推
///活动Ai的最早开始时间：如果活动ai对应的弧为<j,k>，则e(i)等于从源点到顶点j的最长路径的长度，即：e(i)=ve(j)。
///活动Ai的最晚开始时间：如果活动ai对应的弧为<j,k>，其持续时间为dut(<j,k>)，则有：l(i) = vl(k)- dut(<j,k>)
///              即：活动ai的最晚开始时间l(i)是弧头k的最晚发生时间vl(k)与弧的权值之差。
///活动Ai的松弛时间（时间余量）： ai的最晚开始时间与ai的最早开始时间之差：l(i)-e(i)。

int TopoOrder(AdjList* G,SeqStack* T){
//    G为有向网，T来存放逆拓扑序列的栈，S为存放入度为0的顶点的栈
    SeqStack S;
    AdjNode* p;
    int count=0;
    InitStack(&S);
    InitStack(T);
    int PopNum;
    int inDegree[MAX_VERTEX_NUM+1];
    for(int i=1;i<=G->vexNum;i++)
        ve[i]=0;
    FindID(G,inDegree);
    for(int i=1;i<=G->vexNum;i++)
        if(inDegree[i]==0)
            Push(&S,i);
    for(int k=1;k<=G->vexNum;k++){
        if(!IsEmpty(&S)){
            Pop(&S,&PopNum);
            Push(T,PopNum);//生成逆拓扑序列
            count++;
            p=G->vertex[PopNum].firstArc;
            while(p!=NULL){
                inDegree[LocateSearch(G,p->adjVex)]--;
                if(inDegree[p->adjVex]==0)
                    Push(&S, LocateSearch(G,p->adjVex));
                if((ve[PopNum]+p->weight)>ve[LocateSearch(G,p->adjVex)])
                    //p->weight存放的是活动进行所需时间
                    ve[LocateSearch(G,p->adjVex)]=ve[PopNum]+p->weight;//求解该弧段的终点的最早发生时间
                p=p->nextArc;
            }
        }
    }
    if(count<G->vexNum)
        return False;
    return True;
}//为了求解关键路径问题修改后的拓扑排序序列

int CriticalPath(AdjList* G){//约定创建图时，汇点的编号最大
    int vl[MAX_VERTEX_NUM+1];// 每个顶点的最迟发生时间
    int PopNum;
    SeqStack T;
    AdjNode* p;
    int m;
    char tag;
    if(TopoOrder(G,&T)==False)
        return False;
    for(int i=1;i<=G->vexNum;i++)
        vl[i]=ve[G->vexNum];// 初始化顶点事件的最迟发生时间
    while(!IsEmpty(&T)){// 按逆拓扑顺序求各顶点的vl值
        Pop(&T,&PopNum);
        p=G->vertex[PopNum].firstArc;
        while(p!=NULL){
            if((ve[LocateSearch(G,p->adjVex)]-p->weight)<vl[PopNum])
                vl[PopNum]=ve[LocateSearch(G,p->adjVex)]-p->weight;
            p=p->nextArc;
        }
    }
    for(int i=1;i<=G->vexNum;i++){//求解关键活动
        p=G->vertex[i].firstArc;
        while(p!=NULL){
            m=LocateSearch(G,p->adjVex);
            if(ve[i]==(vl[m]-p->weight)) tag='*';
            else tag='-';
            printf("%c,%c,%d,%d,%d,%c",G->vertex[i].headVex,G->vertex[m].headVex,ve[i],vl[i],p->weight,tag);
//            输出活动
            p=p->nextArc;
        }
    }
    return True;
}//关键路径算法