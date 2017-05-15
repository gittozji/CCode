#include "stdio.h"   
#include "malloc.h"   
  
#define TRUE        1   
#define FALSE       0   
#define OK          1   
#define ERROR       0   
#define INFEASIBLE -1   
#define OVERFLOW    -2   
  
typedef int  Status;  
#define STACK_INIT_SIZE  100   
#define STACKINCREMENT   10   
  
typedef struct{  
    SElemType *base;  
    SElemType *top;  
    int      stacksize;  
}SqStack;  
//����һ����ջ   
Status InitStack(SqStack *S){  
    S->base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));  
  
    if(!S->base)  
        exit(OVERFLOW);  
    S->top=S->base;  
    S->stacksize=STACK_INIT_SIZE;  
    return OK;  
}  
//�ж��Ƿ�Ϊ��ջ   
Status StackEmpty(SqStack S){  
    if(S.top == S.base)  
        return TRUE;  
    else  
        return FALSE;  
}  
//��e����S�Ķ�Ԫ��   
Status GetTop(SqStack S, SElemType *e){  
    if(S.top == S.base)  
        return ERROR;  
    *e = *(S.top-1);  
    return OK;  
}  
//����eΪ�µĶ�Ԫ��   
Status Push(SqStack *S, SElemType e){  
    if((S->top - S->base) >= S->stacksize){  
        S->base = (  
                    SElemType*)realloc(S->base,  
                   (S->stacksize+STACKINCREMENT)*sizeof(SElemType)  
                   );  
        if(!S->base)  
            exit(OVERFLOW);  
        S->top = S->base +S->stacksize;  
        S->stacksize += STACKINCREMENT;  
    }  
    *(S->top)=e;  
    S->top++;  
    return OK;  
}  
//ɾ��S�Ķ�Ԫ�أ�����e������ֵ   
Status Pop(SqStack *S, SElemType *e){  
    if(S->top == S->base)  
        return ERROR;  
    S->top--;  
    *e = *(S->top);  
    return OK;  
}  
//��ջ�׵�ջ�����ζ�S��ÿ��Ԫ�ص��ú���Visit������һ��ʧ�ܲ�����Ч   
Status ListTraverse(SqStack S,Status (*visit)(SElemType)){  
    SElemType *p;  
    p=S.base;  
    for(p=S.base;p<S.top;p++)  
        (*visit)(*p);  
  
    return OK;  
}  
//���Ԫ��e   
Status output(SElemType e){  
    printf("%d ",e);  
  
    return OK;  
} 
