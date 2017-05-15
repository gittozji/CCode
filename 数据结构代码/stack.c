#include<stdio.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALUSE 0
typedef struct Stack{
    char *base;
    char *top;
    int stacksize;
}SqStack;
/*初始化栈函数*/
int initStack(SqStack *S){
    S->base = (char *)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!S->base) exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}
/*获取栈顶元素函数*/
int getTop(SqStack S,char *e){
    if(S.top==S.base) return ERROR;
    *e = *(S.top-1);
    return OK;
}
/*进栈函数*/
int push(SqStack *S,char e){
    if((S->top)-(S->base)>=S->stacksize){
        S->base=(char *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(char));
        if(!S->base)exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++ = e;
    return OK;
}
/*出栈函数*/
int pop(SqStack *S,char *e){
    if(S->top==S->base) return ERROR;
    *e=*--S->top;
    return OK;
}
/*优先级判断函数*/
char precede(char a,char b){
    switch(a){
        case '+':if(b=='+'||b=='-'||b==')'||b=='#')
                    return '>';
                 else
                    return '<';
        case '-':if(b=='+'||b=='-'||b==')'||b=='#')
                    return '>';
                 else
                    return '<';
        case '*':if(b=='(')
                    return '<';
                 else
                    return '>';
        case '/':if(b=='(')
                    return '<';
                 else
                    return '>';
        case '(':if(b==')')
                    return '=';
                 else
                    return '<';
        case ')':return '>';
        case '#':if(b=='#')
                    return '=';
                 else
                    return '<';
    }
}
/*判断是否为运算符函数*/
int isOptr(char a){
    if(a=='+'||a=='-'||a=='*'||a=='/'||a=='('||a==')'||a=='#')
        return 1;
    return 0;
}
/*计算函数*/
long operate(a,e,b){
    if(e=='+')
        return a+b-96;
    if(e=='-')
        return a-b-96;
    if(e=='*')
        return (a-48)*(b-48);
    if(e=='/')
        return (a-48)/(b-48);
}
int main(){
    SqStack *optr=NULL;
    SqStack *opnd=NULL;
    char c;
    char *e;
    char *a;/*用于保存计算的数值*/
    char *b;/*用于保存计算的数值*/
    initStack(optr);
    initStack(opnd);
    push(optr,'#');
    printf("Input the expression\n");
    c = getch();/*这里用getch()会怎样呢？*/
    while(c!='#'||(*e=(getTop(*optr,e)))!='#'){
        if(!isOptr(c)){
            push(opnd,c);
            c = getch();
        }
        else{
            switch(precede((*e=getTop(*optr,e)),c)){
                case '<':push(optr,c);
                    c=getch();
                    break;
                case '=':pop(optr,e);
                    c=getch();
                    break;
                case '>':pop(optr,e);
                    pop(opnd,a);pop(opnd,b);
                    push(opnd,(char)(operate(a,e,b)+48));
                    break;
            }
        }
    }
    getTop(*opnd,e);
    printf("c",*e);
    getch();
    return 0;
}

