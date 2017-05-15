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
/*ջ�ṹ��ȡ��ΪStack*/
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}Stack;
/*��������ʼ��ջ*/
Status initStack(Stack *S){
    S->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
/*��������ջ*/
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
/*��������ջ*/
Status pop(Stack *S,SElemType *e){
    if(S->top==S->base) return ERROR;
    *e=*--S->top;
    return OK;
}
/*��������ȡջ��Ԫ��*/
SElemType getTop(Stack *S){
    return *(S->top-1);
}