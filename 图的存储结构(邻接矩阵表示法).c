//简单路径：路径的顶点序列中的顶点各不相同。
//简单回路：除了第一个和最后一个顶点外，其余各顶点均不重复出现的回路
//赋权图或网：带权的图，可有向，可无向
#include<stdio.h>
#define MAX_VERTEX_NUM 20 //最多的顶点个数
#define INFINITY 32768  //表示极大值∞
#define ElemType int
#define True 0
#define False -1

///图的邻接矩阵表示法不适用于稀疏图的存储
typedef enum{DG,DN,UDG,UDN} GraphKind; //定义枚举变量图的种类：有向图，有向网，无向图，无向网依次对应
typedef char VertexData; //假设顶点数据为字符型
typedef struct ArcNode{
    int adj;//无权图用1或0表示是否相邻；赋权图为权值
    ElemType OtherInfo;
}ArcNode;

int visited[MAX_VERTEX_NUM+1];//访问的标志数组

typedef struct {
    VertexData vertex[MAX_VERTEX_NUM+1];//顶点集
    ArcNode arcs[MAX_VERTEX_NUM+1][MAX_VERTEX_NUM+1];//边集，即邻接矩阵
    int vexNum;//顶点数
    int arcNum;//边数
    GraphKind kind;//图的种类
}AdjMatrix;//Adjacency Matrix Graph(邻接矩阵图)

struct Prim{
    int lowCost;
    int AdjVexNum;
}PrimTree[MAX_VERTEX_NUM+1];

int LocateVertex(AdjMatrix* G,VertexData data){
//    在顶点集数组中下标从1开始
    int position;
    position=False;
    for(int i=1;i<=G->vexNum;i++)
        if(data==G->vertex[i]) {
            position = i;
            break;
        }
    return position;
}//判断data在顶点集中下标位置

int CreatDN(AdjMatrix* G){//创建一个有向网DN
    VertexData row,col;
    int p1,p2;
    int weight;
    G->kind=DN;//DN为枚举类型中的有向网
    scanf("有向网的顶点数:%d",&G->vexNum);
    scanf("有向网中的边数:%d",&G->arcNum);
    for(int i=1;i<=G->vexNum;i++)//邻接矩阵两个维度的下标都从1开始
        for(int j=1;j<=G->arcNum;j++)
            G->arcs[i][j].adj=INFINITY;//初始化所有weight为INFINITY
    for(int i=1;i<=G->vexNum;i++)
        G->vertex[i]=getchar();//输入图的顶点，输入顺序决定了该顶点在有向图中的行列下标位置
    for(int i=1;i<=G->arcNum;i++){
        scanf("row:%c,col:%c,weight:%d",&row,&col,&weight);// 输入一条弧的两个顶点及权值
        p1= LocateVertex(G,row);//顶点row在顶点集中的位置
        p2= LocateVertex(G,col);//顶点col在顶点集中的位置
        if(p1==False||p2==False) return False;//如果没有找到该顶点在顶点集的位置，退出程序
        G->arcs[p1][p1].adj=weight;//在邻接矩阵中记录弧对应的权值
    }
    return True;
}//采用邻接矩阵表示法创建有向网

int FirstAdjVertex(AdjMatrix* G,VertexData data){
    int p1= LocateVertex(G,data);
    for(int i=1;i<=G->vexNum;i++){
        if(G->arcs[p1][i].adj!=INFINITY)
            return i;
    }return False;
}//采用邻接矩阵求图中顶点的第一个邻接点

void visit(int n){
    //visit函数根据对顶点操作的需要进行补充
    ;
}

void DepthFirstSearch(AdjMatrix* G,int v0){
    visit(v0);//访问此顶点
    visited[v0]=True;//将该访问过的顶点的标志改为True
    for(int i=1;i<=G->vexNum;i++){//序号从0开始，优先遍历编号小的邻接点
        if(visited[i]==False&&G->arcs[v0][i].adj!=INFINITY)//与v0有边或它为起始点的弧
            DepthFirstSearch(G,i);//以i作为起始顶点，进行深度优先搜索
    }
}//采用邻接矩阵的深度优先搜索算法

void TraverseGraph(AdjMatrix* G){
    for(int i=1;i<=G->vexNum;i++)
        visited[i]=False;//初始化访问标志数组
    for(int j=1;j<=G->vexNum;j++){
        if(!(visited[j])){//连通图或者是强连通图，DFS函数只会调用一次
            DepthFirstSearch(G,j);
        }
    }
}//深度优先遍历图G

int pre[MAX_VERTEX_NUM+1];//全局变量

int DFS_C(AdjMatrix* G,int u,int v){
    int w;
    if(u==v) return True;
    else{
        for(int i=1;i<=G->vexNum;i++){
        if(G->arcs[u][i].adj!=INFINITY&&pre[i]==False){
            pre[i]=u;
            if(i==v) return True;//这里可以改为打印路径的操作
            DFS_C(G,i,v);
        }
        }
    }
}//深度优先找出从顶点u到v的简单路径中的DFS搜索算法

int Path(AdjMatrix* G,int u,int v){
    if(u>G->vexNum||u<1||v>G->vexNum||v<1) return False;
    else{
        for(int i=1;i<=G->vexNum;i++) pre[i]=False;
        pre[u]=u;
        DFS_C(G,u,v);
    }
}//深度优先找出从顶点u到v的简单路径

int Minium(struct Prim *PrimTree){
    int min;
    for(int i=1;i<=MAX_VERTEX_NUM;i++)
        if(PrimTree[i].lowCost!=0){
            min=PrimTree[i].lowCost;
            break;
        }
    for(int i=1;i<=MAX_VERTEX_NUM;i++){
        if(PrimTree[i].lowCost<min)
            min=PrimTree[i].lowCost;
    }
    for(int i=1;i<=MAX_VERTEX_NUM;i++){
        if(PrimTree[i].lowCost==min)
            return i;
    }
}//查找与U中结点连接的权值最小的边的邻接点v(在Prim算法中调用)

void MiniSpanTree_Prim(AdjMatrix*G,int u){
//    从顶点u出发，构建连通图G的一个最小生成树，并输出该最小生成树的每条边
    int v;
    PrimTree[u].lowCost=0;
    for(int i=1;i<=G->vexNum;i++)
        if(i!=u){//对V-U中的结点i初始化PrimTree[i]权值以及与u中第一个结点即顶点的连接
            PrimTree[i].lowCost=G->arcs[u][i].adj;
            PrimTree[i].AdjVexNum=u;
        }
    for(int j=1;j<=(G->vexNum-1);j++){
        v = Minium(PrimTree);//查找与U中结点连接的权值最小的边的邻接点v
        PrimTree[v].lowCost=0;//将v结点放入已找好的生成树结点U中
        u=PrimTree[v].AdjVexNum;//寻找v结点所在的最小生成树中的起始节点，以便之后的打印输出
        printf("%c%c",G->vertex[u],G->vertex[v]);
        for(int i=1;i<=G->vexNum;i++){
            //将v纳入U集合后，根据情况，更新PrimTree[i]
            if(G->arcs[v][i].adj<PrimTree[i].lowCost){
                PrimTree[i].lowCost=G->arcs[v][i].adj;
                PrimTree[i].AdjVexNum=v;
            }
        }
    }
}//最小生成树(Prim算法)

//求最小生成树的加点法(Prim算法)适合稠密图
//求最小生成树的加边法(Kruskal算法)适合稀疏图