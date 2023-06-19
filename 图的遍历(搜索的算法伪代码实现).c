#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1
#define MAX_VERTEX_NUM 20 //最多的顶点个数
#define Graph ///待补足，邻接表，邻接矩阵，十字链表三种方法

typedef int ElemType;

int visited[MAX_VERTEX_NUM+1];

void TraverseGraph(Graph G){
//    Graph泛指图的一种存储结构
    for(int i=1;i<=G.vexNum;i++)
        visited[i]=False;//访问标志数组的初始化
    for(int i=1;i<=G.vexNum;i++) {
        //若G是连通图，此循环执行一次;如果是非连通图，需要执行多次
        if(!visited[i])
            Search(G,i);//以某种策略遍历图的一个连通子图
            //回溯操作是在Search函数里的
    }
}//图的遍历算法基本框架

void DepthFirstSearch(Graph g, int v0){ // v0为顶点的序号
    int w; // 补充教材，顶点序号
    visit(v0);
    visited[v0] = True;
    w = FirstAdjVertex(g,v0); // 获得v0的第一个邻接点
    while (w!=-1) { // 邻接点存在
        if(!visited[w])
            DepthFirstSearch(g,w);
        w = NextAdjVertex(g,v0,w); // 返回v0紧跟w之后的下一个邻接点
    }
}//深度优先遍历v0所在的连通子图

void DepthFirstSearch(Graph g, int v0) { // v0为顶点的序号
    SeqStack S; // 补充教材
    int w, v; // 补充教材
    InitStack(&S); // 初始化空栈
    Push(&S, v0)；
    while (!Empty(S)) {
        Pop(&S,&v);
        if(!visited[v]) {
            visit(v);
            visited[v] = True;
        } // 纠正教材
        w = FirstAdjVertex(g, v); // 求v的第一个邻接点
        while (w!=-1) {
            if (!visited[w])
                Push(&S, w);
            w = NextAdjVertex(g, v, w); // 求v相对于w的下一个邻接点
        }
    }
}

void BreadthFirstSearch(Graph g, int v0) { // v0为顶点的序号
// 广度优先搜索图g中v0所在的连通子图
    SeqQueue Q; // 补充教材
    int w, v; // 补充教材
    visit(v0);
    visited[v0] = True;
    InitQueue(&Q); // 初始化队列
    EnterQueue(&Q,v0);// v0进队
    while (!Empty(Q)) {
        DeleteQueue(&Q, &v); //队头元素出队
        w = FirstAdjVertex(g,v); // 求v的第一个邻接点
// 转下页
        while (w!=-1 ) {
            if (!visited[w]) {
                visit(w);
                visited[w] = True;
                EnterQueue(&Q, w);
            }
            w = NextAdjVertex(g, v, w); // 求v相对于w的下一个邻接点
        }
    }

}