#include<stdlib.h>
#include<stdio.h>
#define Status int
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALUSE 0
/*栈结构体取名为Stack*/
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}Stack;
/*函数：初始化栈*/
Status initStack(Stack *S){
    S->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
/*函数：进栈*/
Status push(Stack *S,SElemType e){
    if((S->top-S->base)>=S->stacksize){
        S->base=(SElemType*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!S->base) exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++ = e;
    return OK;
}
/*函数：出栈*/
Status pop(Stack *S,SElemType *e){
    if(S->top==S->base) return ERROR;
    *e=*--S->top;
    return OK;
}
/*函数：获取栈顶元素*/
SElemType getTop(Stack *S){
    return *(S->top-1);
}