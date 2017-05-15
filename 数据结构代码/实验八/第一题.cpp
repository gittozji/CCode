#include<stdlib.h>
#include<stdio.h>
#include"Queue.h"

#define INFINITY INT_MAX   // ���ֵ��
#define MAX_VERTEX_NUM 20  // ��󶥵���
typedef enum{DG,DN,UDG,UDN} GraphKind;  //{����ͼ��������������ͼ��������}
typedef int VertexType;
typedef int VRType;
typedef int InfoType;
typedef int Status;
bool visited[MAX_VERTEX_NUM];  // ���ʱ�־����

typedef struct ArcCell {
	VRType adj;  // VRType�Ƕ����ϵ���͡�����Ȩͼ����1��0
				 // ��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ���͡�
	InfoType *info;  // �û������Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];  // ��������
	AdjMatrix arcs;  // �ڽӾ���
	int vexnum,arcnum;  // ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;  // ͼ�������־
}MGraph;

int locateVex(MGraph G,int v){  // ȷ����v��ͼ����������λ��
	int i;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==v)
			return i;
	}
	return -1;
}

Status createDG(MGraph *G){
	int v1,v2;
	//��������ͼ
	printf("���붥�㡢��������\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("����%d������\n",G->vexnum);
	for(int i=0;i<G->vexnum;i++){  
		scanf("%d",&G->vexs[i]);   // ���춥������
	}
	for(int j=0;j<G->vexnum;j++){   // ��ʼ���ڽӾ���
		for(int k=0;k<G->vexnum;k++){
			G->arcs[j][k].adj = 0;
			G->arcs[j][k].info = NULL;
		}
	}
	for(int p=0;p<G->arcnum;p++){  //�����ڽӾ���
		printf("����һ������������������(��һ����ָ��ڶ�����):");
		scanf("%d%d",&v1,&v2);
		G->arcs[locateVex(*G,v1)][locateVex(*G,v2)].adj = 1;
	}
	return OK;
}
Status createDN(MGraph *G){
	 //����������
	printf("���躯����\n");
	return OK;
}
Status createUDG(MGraph *G){
	//��������ͼ
	int v1,v2;
	//��������ͼ
	printf("���붥�㡢��������\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("����%d������\n",G->vexnum);
	for(int i=0;i<G->vexnum;i++){  
		scanf("%d",&G->vexs[i]);   // ���춥������
	}
	for(int j=0;j<G->vexnum;j++){   // ��ʼ���ڽӾ���
		for(int k=0;k<G->vexnum;k++){
			G->arcs[j][k].adj = 0;
			G->arcs[j][k].info = NULL;
		}
	}
	for(int p=0;p<G->arcnum;p++){  //�����ڽӾ���
		printf("����һ������������������(û���Ⱥ�˳��):");
		scanf("%d%d",&v1,&v2);
		G->arcs[locateVex(*G,v1)][locateVex(*G,v2)].adj = 1;
		G->arcs[locateVex(*G,v2)][locateVex(*G,v1)].adj = 1;
	}
	return OK;
}
Status createUDN(MGraph *G){
	//����������
	printf("���躯����\n");
	return OK;
}

void printMatrix(MGraph G){
	//���ͼ
	int i,j;
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++){
			printf("%3d",G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

void visitFunc(MGraph G,int v){
	// ����ͼ��v������
	printf("%3d",G.vexs[v]);
}
int firstAdjVex(MGraph G,int v){
	// ��ȡͼG��v������ĵ�һ�����ڵ�
	for(int i=0;i<G.vexnum;i++){
		if(G.arcs[v][i].adj == 1)
			return i;
	}
	return -1;
}

int nextAdjVex(MGraph G,int v,int w){
	// ��ȡͼG��v������ĵ�w�����ڵ����һ�����ڵ�
	for(++w;w<G.vexnum;w++){
		if(G.arcs[v][w].adj == 1)
			return w;
	}
	return -1;
}

void DFS(MGraph G,int v){
	// �ӵ�v����������ݹ��������ȱ���G
	visited[v] = true;
	visitFunc(G,v);
	for(int w = firstAdjVex(G,v);w>=0;w=nextAdjVex(G,v,w)){
		if(!visited[w])
			DFS(G,w);
	}
}

void BFSTraverse(MGraph G){
	// ������ȱ���
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
	//�������
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
	printf("����ͼ�����͹����ڽӾ���0-DG,1-DN,2-UDG,3-UDN\n");
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
	printf("ͼ�ľ��������\n");
	printMatrix(*G);
	while(1){
		printf("\n1-��ȣ�2-���\n");
		scanf("%d",&c);
		switch(c){
		case 1:
			printf("������ȱ���ͼ��\n");
			DFSTraverse(*G);
			break;
		case 2:
			printf("������ȱ���ͼ��\n");
			BFSTraverse(*G);
			break;
		}
	}
	return 0;
}