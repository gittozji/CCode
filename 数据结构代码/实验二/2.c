/**

 1���ṹ��򵥵�int�ͳ�Ա��nextָ�� 
 2�����һ����ʼ��������
 3���ж��Ƿ�ݼ����Ż�0�����ǵݼ����Ż�1����ͬʱɾ��ֵ��ͬ���
 4����ӡ����
 5�����ú��� 
 6����������С�жϺ���	
*/
#include<stdio.h>
#include<stdlib.h>
#define mall (ListInt*)malloc(sizeof(ListInt))
typedef struct ListInt{
	int elem;
	struct ListInt *next;
}ListInt;
//���һ����ʼ��������
ListInt	*initList(){
	ListInt *head,*p,*q;
	int i,number;
	head=mall;
	p=head;
	printf("�����ʼ������ĳ��ȣ�\n");
	scanf("%d",&number);
	for(i=0;i<number;i++){
		q=mall;
		printf("����elemֵ��\n");
		scanf("%d",&q->elem);
		p->next=q;
		p=q;
	}
	p->next=NULL;
	return head;
}
//��������С�жϺ��������ڣ�2����С�ڣ�1�������ڣ�0�� 
int cmp(int a,int b){
	if(a>b)
		return 2;
	if(a<b)
		return 1;
	return 0;
}

//�ж��Ƿ�ݼ�������0�����ǵݼ�������1����ͬʱɾ��ֵ��ͬ���
int judgeAndDelete(ListInt* head){
	ListInt *q,*p;
	p=head->next;
	q=p->next;
	while(q){
		switch(cmp(p->elem,q->elem)){
			case 1: return 1;
			case 2: p=q;q=q->next;break;
			case 0: q=q->next;p->next=q;break;
		}
	}
	return 0;
}
//���ú��� 
void backFace(ListInt* head){
	ListInt *q,*p;
	p=head->next;
	head->next=NULL;
	while(p){
		q=p->next;
		p->next=head->next;
		head->next=p;
		p=q;
	}
}

//��ӡ����
void print(ListInt* head){
	//�ҵ����ʣ���������headָ������ 
	head=head->next;
	while(head){	
		printf("%d ",head->elem);
		head=head->next;
	}
	printf("\n\n");
}
int main(){
	ListInt *head;
	head=initList();
	printf("�����ͷ��㵥������\n");
	print(head);
	if(judgeAndDelete(head)){
		printf("�������Ƿǵ�������\n");
	}else{
		printf("�������Ƿǵ�������,����Ϊ���ý��\n");
		backFace(head);
		print(head);
	}
	getchar();
	return 0;
}
