/*
 *������ʽ��ֵ
 *ֻ������int����ֵ
 *
 */

/***************************�ݴ���************************************

1��int������char���͵��໥ת�����ϸ�
int main(){
    char c = (char)43;
    printf("%c",c);
    getch();
    return 0;
}
2������ջ���ϸ�
int main(){
    SqStack *OPND=NULL;
    int *e=NULL;
    initStack(OPND);
    push(OPND,1);
    push(OPND,2);
    push(OPND,3);
    push(OPND,4);
    pop(OPND,e);
    printf("%d",*e);
    printf("%d",getTop(OPND));
    getch();
    return 0;
}
3�����ԱȽ���������ȼ��������ϸ�
int main(){
    printf("%c",precede('#','+'));
    printf("%c",precede('#','-'));
    printf("%c",precede('#','*'));
    printf("%c",precede('#','/'));
    printf("%c",precede('#','('));
    printf("%c",precede('#',')'));
    printf("%c",precede('#','#'));
    getch();
    return 0;
}
4������operate�������ϸ�
int main(){
    printf("%d ",operate(2,'*',3));
    getch();
    return 0;
}

*********************************************************************/

#include<stdio.h>
#define SElemType int
#define ElemType char
#define Status int
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALUSE 0
/*ջ�ṹ��ȡ��ΪSqStack*/
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
/*��������ʼ��ջ*/
Status initStack(SqStack *S){
    S->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
/*��������ջ*/
Status push(SqStack *S,SElemType e){
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
Status pop(SqStack *S,SElemType *e){
    if(S->top==S->base) return ERROR;
    *e=*--S->top;
    return OK;
}
/*��������ȡջ��Ԫ��*/
SElemType getTop(SqStack *S){
    return *(S->top-1);
}


/*�������Ƚ���������ȼ�*/
char precede(char a,char b){
    int aIndex=0,bIndex=0;
    char T[7][7]={
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}};
    switch(a){
        case '+':aIndex=0;break;
        case '-':aIndex=1;break;
        case '*':aIndex=2;break;
        case '/':aIndex=3;break;
        case '(':aIndex=4;break;
        case ')':aIndex=5;break;
        case '#':aIndex=6;break;
    }
    switch(b){
        case '+':bIndex=0;break;
        case '-':bIndex=1;break;
        case '*':bIndex=2;break;
        case '/':bIndex=3;break;
        case '(':bIndex=4;break;
        case ')':bIndex=5;break;
        case '#':bIndex=6;break;
    }
    return T[aIndex][bIndex];
}
/*����������*/
/* 43:+,45:-,42:*,47:/,40:(,41:),35:#*/
SElemType operate(SElemType a,SElemType theta,SElemType b){
    if(theta == '+')
        return a+b;
    if(theta == '-')
        return a-b;
    if(theta == '*')
        return a*b;
    if(theta == '/')
        return a/b;
}
/*�������ַ�����̬�����ѵ㣬����ʵ�֣�*/
/*Ϊ0ʱ����ֵ��Ϊ1ʱ�������*/
int dealChar(SElemType *values){
    char c;
    *values=0;
    c = getchar();
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#'){
        *values=(SElemType)c;
        return 1;
    }
    while(c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='('&&c!=')'&&c!='#'){
        *values=(*values)*10+(c-'0');
        c=getchar();
    }
    ungetc(c,stdin);/*�Żػ�����*/
    return 0;
}
/*������������ջ�ĺ��Ĵ���*/
int evaluateExpression(){
    int c,a,b,x,theta,flag;
    SqStack *OPTR=NULL,*OPND=NULL;
    OPTR=(SqStack*)malloc(sizeof(SqStack));
    OPND=(SqStack*)malloc(sizeof(SqStack));
    initStack(OPTR);
    initStack(OPND);
    push(OPTR,'#');
    flag=dealChar(&c);
    while(c!='#'||getTop(OPTR)!='#'){
        if(flag==0){
            push(OPND,c);
            flag=dealChar(&c);
        }
        else{
            switch(precede(getTop(OPTR),c)){
                case '<':push(OPTR,c);
                    flag=dealChar(&c);
                    break;
                case '=':pop(OPTR,&x);
                    flag=dealChar(&c);
                    break;
                case '>':pop(OPTR,&theta);
                    pop(OPND,&b);
                    pop(OPND,&a);
                    push(OPND,operate(a,theta,b));
                    break;
            }
        }
    }
    return getTop(OPND);
}
int main(){


    printf("%d",evaluateExpression());
    getch();
    return 0;
}
