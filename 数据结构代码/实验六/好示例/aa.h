#include <stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2        
typedef int Status;           //函数结果状态代码
typedef BiTNode QElemType;     //定义队列中的数据元素类型

typedef struct{               //定义队列中的数据类型
	QElemType *base;
	int front,rear;
}Queue;
Status initQueue(Queue *q){
	q->base = (QElemType*)malloc(MAXSIZE*sizeof(QElemType));
	if(!(q->base)) exit (OVERFLOW);
	q->front=q->rear=0;
	return OK;
}
int queueLength(Queue q){
	return (q.rear-q.front+MAXSIZE)%MAXSIZE;
}
Status enQueue(Queue *q,QElemType e){
	if((q->rear+1)%MAXSIZE==q->front) return ERROR;
	q->base[q->rear]=e;
	q->rear=(q->rear+1)%MAXSIZE;
	return OK;
}
Status deQueue(Queue *q,QElemType *e){
	if(q->front==q->rear) return ERROR;
	*e=q->base[q->front];
	q->front=(q->front+1)%MAXSIZE;
	return OK;
}
