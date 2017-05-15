/*�����������ʽ��ֵ 
 *���ʽ������#���� 
 *���ʽ�п��Գ��ֶ�λ���֣� 
 *���ʽ�п��Գ��ֿո� 
 *���������+,-,*,/,(,) 
 *�����������Ƕ�λ������������������ʽ���� 
 */  
typedef int SElemType;      /*�����ջ��Ԫ�ص�����*/  
#include <ctype.h>   
#include "stack_s.c"   
/*�ж������ĳ���ַ��Ƿ�������� 
 *c��ʾ������ַ� 
 *op�����д��ϵͳ��ʶ�������� 
 */  
Status in(char c,char op[]){  
    char *p;  
    p=op;  
    while(*p != '\0'){  
        if(c == *p)  
            return TRUE;  
        p++;  
    }  
    return FALSE;  
}  
/*�Ƚ���������������ȼ� 
 *a��b�д�Ŵ��Ƚϵ������ 
 *'>'��ʾa>b 
 *'0'��ʾ�����ܳ��ֵıȽ� 
 */  
char Precede(char a, char b){  
    int i,j;  
    char pre[][7]={           
    /*�����֮������ȼ�������һ�ű��*/  
        {'>','>','<','<','<','>','>'},  
        {'>','>','<','<','<','>','>'},  
        {'>','>','>','>','<','>','>'},  
        {'>','>','>','>','<','>','>'},  
        {'<','<','<','<','<','=','0'},  
        {'>','>','>','>','0','>','>'},  
        {'<','<','<','<','<','0','='}};  
    switch(a){  
        case '+': i=0; break;  
        case '-': i=1; break;  
        case '*': i=2; break;  
        case '/': i=3; break;  
        case '(': i=4; break;  
        case ')': i=5; break;  
        case '#': i=6; break;  
    }  
    switch(b){  
        case '+': j=0; break;  
        case '-': j=1; break;  
        case '*': j=2; break;  
        case '/': j=3; break;  
        case '(': j=4; break;  
        case ')': j=5; break;  
        case '#': j=6; break;  
    }  
    return pre[i][j];  
}  
/*����ʵ�ʵ����� 
 *a��b�зֱ�����������ʽ�������������Ĳ����� 
 *theta�д�Ŵ�����������ַ� 
 *�������������ʽ���� 
 */  
int Operate(int a, char theta, int b){  
    int i,j,result;  
    i=a;  
    j=b;  
  
    switch(theta)   {  
        case '+': result = i + j; break;  
        case '-': result = i - j; break;  
        case '*': result = i * j; break;  
        case '/': result = i / j; break;  
    }  
    return result;  
}  
/*�����뻺�����л����һ�����������������ͨ��n���ص��������� 
 *����ֵΪ1��ʾ��õ�������� 
 *����ֵΪ0��ʾ��õ������β����� 
 */  
int getNext(int *n){  
    char c;  
    *n=0;  
    while((c=getchar())==' ');  /*����һ�������ո�*/  
    if(!isdigit(c)){            /*ͨ�������ж�����ַ��������֣���ôֻ���������*/  
        *n=c;  
        return 1;  
    }  
    do    {                         /*��ִ�е�������䣬˵���ַ������֣��˴���ѭ���������������*/  
        *n=*n*10+(c-'0');       /*�������������ַ�ת�������Ӧ������*/  
        c=getchar();  
    }    while(isdigit(c));         /*�����һ���ַ������֣�������һ��ѭ��*/  
    ungetc(c,stdin);            /*�¶�����ַ��������֣������������,Ϊ�˲�Ӱ���´ζ��룬�Ѹ��ַ��Żص����뻺����*/  
    return 0;  
}  
  
int EvaluateExpression(){  
  
    int n;  
    int flag;  
    int c;  
    char x,theta;  
    int a,b;  
  
    char OP[]="+-*/()#";  
    SqStack  OPTR;  
    SqStack  OPND;  
  
    InitStack(&OPTR);        
    Push(&OPTR,'#');  
    InitStack(&OPND);  
    flag=getNext(&c);  
  
    GetTop(OPTR, &x);  
    while(c!='#' || x != '#')  
    {  
        if(flag == 0)  
         {  
                  Push(&OPND,c);  
                  flag = getNext(&c);  
             }        else  
    {  
            GetTop(OPTR, &x);  
            switch(Precede(x, c))  
        {  
                case '<'://ջ��Ԫ�����ȼ���                       
                    Push(&OPTR,c);  
                    flag = getNext(&c);  
                    break;  
                case '='://�����Ų�������һ�ַ�    
                    Pop(&OPTR,&x);  
                    flag = getNext(&c);  
                    break;  
                case '>'��// ��ջ������������ջ                                          
                    Pop(&OPTR, &theta);  
                    Pop(&OPND,&b);  
                    Pop(&OPND,&a);  
                    Push(&OPND, Operate(a, theta, b));  
                    break;  
            }  
        }  
        GetTop(OPTR, &x);  
    }  
    GetTop(OPND, &c);  
    return c;  
}  
  
void main(){  
    int c;  
    printf("Please input one expression:");  
    c=EvaluateExpression();  
    printf("Result=%d\n",c);  
    getch();  
}  

