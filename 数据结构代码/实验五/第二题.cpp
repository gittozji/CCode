#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct T{
	int value,x,y;
}T;
typedef struct A{
	T data[100];
}A;
typedef struct E{
	int e[100][100];
	int x,y;
}E;
E* initE(int x,int y){
	int i,j;
	E* e=(E*)malloc(sizeof(E));
	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			e->e[i][j]=0;
	e->x=x;
	e->y=y;
	return e;
}
void exchangeForE(A* a,E* e){
	int i;
	for(i=1;i<=a->data[0].value;i++){
		e->e[a->data[i].x-1][a->data[i].y-1]=a->data[i].value;
	}
	e->x=a->data[0].x;
	e->y=a->data[0].y;
}
//��ʼ����Ԫ��
A* initA(int x,int y){
	int count=0,i,j,temp;
	A* a=(A*)malloc(sizeof(A));
	a->data[0].x=x;
	a->data[0].y=y;
	for(i=1;i<=x;i++){
		for(j=1;j<=y;j++){
			if((temp=rand()%10)!=0){
				a->data[++count].value=temp;
				a->data[count].x=i;
				a->data[count].y=j;
			}
		}
	}
	a->data[0].value=count;
	return a;
}
void printE(E* e){
	int i,j;
	for(i=0;i<e->x;i++){
		for(j=0;j<e->y;j++)
			printf("%3d",e->e[i][j]);
		printf("\n");
	}
	printf("\n");
}
//��ӡ��Ԫ��
void printA(A* a){
	int i;
	for(i=0;i<=a->data[0].value;i++){
		printf("%3d%3d%3d\n",a->data[i].x,a->data[i].y,a->data[i].value);
	}
	printf("\n");
}
//������
int horse(A* a){
	int i,zero_x[100],zero_y[100];
	T min[100],max[100];
	
	/*****�����з����������zero_x��zero_y��******/
	for(i=1;i<=a->data[0].x;i++)
		zero_x[i]=0;
	for(i=1;i<=a->data[0].y;i++)
		zero_y[i]=0;
	for(i=1;i<=a->data[0].value;i++){
		zero_x[a->data[i].x]++;
		zero_y[a->data[i].y]++;
	}
	/*********��min��max�ֱ���Ϊx��y���Ԫ��*********/
	max[0].x=0;
	min[0].y=0;//y��0�򲻿��ܱ�����Ϊ����
	for(i=1;i<=a->data[0].value;i++){
		min[a->data[i].x]=a->data[i];
		max[a->data[i].y]=a->data[i];
	}
	for(i=1;i<=a->data[0].value;i++){
		if(min[a->data[i].x].value>a->data[i].value)
			min[a->data[i].x]=a->data[i];
		if(max[a->data[i].y].value<a->data[i].value)
			max[a->data[i].y]=a->data[i];
	}
	//��������ʱ��ֱ����valueΪ0����0�����ܳ�Ϊ����
	for(i=1;i<=a->data[0].x;i++){
		if(zero_x[i]<a->data[0].x)
			min[i].y=0;
	}
	for(i=1;i<a->data[0].value;i++){
		if(min[a->data[i].x].value==a->data[i].value&&min[a->data[i].x].y!=a->data[i].y)
			min[a->data[i].x].y=0;
	}
	for(i=1;i<a->data[0].value;i++){
		if(max[a->data[i].y].value==a->data[i].value&&max[a->data[i].y].x!=a->data[i].x)
			max[a->data[i].y].x=0;
	}
	for(i=1;i<a->data[0].x;i++){
		if(max[min[i].y].x==i){
			printf("����%d,%d,%d\n",min[i].x,min[i].y,min[i].value);
			return 1;
		}
	}
	return 0;
}
int main(){
	A *a=NULL,*t=NULL,*a_t=NULL;
	int x=0,y=0;
	srand((unsigned) time(NULL));
	printf("��������С��\n");
	scanf("%d%d",&x,&y);
	do{
	a = initA(x,y);
	printf("������ɵ���Ԫ�飺\n");
	printA(a);
	E* e = initE(x,y);
	exchangeForE(a,e);
	printE(e);
	}while(horse(a)!=1);
	
	return 0;
}
