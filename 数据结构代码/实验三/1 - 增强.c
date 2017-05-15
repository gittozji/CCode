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
#include<math.h>
#define SElemType Key
#define Status int
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALUSE 0
/*ջ�ṹ��ȡ��ΪSqStack*/
typedef struct Key{
	float value;
	char operated;
}Key;
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
	SElemType *e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	e->operated='0';
    if(theta.operated == '+')
    	e->value=a.value+b.value;
    if(theta.operated == '-')
        e->value=a.value-b.value;
    if(theta.operated == '*')
        e->value=a.value*b.value;
    if(theta.operated == '/')
        e->value=a.value/b.value;
    return *e;
}
/*�������ַ�����̬�����ѵ㣬����ʵ�֣�*/
/*Ϊ0ʱ����ֵ��Ϊ1ʱ�������*/
int dealChar(SElemType *values){
    char c;
    values->value=0;
    values->operated='0';
    c = getchar();
    int digit=1;
    int judge=0;//0Ϊû�������㣬1Ϊ������ 
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#'){
        values->operated=c;
        return 1;
    }
    while(c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='('&&c!=')'&&c!='#'&&c!='.'){
        values->value=(values->value)*10+(c-'0');
        c=getchar();
        if(c=='.'){
        	judge=1;
        	c=getchar();
        	break;
        }
    }
    while(c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='('&&c!=')'&&c!='#'&&judge){
        values->value=(values->value)+(float)(c-'0')/pow(10,digit++);
        c=getchar();
    }
    ungetc(c,stdin);/*�Żػ�����*/
    return 0;
}
/*������������ջ�ĺ��Ĵ���*/
float evaluateExpression(){
    int flag;
    SElemType *e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    SElemType *x = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    SElemType *theta = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    SElemType *a = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    SElemType *b = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    SqStack *OPTR=NULL,*OPND=NULL,*NIBOLAN=NULL,*NIBOLAN1=NULL;
    OPTR=(SqStack*)malloc(sizeof(SqStack));
    OPND=(SqStack*)malloc(sizeof(SqStack));
    NIBOLAN=(SqStack*)malloc(sizeof(SqStack));//�沨�� 
    NIBOLAN1=(SqStack*)malloc(sizeof(SqStack));//�沨�� 1
    initStack(OPTR);
    initStack(OPND);
    initStack(NIBOLAN);//�沨�� 
    initStack(NIBOLAN1);//�沨�� 1
    e->operated='#';
    push(OPTR,*e);
    push(NIBOLAN,*e);//�沨�� 
    push(NIBOLAN1,*e);
    e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    printf("������ʽ��\n");
    flag=dealChar(e);
    while(e->operated!='#'||getTop(OPTR).operated!='#'){
        if(flag==0){
            push(OPND,*e);
            push(NIBOLAN,*e);//�沨�� 
            e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
            flag=dealChar(e);
        }
        else{
            switch(precede(getTop(OPTR).operated,e->operated)){
                case '<':push(OPTR,*e);
                	e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
                    flag=dealChar(e);
                    break;
                case '=':pop(OPTR,x);
                	e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
                    flag=dealChar(e);
                    break;
                case '>':pop(OPTR,theta);
                	push(NIBOLAN,*theta);//�沨�� 
                    pop(OPND,b);
                    pop(OPND,a);
                    push(OPND,operate(*a,*theta,*b));
                    break;
            }
        }
    }
    printf("�沨����ʽ��\n");
    e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	pop(NIBOLAN,e);
   	while(e->operated!='#'){
    	if(e->operated!='0'){
	    	printf("%c\n",e->operated);
	    	push(NIBOLAN1,*e);
	    }	
    	else{
	    	printf("%f\n",e->value);
	    	push(NIBOLAN1,*e);
	    }	
   		e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   		pop(NIBOLAN,e);
    }
    printf("\nת�ã�\n");
    e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   		pop(NIBOLAN1,e);
   	while(e->operated!='#'){
    	if(e->operated!='0'){
	    	printf("%c\n",e->operated);
	    }	
    	else{
	    	printf("%f\n",e->value);
	    }	
   		e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   		pop(NIBOLAN1,e);
    }
   	printf("��������\n");
    return getTop(OPND).value;
}
int main(){
    printf("%f",evaluateExpression());
    getch();
    return 0;
}
