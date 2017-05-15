#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define ElemType int
#define mallD (Data*)malloc(sizeof(Data))
#define mallQ (Queue*)malloc(sizeof(Queue))
/**
	1、测试链队列。合格 ！ 
	initQueue(Q);
	enQueue(Q,1);
	enQueue(Q,2);
	enQueue(Q,3);
	deQueue(Q,&e);
	printf("%d\n",e);
	deQueue(Q,&e);
	printf("%d\n",e);
	deQueue(Q,&e);
	printf("%d\n",e);
*/
typedef struct Data{
	ElemType data;
	struct Data* next;
}Data;
typedef struct Queue{
	Data* front;
	Data* rear;
}Queue;
ElemType initQueue(Queue* Q){
	Q->front = Q->rear = mallD;
	if(!Q->front) exit(OVERFLOW);
	Q->front->next=NULL;
	return OK;
}
ElemType enQueue(Queue* Q,ElemType e){
	Data* p = mallD;
	if(!p) exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q->rear->next=p;
	Q->rear=p;
	return OK;
}
ElemType deQueue(Queue* Q,ElemType* e){
	if(Q->front==Q->rear)
		return ERROR;
	Data* d = Q->front->next;
	*e=d->data;
	Q->front->next=d->next;
	if(Q->rear==d) Q->rear=Q->front;
	free(d);
	return OK;
}
ElemType pascal(int number){
	Queue *Q;
	int s=0,t,i,j;//number为杨辉三角行数，s为上一次出队列的数，t为此次出队列的数，i和j为for循环计数变量。 
	initQueue(Q);
	
	enQueue(Q,1);
	enQueue(Q,1);
	for(j=0;j<=number;j++){
			printf("   ");
	}
	printf("  1");
	number--;
	for(i=0;i<number;i++){//第一层为控制层数 
		printf("\n");
		for(j=i;j<number;j++){
			printf("   ");
		}
		enQueue(Q,0);
		for(j=0;j<=i+2;j++){
			deQueue(Q,&t);
			enQueue(Q,t+s);
			s=t;
			if(j!=i+2)
				printf("%6d",t);				
		}
	}
}
int main(){
	int number;
	printf("输入欲打印杨辉三角的行数:\n");
	scanf("%d",&number);
	pascal(number);
	printf("\n\n\n\n\n\n\n");
	return 0;
}
