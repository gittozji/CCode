/**
	�Թ����⡣�����Թ���m��n�й��ɣ���һ����ں�һ�����ڣ��������Ϊ��1,1��	����������Ϊ��m��n����
	����Ʋ���֤�����㷨���ҳ�һ�������ͨ�����ڵ�·�����򱨸�һ�����޷�ͨ������Ϣ����
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define M 17
#define N 17
#define mm 7
#define nn 7
#define STACKINCREMENT 5
#define STACK_INIT_SIZE 50
#define Status int
//��ṹ��
typedef struct Point{
	int x;
	int y;
	int di;
}Point;
//ջ�ṹ��
typedef struct SqStack{
    Point *base;
    Point *top;
    int stacksize;
}SqStack;
//���治��ͨ��ṹ�壨���Ա�
typedef struct SqList{
    Point *elem;
    int length;
    int listsize;
}SqList;
/*��ʼ��SqListʵ���ĺ���*/
int InitList_Sq(SqList* L){
    L->elem=(Point *)malloc(STACK_INIT_SIZE*sizeof(Point));
    if(!L->elem)
        exit(OVERFLOW);
    L->length=0;
    L->listsize=STACK_INIT_SIZE;
    return OK;
}
/*��int����ı�β��������elem*/
int addList(SqList* L,Point elem){
    Point *newbase;
    /*fflush(stdin);*/
    /*ԭint���鳤�Ȳ��������ӿռ����*/
    if(L->length>=L->listsize){
        newbase=(Point *)realloc(L->elem,(L->listsize+STACKINCREMENT)*sizeof(Point));
        if(!newbase)
            exit(OVERFLOW);
        L->elem=newbase;
        L->listsize=L->length;
    }
    L->elem[L->length]=elem;
    L->length++;
    return OK;
}
/*����SqList,1Ϊ����ͨ��0Ϊ��ͨ*/
int seekList(SqList * S,Point p){
	int i=0;
	for(i;i<S->length;i++){
		if(S->elem[i].x==p.x&&S->elem[i].y==p.y)
			return 1;
	}
	return 0;
}
/*��������ʼ��ջ*/
Status initStack(SqStack *S){
    S->base=(Point*)malloc(STACK_INIT_SIZE*sizeof(Point));
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
/*��������ջ*/
Status push(SqStack *S,Point e){
    if((S->top-S->base)>=S->stacksize){
        S->base=(Point*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(Point));
        if(!S->base) exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++ = e;
    return OK;
}
/*��������ջ*/
Status pop(SqStack *S,Point *e){
    if(S->top==S->base) return ERROR;
    *e=*--S->top;
    return OK;
}
/*��������ȡջ��Ԫ��(��û�г�ջ)*/
Point getTop(SqStack *S){
    return *(S->top-1);
}
/*ջ���п�,0Ϊ�գ�1Ϊ�ǿ�*/
int isEmpty(SqStack *S){
	if(S->top==S->base)
		return 0;
	return 1;
}
/*��̬�����Թ�,m�У�n��*/
int newMaze(int maze[M][N],int m,int n){
	int i,j;
	srand((unsigned) time(NULL));
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(i==0||i==(m-1)||j==0||j==(n-1)){
				maze[i][j]=1;
			}else{
				maze[i][j] = rand()%2;
			}
		}
	}
	return OK;
}
Point nextPos(Point current){
	if(current.di==0)
		current.y++;
	if(current.di==1)
		current.x++;
	if(current.di==2)
		current.y--;
	if(current.di==3)
		current.x--;
	current.di=0;
	return current;
}

/*��ӡ�Թ�ͼ*/
void printMaze(int maze[M][N],int m,int n,Point p){
	int i,j;
	printf("\n\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(i==p.x&&j==p.y){
				if(p.di==0)
					printf("%c ",16);
				if(p.di==1)
					printf("%c ",31);
				if(p.di==2)
					printf("%c ",17);
				if(p.di==3)
					printf("%c ",30);
				if(p.di>3)
					printf("%d ",maze[i][j]);
			}
				
			else
				printf("%d ",maze[i][j]);
		}
		printf("\n");
	}
}
/*�Թ�ʵ��,1Ϊ����ͨ��0Ϊ��ͨ*/
int realize(int maze[M][N],Point start,Point end){
	SqList *L = (SqList*)malloc(sizeof(SqList));//����Ѿ��߹��ĵ�
	SqStack* S = (SqStack*)malloc(sizeof(SqStack));//���·��
	InitList_Sq(L);
	initStack(S);
	Point current = start;
	current.di=0;
	do{ 
		if((!seekList(L,current))&&(maze[current.x][current.y]!=1)){//��ǰ����
			addList(L,current);//�������·��
			push(S,current);//��·��ջ
			Sleep(500);
			system("cls");
			printMaze(maze,mm,nn,getTop(S));
			if(current.x==end.x&&current.y==end.y){
				return 0;
			}
			current = nextPos(current);
		}else{
			if(!isEmpty(S))
				break;
			pop(S,&current);
			if(current.di>=3){
				if(!isEmpty(S))
					break;
				pop(S,&current);
			}
			current.di++;
			push(S,current);
			Sleep(500);
			system("cls");
			printMaze(maze,mm,nn,getTop(S));
			
			current=nextPos(current);
		}	
	}while(isEmpty(S));
	return 1;
}




int main(){
	//���������Թ�
	int maze[M][N]={
		{1,1,1,1,1,1,1},
		{1,0,0,0,0,0,1},
		{1,1,1,1,0,1,1},
		{1,1,1,1,0,0,1},
		{1,1,1,1,1,0,1},
		{1,1,1,1,1,0,1},
		{1,1,1,1,1,1,1}
	};
	//���������Թ�
	/*int maze[M][N]={
		{1,1,1,1,1,1,1},
		{1,0,1,0,1,0,1},
		{1,0,0,0,0,1,1},
		{1,0,0,0,1,1,1},
		{1,1,1,1,0,1,1},
		{1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1}
	};*/
	/*���������Թ�
	int maze[M][N]={
		{1,1,1,1,1,1,1},
		{1,0,0,0,0,0,1},
		{1,0,1,1,1,1,1},
		{1,0,0,0,0,1,1},
		{1,1,1,0,0,1,1},
		{1,1,1,0,0,0,1},
		{1,1,1,1,1,1,1}
	};*/
	Point *start,*end;
	int choose;
	printf("1��������ɵ��Թ�   2����Ӳ������Թ�\n");
	scanf("%d",&choose);
	if(choose==1){
		newMaze(maze,mm,nn);
	}
	start=(Point*)malloc(sizeof(Point));
	end=(Point*)malloc(sizeof(Point));
	start->x=1;
	start->y=1;
	end->x=5;
	end->y=5;
	if(realize(maze,*start,*end)){
		printf("\n\n�������ˣ�\n");	
	}else{
		printf("\n\n�Թ��ɹ����ѣ�\n");
	}
	return 0;
}