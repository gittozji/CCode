#include<stdlib.h>
#include<stdio.h>
#include"Queue.h"
#define MAX_VERTEX_NUM 20
typedef int VertexType;
typedef int InfoType;
typedef int Status;
typedef enum{DG,DN,UDG,UDN} GraphKind;  //{����ͼ��������������ͼ��������}
bool visited[MAX_VERTEX_NUM];  // ���ʱ�־����

typedef struct ArcNode{  
	int adjvex;  //�û���ָ��Ķ����λ��
	struct ArcNode *nextarc;  //ָ����һ������ָ��
	InfoType info;  //�û������Ϣ��ָ��
}ArcNode;

typedef struct VNode{
	VertexType data;  //������Ϣ
	ArcNode *firstarc;  //ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;  
	int vexnum,arcnum;  //ͼ�ĵ�ǰ�������ͻ���
	int kind;  //ͼ�������־
}ALGraph;

int locateVex(ALGraph G,int v){  // ȷ����v��ͼ����������λ��
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
		p->adjvex = locateVex(*G,v2);   //p->adjvex��v2�ڱ�ͷ������λ��
		p->info = weight;  //��Ȩֵ
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
	//��������ͼ
	printf("���躯����\n");
	return OK;
}

Status createDN(ALGraph *G){
	int v1,v2,weight;
	//����������
	printf("���붥�㡢��������\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("����%d������\n",G->vexnum);
	for(int i=0;i<G->vexnum;i++){  //�����ͷ����
		scanf("%d",&G->vertices[i].data);  //���붥��ֵ
		G->vertices[i].firstarc=NULL;
	}
	for(int k=0;k<G->arcnum;k++){
		printf("����һ�����������������㼰��Ȩֵ(��һ����ָ��ڶ�����):");
		scanf("%d%d%d",&v1,&v2,&weight);
		addArcNode(G,v1,v2,weight);  //���뻡
			
	}
	return OK;
}
Status createUDG(ALGraph *G){
	//��������ͼ
	printf("���躯����\n");
	return OK;
}
Status createUDN(ALGraph *G){
	//����������
	int v1,v2,weight;
	//����������
	printf("���붥�㡢��������\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	printf("����%d������\n",G->vexnum);
	for(int i=0;i<G->vexnum;i++){  //�����ͷ����
		scanf("%d",&G->vertices[i].data);  //���붥��ֵ
		G->vertices[i].firstarc=NULL;
	}
	for(int k=0;k<G->arcnum;k++){
		printf("����һ�����������������㼰��Ȩֵ(û���Ⱥ�˳��):");
		scanf("%d%d%d",&v1,&v2,&weight);
		addArcNode(G,v1,v2,weight);
		addArcNode(G,v2,v1,weight);
	}
	return OK;
}

Status createGraph(ALGraph *G){
	printf("����ͼ�����͹����ڽӱ�0-DG,1-DN,2-UDG,3-UDN\n");
	scanf("%d",&G->kind);
	switch(G->kind){
		case DG: return createDG(G);
		case DN: return createDN(G);
		case UDG: return createUDG(G);
		case UDN: return createUDN(G);
		default:return ERROR;
	}
}

void printALGraph(ALGraph G){  // ��ӡ�ڽӱ�
	ArcNode* p;
	for(int i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		printf("%d:  ",G.vertices[i].data);
		while(p!=NULL){
			printf("��:%d Ȩ:%d ----> ",G.vertices[p->adjvex].data,p->info);
			p=p->nextarc;
		}
		printf("\n");
	}
}

void visitFunc(ALGraph G,int v){
	// ����ͼ��v������
	printf("%3d",G.vertices[v].data);
}

int firstAdjVex(ALGraph G,int v){
	// ��ȡͼG��v������ĵ�һ�����ڵ�
	if(G.vertices[v].firstarc == NULL)
		return -1;
	return G.vertices[v].firstarc->adjvex;
}

int nextAdjVex(ALGraph G,int v,int flag){
	// ��ȡͼG��v������ĵ�w�����ڵ����һ�����ڵ�
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
	// ������ȱ���
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
	// �ӵ�v����������ݹ��������ȱ���G
	int flag,w;
	visited[v] = true;
	visitFunc(G,v);
	for(flag=0,w = firstAdjVex(G,v);flag>=0&&w>=0;w = nextAdjVex(G,v,++flag)){
		if(!visited[w])
			DFS(G,w);
	}
}

void DFSTraverse(ALGraph G){
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

int main(){
	ALGraph *G = (ALGraph*)malloc(sizeof(ALGraph));
	int c;
	createGraph(G);
	printf("ͼ���ڽӱ����:\n");
	printALGraph(*G);
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
