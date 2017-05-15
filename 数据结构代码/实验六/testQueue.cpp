#include<stdlib.h>
#include<stdio.h>
#include"Queuetest.cpp"

int main(){
	int e;
	Queue *q=(Queue*)malloc(sizeof(Queue));
	initQueue(q);
	for(int i=0;i<100;i++)
		enQueue(q,i);
	for(i=0;i<100;i++){
		deQueue(q,&e);
		printf("%d \n",e);
	}for(i=0;i<100;i++)
		enQueue(q,i);
	for(i=0;i<100;i++){
		deQueue(q,&e);
		printf("%d \n",e);
	}
	return 0;
}