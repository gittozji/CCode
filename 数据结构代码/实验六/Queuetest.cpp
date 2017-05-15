#include <stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2        
typedef int Status;           //函数结果状态代码

typedef struct{
	int *base;
	int front,rear;
}Queue;
Status initQueue(Queue *q){
	q->base = (int*)malloc(MAXSIZE*sizeof(int));
	if(!(q->base)) exit (OVERFLOW);
	q->front=q->rear=0;
	return OK;
}
int queueLength(Queue q){
	return (q.rear-q.front+MAXSIZE)%MAXSIZE;
}
Status enQueue(Queue *q,int e){
	if((q->rear+1)%MAXSIZE==q->front) return ERROR;
	q->base[q->rear]=e;
	q->rear=(q->rear+1)%MAXSIZE;
	return OK;
}
Status deQueue(Queue *q,int *e){
	if(q->front==q->rear) return ERROR;
	*e=q->base[q->front];
	q->front=(q->front+1)%MAXSIZE;
	return OK;
}
