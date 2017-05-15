#include<stdlib.h>
#include<stdio.h>
#include"Queue.h"

#define INFINITY INT_MAX   // 最大值∞
#define MAX_VERTEX_NUM 20  // 最大顶点数
typedef enum{DG,DN,UDG,UDN} GraphKind;  //{有向图，有向网，无向图，无向网}
typedef int VertexType;
typedef int VRType;
typedef int InfoType;
typedef int Status;
bool visited[MAX_VERTEX_NUM];  // 访问标志数组

typedef struct ArcCell {
	VRType adj;  // VRType是顶点关系类型。对无权图，用1或0
				 // 表示相邻否；对带权图，则为权值类型。
	InfoType *info;  // 该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];  // 顶点向量
	AdjMatrix arcs;  // 邻接矩阵
	int vexnum,arcnum;  // 图的当前顶点数和弧数
	GraphKind kind;  // 图的种类标志
}MGraph;

int locateVex(MGraph G,int v){  // 确定点v在图顶点向量的位置
	int i;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==v)
			return i;
	}
	return -1;
}

Status createDG(MGraph *G){
	int v1,v2;
	//构建有向图
	printf("输入顶点、弧的数量\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("输入%d个顶点\n",G->vexnum);
	for(int i=0;i<G->vexnum;i++){  
		scanf("%d",&G->vexs[i]);   // 构造顶点向量
	}
	for(int j=0;j<G->vexnum;j++){   // 初始化邻接矩阵
		for(int k=0;k<G->vexnum;k++){
			G->arcs[j][k].adj = 0;
			G->arcs[j][k].info = NULL;
		}
	}
	for(int p=0;p<G->arcnum;p++){  //构建邻接矩阵
		printf("输入一条边依附的两个顶点(第一个点指向第二个点):");
		scanf("%d%d",&v1,&v2);
		G->arcs[locateVex(*G,v1)][locateVex(*G,v2)].adj = 1;
	}
	return OK;
}
Status createDN(MGraph *G){
	 //构建有向网
	printf("虚设函数！\n");
	return OK;
}
Status createUDG(MGraph *G){
	//构建无向图
	int v1,v2;
	//构建有向图
	printf("输入顶点、弧的数量\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("输入%d个顶点\n",G->vexnum);
	for(int i=0;i<G->vexnum;i++){  
		scanf("%d",&G->vexs[i]);   // 构造顶点向量
	}
	for(int j=0;j<G->vexnum;j++){   // 初始化邻接矩阵
		for(int k=0;k<G->vexnum;k++){
			G->arcs[j][k].adj = 0;
			G->arcs[j][k].info = NULL;
		}
	}
	for(int p=0;p<G->arcnum;p++){  //构建邻接矩阵
		printf("输入一条边依附的两个顶点(没有先后顺序):");
		scanf("%d%d",&v1,&v2);
		G->arcs[locateVex(*G,v1)][locateVex(*G,v2)].adj = 1;
		G->arcs[locateVex(*G,v2)][locateVex(*G,v1)].adj = 1;
	}
	return OK;
}
Status createUDN(MGraph *G){
	//构建无向网
	printf("虚设函数！\n");
	return OK;
}

void printMatrix(MGraph G){
	//输出图
	int i,j;
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++){
			printf("%3d",G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

void visitFunc(MGraph G,int v){
	// 访问图第v个顶点
	printf("%3d",G.vexs[v]);
}
int firstAdjVex(MGraph G,int v){
	// 获取图G第v个顶点的第一个相邻点
	for(int i=0;i<G.vexnum;i++){
		if(G.arcs[v][i].adj == 1)
			return i;
	}
	return -1;
}

int nextAdjVex(MGraph G,int v,int w){
	// 获取图G第v个顶点的第w个相邻点的下一个相邻点
	for(++w;w<G.vexnum;w++){
		if(G.arcs[v][w].adj == 1)
			return w;
	}
	return -1;
}

void DFS(MGraph G,int v){
	// 从第v个顶点出发递归地深度优先遍历G
	visited[v] = true;
	visitFunc(G,v);
	for(int w = firstAdjVex(G,v);w>=0;w=nextAdjVex(G,v,w)){
		if(!visited[w])
			DFS(G,w);
	}
}

void BFSTraverse(MGraph G){
	// 广度优先遍历
	int v,u,w;
	Queue *Q = (Queue*)malloc(sizeof(Queue));
	for(v=0;v<G.vexnum;v++){
		visited[v]=false;
	}
	initQueue(Q);
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]){
			visited[v] = true;
			visitFunc(G,v);
			enQueue(Q,v);
			while(queueLength(*Q)>0){
				deQueue(Q,&u);
				for(w = firstAdjVex(G,u);w>=0;w = nextAdjVex(G,u,w)){
					if(!visited[w]){
						visited[w] = true;
						visitFunc(G,w);
						enQueue(Q,w);
					}
				}
			}
		}
	}

}

void DFSTraverse(MGraph G){
	//深度优先
	int v;
	for(v=0;v<G.vexnum;v++){
		visited[v] = false;
	}
	for(v=0;v<G.vexnum;v++){
		if(!visited[v])
			DFS(G,v);
	}
}

Status createGraph(MGraph *G){
	printf("输入图的类型构造邻接矩阵：0-DG,1-DN,2-UDG,3-UDN\n");
	scanf("%d",&G->kind);
	switch(G->kind){
		case DG: return createDG(G);
		case DN: return createDN(G);
		case UDG: return createUDG(G);
		case UDN: return createUDN(G);
		default:return ERROR;
	}
}
int main(){
	MGraph *G;
	int c;
	G = (MGraph*)malloc(sizeof(MGraph));
	createGraph(G);
	printf("图的矩阵输出：\n");
	printMatrix(*G);
	while(1){
		printf("\n1-深度，2-广度\n");
		scanf("%d",&c);
		switch(c){
		case 1:
			printf("深度优先遍历图：\n");
			DFSTraverse(*G);
			break;
		case 2:
			printf("广度优先遍历图：\n");
			BFSTraverse(*G);
			break;
		}
	}
	return 0;
}