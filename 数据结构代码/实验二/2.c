/**

 1、结构体简单的int型成员和next指针 
 2、设计一个初始化链表函数
 3、判断是否递减（放回0），非递减（放回1），同时删除值相同项函数
 4、打印函数
 5、逆置函数 
 6、两个数大小判断函数	
*/
#include<stdio.h>
#include<stdlib.h>
#define mall (ListInt*)malloc(sizeof(ListInt))
typedef struct ListInt{
	int elem;
	struct ListInt *next;
}ListInt;
//设计一个初始化链表函数
ListInt	*initList(){
	ListInt *head,*p,*q;
	int i,number;
	head=mall;
	p=head;
	printf("输入初始化链表的长度：\n");
	scanf("%d",&number);
	for(i=0;i<number;i++){
		q=mall;
		printf("输入elem值：\n");
		scanf("%d",&q->elem);
		p->next=q;
		p=q;
	}
	p->next=NULL;
	return head;
}
//两个数大小判断函数，大于（2），小于（1），等于（0） 
int cmp(int a,int b){
	if(a>b)
		return 2;
	if(a<b)
		return 1;
	return 0;
}

//判断是否递减（返回0），非递减（返回1），同时删除值相同项函数
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
//逆置函数 
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

//打印函数
void print(ListInt* head){
	//我的疑问，主函数的head指针会变吗？ 
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
	printf("输出带头结点单向链表：\n");
	print(head);
	if(judgeAndDelete(head)){
		printf("该链表不是非递增有序\n");
	}else{
		printf("该链表是非递增有序,下列为逆置结果\n");
		backFace(head);
		print(head);
	}
	getchar();
	return 0;
}
