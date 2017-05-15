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
A* initA(int x,int y,int bi){
	int count=0,i,j,temp;
	A* a=(A*)malloc(sizeof(A));
	a->data[0].x=x;
	a->data[0].y=y;
	for(i=1;i<=x;i++){
		for(j=1;j<=y;j++){
			if((rand()%100)<bi){
				temp=(rand()%9)+1;
				a->data[++count].value=temp;
				a->data[count].x=i;
				a->data[count].y=j;
			}
				
		}
	}
	a->data[0].value=count;
	return a;
}
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
void soFar(A* a,A* t){
	int col[100],cptr[100],i;
	for(i=0;i<a->data[0].y;i++)
		col[i]=0;
	cptr[0]=1;
	for(i=1;i<=a->data[0].value;i++){
		col[a->data[i].y-1]++;
	}
	for(i=1;i<a->data[0].y;i++){
		cptr[i]=cptr[i-1]+col[i-1];
	}
	for(i=1;i<=a->data[0].value;i++){
		t->data[cptr[a->data[i].y-1]].value=a->data[i].value;
		t->data[cptr[a->data[i].y-1]].x=a->data[i].y;
		t->data[cptr[a->data[i].y-1]].y=a->data[i].x;
		cptr[a->data[i].y-1]++;
	}
	t->data[0].x=a->data[0].y;
	t->data[0].y=a->data[0].x;
	t->data[0].value=a->data[0].value;
}
int compere(int a,int b,int c,int d){
	if(a==c&&b==d)
		return 0;
	if(a>c||(a==c&&b>d))
		return 1;
	return -1;
}
void add(A* a,A* t,A* a_t){
	int count=0,flag_a=1,flag_t=1;
	while(flag_a<=a->data[0].value&&flag_t<=t->data[0].value){
		switch(compere(a->data[flag_a].x,a->data[flag_a].y,t->data[flag_t].x,t->data[flag_t].y)){
		case 0: a_t->data[++count].value=a->data[flag_a].value+t->data[flag_t++].value;
			    a_t->data[count].x=a->data[flag_a].x;
				a_t->data[count].y=a->data[flag_a++].y;
				break;
		case 1: a_t->data[++count].value=t->data[flag_t].value;
			     a_t->data[count].x=t->data[flag_t].x;
				 a_t->data[count].y=t->data[flag_t++].y;
				 break;
		case -1: a_t->data[++count].value=a->data[flag_a].value;
			    a_t->data[count].x=a->data[flag_a].x;
				a_t->data[count].y=a->data[flag_a++].y;
				break;
		}
	}
	while(flag_t<=t->data[0].value){
		a_t->data[++count].value=t->data[flag_t].value;
		a_t->data[count].x=t->data[flag_t].x;
		a_t->data[count].y=t->data[flag_t].y;
	}
	while(flag_a<=a->data[0].value){
		a_t->data[++count].value=a->data[flag_a].value;
		a_t->data[count].x=a->data[flag_a].x;
		a_t->data[count].y=a->data[flag_a++].y;
	}
	a_t->data[0].value=count;
}

void printA(A* a){
	int i;
	for(i=0;i<=a->data[0].value;i++){
		printf("%3d%3d%3d\n",a->data[i].x,a->data[i].y,a->data[i].value);
	}
	printf("\n");
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

int main(){
	A *a=NULL,*t=NULL,*a_t=NULL;
	E *e = NULL;
	int x,y,bi;
	srand((unsigned) time(NULL));
	printf("输入矩阵大小及非零概率（百分制）：\n");
	scanf("%d%d%d",&x,&y,&bi);
	a = initA(x,y,bi);
	t = initA(x,y,bi);
	printf("随机生成的三元组：\n");
	printA(a);
	soFar(a,t);
	printf("快速转置得到：\n");
	printA(t);
	a_t=initA(x,y,bi);
	add(a,t,a_t);
	printf("相加得到：\n");
	printA(a_t);
	e = initE(x,y);
	exchangeForE(a_t,e);
	printf("三元组转化成矩阵：\n");
	printE(e);
	return 0;
}
