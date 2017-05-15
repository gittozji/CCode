/*
 *运算表达式求值
 *只能用于int型求值
 *
 */

/***************************暂存区************************************

1、int类型与char类型的相互转化，合格
int main(){
    char c = (char)43;
    printf("%c",c);
    getch();
    return 0;
}
2、测试栈，合格
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
3、测试比较运算符优先级函数，合格
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
4、测试operate函数，合格
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
/*栈结构体取名为SqStack*/
typedef struct Key{
	float value;
	char operated;
}Key;
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
/*函数：初始化栈*/
Status initStack(SqStack *S){
    S->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
/*函数：进栈*/
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
/*函数：出栈*/
Status pop(SqStack *S,SElemType *e){
    if(S->top==S->base) return ERROR;
    *e=*--S->top;
    return OK;
}
/*函数：获取栈顶元素*/
SElemType getTop(SqStack *S){
    return *(S->top-1);
}


/*函数：比较运算符优先级*/
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
/*函数：运算*/
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
/*函数：字符串动态处理（难点，尝试实现）*/
/*为0时是数值，为1时是运算符*/
int dealChar(SElemType *values){
    char c;
    values->value=0;
    values->operated='0';
    c = getchar();
    int digit=1;
    int judge=0;//0为没有遇到点，1为遇到点 
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
    ungetc(c,stdin);/*放回缓冲区*/
    return 0;
}
/*函数：本程序栈的核心代码*/
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
    NIBOLAN=(SqStack*)malloc(sizeof(SqStack));//逆波兰 
    NIBOLAN1=(SqStack*)malloc(sizeof(SqStack));//逆波兰 1
    initStack(OPTR);
    initStack(OPND);
    initStack(NIBOLAN);//逆波兰 
    initStack(NIBOLAN1);//逆波兰 1
    e->operated='#';
    push(OPTR,*e);
    push(NIBOLAN,*e);//逆波兰 
    push(NIBOLAN1,*e);
    e = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    printf("输入表达式：\n");
    flag=dealChar(e);
    while(e->operated!='#'||getTop(OPTR).operated!='#'){
        if(flag==0){
            push(OPND,*e);
            push(NIBOLAN,*e);//逆波兰 
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
                	push(NIBOLAN,*theta);//逆波兰 
                    pop(OPND,b);
                    pop(OPND,a);
                    push(OPND,operate(*a,*theta,*b));
                    break;
            }
        }
    }
    printf("逆波兰形式：\n");
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
    printf("\n转置：\n");
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
   	printf("运算结果：\n");
    return getTop(OPND).value;
}
int main(){
    printf("%f",evaluateExpression());
    getch();
    return 0;
}
