/**

	�����Դ�ͷ���ĵ���ѭ�������ʾ���У�����ֻ��һ��ָ��ָ��һ����βԪ�ؽ�㣨ע�⣺����ͷָ�룩��
	����Ʋ���֤��Ӧ�ö��г�ʼ���������пա�����С������кͱ��������㷨��

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
/*��ʼ������*/
int initQueue(Queueptr Q){
	Q->head = (Dataptr)malloc(sizeof(Data));
	if(!Q->head)
		exit(OVERFLOW);
	Q->head->next=Q->head;
	return OK;
}
/*�пգ�1Ϊ�ǿգ�0Ϊ��*/
int isEmpty(Queueptr Q){
	if(Q->head->next==Q->head)
		return 0;
	return 1;
}
/*�����*/
int enQueue(Queueptr Q,int e){
	Dataptr D = (Dataptr)malloc(sizeof(Data));
	D->value=e;
	D->next=Q->head->next;
	Q->head->next=D;
	Q->head=D;
	return OK;
}
/*������*/
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
/*��������*/
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
	printf("������Ԫ��Ϊ��%d\n",e);
	if(isEmpty(Q))
		printf("���в�Ϊ��\n");
	else
		printf("����Ϊ��\n");
	lookQueue(Q);
	return 0;
}