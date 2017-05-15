/**

	假设以带头结点的单向循环链表表示队列，并且只设一个指针指向一个队尾元素结点（注意：不设头指针），
	试设计并验证相应得队列初始化、队列判空、入队列、出队列和遍历队列算法。

*/
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROE 0
#define OVERFLOW -2
typedef struct Data{
	int value;
	struct Data* next;
}Data,*Dataptr;
typedef struct Queue{
	Dataptr head;
}Queue,*Queueptr;
/*初始化队列*/
int initQueue(Queueptr Q){
	Q->head = (Dataptr)malloc(sizeof(Data));
	if(!Q->head)
		exit(OVERFLOW);
	Q->head->next=Q->head;
	return OK;
}
/*判空，1为非空，0为空*/
int isEmpty(Queueptr Q){
	if(Q->head->next==Q->head)
		return 0;
	return 1;
}
/*入队列*/
int enQueue(Queueptr Q,int e){
	Dataptr D = (Dataptr)malloc(sizeof(Data));
	D->value=e;
	D->next=Q->head->next;
	Q->head->next=D;
	Q->head=D;
	return OK;
}
/*出队列*/
int deQueue(Queueptr Q,int* e){ 
	Dataptr D;
    if(Q->head->next==Q->head)
		return 0;
	D=Q->head->next->next;
	*e=D->value;
    Q->head->next->next=D->next;
	if(Q->head==D){
		Q->head->next=Q->head->next->next;
		Q->head=Q->head->next;
    }
	free(D);
	return OK;
}
/*遍历队列*/
int lookQueue(Queueptr Q){
	Dataptr D = Q->head;
	Dataptr current_D=Q->head->next;
	do{
		current_D=current_D->next;
		printf("%d\n",current_D->value);
	}while(current_D!=D);
	return OK;
}
int main(){
	int e;
	Queueptr Q = (Queueptr)malloc(sizeof(Queue));
	initQueue(Q);
	enQueue(Q,1);
	enQueue(Q,2);
	enQueue(Q,3);
	enQueue(Q,4);
	enQueue(Q,5);
	deQueue(Q,&e);
	printf("出队列元素为：%d\n",e);
	if(isEmpty(Q))
		printf("队列不为空\n");
	else
		printf("队列为空\n");
	lookQueue(Q);
	return 0;
}