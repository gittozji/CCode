/**
	迷宫问题。假设迷宫由m行n列构成，有一个入口和一个出口，入口坐标为（1,1）	，出口坐标为（m，n），
	试设计并验证以下算法：找出一条从入口通往出口的路径，或报告一个“无法通过的信息”。
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
//点结构体
typedef struct Point{
	int x;
	int y;
	int di;
}Point;
//栈结构体
typedef struct SqStack{
    Point *base;
    Point *top;
    int stacksize;
}SqStack;
//保存不可通点结构体（线性表）
typedef struct SqList{
    Point *elem;
    int length;
    int listsize;
}SqList;
/*初始化SqList实例的函数*/
int InitList_Sq(SqList* L){
    L->elem=(Point *)malloc(STACK_INIT_SIZE*sizeof(Point));
    if(!L->elem)
        exit(OVERFLOW);
    L->length=0;
    L->listsize=STACK_INIT_SIZE;
    return OK;
}
/*在int数组的表尾加入数据elem*/
int addList(SqList* L,Point elem){
    Point *newbase;
    /*fflush(stdin);*/
    /*原int数组长度不够，增加空间分配*/
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
/*遍历SqList,1为不可通，0为可通*/
int seekList(SqList * S,Point p){
	int i=0;
	for(i;i<S->length;i++){
		if(S->elem[i].x==p.x&&S->elem[i].y==p.y)
			return 1;
	}
	return 0;
}
/*函数：初始化栈*/
Status initStack(SqStack *S){
    S->base=(Point*)malloc(STACK_INIT_SIZE*sizeof(Point));
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
/*函数：进栈*/
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
/*函数：出栈*/
Status pop(SqStack *S,Point *e){
    if(S->top==S->base) return ERROR;
    *e=*--S->top;
    return OK;
}
/*函数：获取栈顶元素(并没有出栈)*/
Point getTop(SqStack *S){
    return *(S->top-1);
}
/*栈的判空,0为空，1为非空*/
int isEmpty(SqStack *S){
	if(S->top==S->base)
		return 0;
	return 1;
}
/*动态生成迷宫,m行，n列*/
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

/*打印迷宫图*/
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
/*迷宫实现,1为不可通，0为可通*/
int realize(int maze[M][N],Point start,Point end){
	SqList *L = (SqList*)malloc(sizeof(SqList));//存放已经走过的点
	SqStack* S = (SqStack*)malloc(sizeof(SqStack));//存放路径
	InitList_Sq(L);
	initStack(S);
	Point current = start;
	current.di=0;
	do{ 
		if((!seekList(L,current))&&(maze[current.x][current.y]!=1)){//当前可行
			addList(L,current);//标记已走路径
			push(S,current);//进路径栈
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
	//出得来的迷宫
	int maze[M][N]={
		{1,1,1,1,1,1,1},
		{1,0,0,0,0,0,1},
		{1,1,1,1,0,1,1},
		{1,1,1,1,0,0,1},
		{1,1,1,1,1,0,1},
		{1,1,1,1,1,0,1},
		{1,1,1,1,1,1,1}
	};
	//出不来的迷宫
	/*int maze[M][N]={
		{1,1,1,1,1,1,1},
		{1,0,1,0,1,0,1},
		{1,0,0,0,0,1,1},
		{1,0,0,0,1,1,1},
		{1,1,1,1,0,1,1},
		{1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1}
	};*/
	/*出得来的迷宫
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
	printf("1、随机生成的迷宫   2、用硬编码的迷宫\n");
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
		printf("\n\n出不来了！\n");	
	}else{
		printf("\n\n迷宫成功逃脱！\n");
	}
	return 0;
}