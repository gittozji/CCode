/*
*һԪϡ�����ʽ������
*
*/
#include<stdio.h>
#include<stdlib.h>
/*�����ṹ��*/
typedef struct Polynoial{
    float coef;
    int expn;
    struct Polynoial *next;
}Polynoial;
/*����������һ������ʽ����*/
Polynoial *createPolyn(){
    Polynoial *head,*p,*q;
    int i,number;
    printf("�������ʽ����:\n");
    scanf("%d",&number);
    head=(Polynoial*)malloc(sizeof(Polynoial));
    head->next=NULL;
    p=head;
    for(i=0;i<number;i++){
        q=(Polynoial*)malloc(sizeof(Polynoial));
        printf("����ϵ����ָ��:\n");
        scanf("%f %d",&(q->coef),&(q->expn));
        p->next=q;
        p=q;
    }
    p->next=NULL;
    return head;
}
//������0Ϊ���ڣ�1Ϊ���ڣ�2ΪС��
int cmp(int a,int b) {
	if(a>b)
		return 0;
	if(a==b)
		return 1;
	return 2;
}
//������������ʽ��ӣ�0���������1�� 
Polynoial * addOrRed(Polynoial *first,Polynoial *second,int judge){
	Polynoial *head,*zeroCur,*q,*oneCur,*secondCur;
	head=(Polynoial*)malloc(sizeof(Polynoial));
	head->next=NULL;
	zeroCur=head;
	oneCur=first->next;
	secondCur=second->next;
	while(oneCur&&secondCur){
		switch(cmp(oneCur->expn	,secondCur->expn)){
			case 2: q=(Polynoial*)malloc(sizeof(Polynoial));
				q->coef=oneCur->coef;
				q->expn=oneCur->expn;
				zeroCur->next=q;
				q->next=NULL;
				zeroCur=q;
				oneCur=oneCur->next;
				break;
			case 0: q=(Polynoial*)malloc(sizeof(Polynoial));
				q->coef=secondCur->coef;
				q->expn=secondCur->expn;
				zeroCur->next=q;
				q->next=NULL;
				zeroCur=q;
				secondCur=secondCur->next;
				break;
			case 1: q=(Polynoial*)malloc(sizeof(Polynoial));
				if(judge==0)
					q->coef=secondCur->coef+oneCur->coef;
				else
					q->coef=oneCur->coef-secondCur->coef;
				q->expn=oneCur->expn;
				zeroCur->next=q;
				q->next=NULL;
				zeroCur=q;
				oneCur=oneCur->next;
				secondCur=secondCur->next;
				break;
		}
	}
	while(oneCur!=NULL){
		q=(Polynoial*)malloc(sizeof(Polynoial));
		q->coef=oneCur->coef;
		q->expn=oneCur->expn;
		zeroCur->next=q;
		q->next=NULL;
		zeroCur=q;
		oneCur=oneCur->next;
	}
	while(secondCur!=NULL){
		q=(Polynoial*)malloc(sizeof(Polynoial));
		q->coef=secondCur->coef;
		q->expn=secondCur->expn;
		zeroCur->next=q;
		q->next=NULL;
		zeroCur=q;
		secondCur=secondCur->next;
	}
	return head;	
}
//��������ӡ��� 
void print(Polynoial *addOneSecond){
	addOneSecond=addOneSecond->next;
    while(addOneSecond){
    	printf("%fX^%d ",addOneSecond->coef,addOneSecond->expn);
    	addOneSecond=addOneSecond->next;
    }
}
int main(){
	Polynoial *one,*second,*addOneSecond;
    one=createPolyn();
    second=createPolyn();
    addOneSecond=addOrRed(one,second,0);
    printf("��ӽ����\n");
    print(addOneSecond);
    printf("��������\n");
    print(addOrRed(one,second,1));
    return 0;
}
