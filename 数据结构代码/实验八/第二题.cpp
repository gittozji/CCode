#include<stdlib.h>
#include<stdio.h>
#include"Queue.h"
#define MAX_VERTEX_NUM 20
typedef int VertexType;
typedef int InfoType;
typedef int Status;
typedef enum{DG,DN,UDG,UDN} GraphKind;  //{有向图，有向网，无向图，无向网}
bool visited[MAX_VERTEX_NUM];  // 访问标志数组

typedef struct ArcNode{  
	int adjvex;  //该弧所指向的顶点的位置
	struct ArcNode *nextarc;  //指向下一条弧的指针
	InfoType info;  //该弧相关信息的指针
}ArcNode;

typedef struct VNode{
	VertexType data;  //顶点信息
	ArcNode *firstarc;  //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;  
	int vexnum,arcnum;  //图的当前顶点数和弧数
	int kind;  //图的种类标志
}ALGraph;

int locateVex(ALGraph G,int v){  // 确定点v在图顶点向量的位置
	int i;
	for(i=0;i<G.vexnum;i++){
		if(G.vertices[i].data==v)
			return i;
	}
	return -1;
}

void addArcNode(ALGraph *G,int v1,int v2,int weight){
	ArcNode *p;
	p = G->vertices[locateVex(*G,v1)].firstarc;
	if(p == NULL){
		p = G->vertices[locateVex(*G,v1)].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = locateVex(*G,v2);   //p->adjvex存v2在表头向量的位置
		p->info = weight;  //赋权值
		p->nextarc = NULL;
	}
	else{
		while(p->nextarc != NULL){
			p = p->nextarc;
		}
		p = p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = locateVex(*G,v2);
		p->info = weight;
		p->nextarc = NULL;
	}
}

Status createDG(ALGraph *G){
	//构建有向图
	printf("虚设函数！\n");
	return OK;
}

Status createDN(ALGraph *G){
	int v1,v2,weight;
	//构建有向网
	printf("输入顶点、弧的数量\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("输入%d个顶点\n",G->vexnum);
	for(int i=0;i<G->vexnum;i++){  //构造表头向量
		scanf("%d",&G->vertices[i].data);  //输入顶点值
		G->vertices[i].firstarc=NULL;
	}
	for(int k=0;k<G->arcnum;k++){
		printf("输入一条边依附的两个顶点及其权值(第一个点指向第二个点):");
		scanf("%d%d%d",&v1,&v2,&weight);
		addArcNode(G,v1,v2,weight);  //加入弧
			
	}
	return OK;
}
Status createUDG(ALGraph *G){
	//构建无向图
	printf("虚设函数！\n");
	return OK;
}
Status createUDN(ALGraph *G){
	//构建无向网
	int v1,v2,weight;
	//构建有向网
	printf("输入顶点、弧的数量\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("输入%d个顶点\n",G->vexnum);
	for(int i=0;i<G->vexnum;i++){  //构造表头向量
		scanf("%d",&G->vertices[i].data);  //输入顶点值
		G->vertices[i].firstarc=NULL;
	}
	for(int k=0;k<G->arcnum;k++){
		printf("输入一条边依附的两个顶点及其权值(没有先后顺序):");
		scanf("%d%d%d",&v1,&v2,&weight);
		addArcNode(G,v1,v2,weight);
		addArcNode(G,v2,v1,weight);
	}
	return OK;
}

Status createGraph(ALGraph *G){
	printf("输入图的类型构造邻接表：0-DG,1-DN,2-UDG,3-UDN\n");
	scanf("%d",&G->kind);
	switch(G->kind){
		case DG: return createDG(G);
		case DN: return createDN(G);
		case UDG: return createUDG(G);
		case UDN: return createUDN(G);
		default:return ERROR;
	}
}

void printALGraph(ALGraph G){  // 打印邻接表
	ArcNode* p;
	for(int i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		printf("%d:  ",G.vertices[i].data);
		while(p!=NULL){
			printf("点:%d 权:%d ----> ",G.vertices[p->adjvex].data,p->info);
			p=p->nextarc;
		}
		printf("\n");
	}
}

void visitFunc(ALGraph G,int v){
	// 访问图第v个顶点
	printf("%3d",G.vertices[v].data);
}

int firstAdjVex(ALGraph G,int v){
	// 获取图G第v个顶点的第一个相邻点
	if(G.vertices[v].firstarc == NULL)
		return -1;
	return G.vertices[v].firstarc->adjvex;
}

int nextAdjVex(ALGraph G,int v,int flag){
	// 获取图G第v个顶点的第w个相邻点的下一个相邻点
	ArcNode *p;
	p = G.vertices[v].firstarc;
	for(int i=0;i<flag;i++){
		p = p->nextarc;	
		if(p == NULL)
			return -1;
	}
	return p->adjvex;
}

void BFSTraverse(ALGraph G){
	// 广度优先遍历
	int v,u,w,flag;
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
				for(w = firstAdjVex(G,u),flag=0;flag>=0&&w>=0;w = nextAdjVex(G,u,++flag)){
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

void DFS(ALGraph G,int v){
	// 从第v个顶点出发递归地深度优先遍历G
	int flag,w;
	visited[v] = true;
	visitFunc(G,v);
	for(flag=0,w = firstAdjVex(G,v);flag>=0&&w>=0;w = nextAdjVex(G,v,++flag)){
		if(!visited[w])
			DFS(G,w);
	}
}

void DFSTraverse(ALGraph G){
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

int main(){
	ALGraph *G = (ALGraph*)malloc(sizeof(ALGraph));
	int c;
	createGraph(G);
	printf("图的邻接表输出:\n");
	printALGraph(*G);
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
