/**
	��Ŀ��
		��Ʋ���֤�����㷨���������������뽨�����Ŷ�������ṹ����˫��֧����������ж����Ŷ������Ƿ���ȡ�
	������
		�ж����Ŷ������Ƿ���ȣ�
			��root1����������root2����������ͬ��root1����������root2����������ͬʱ�������Ŷ�������ͬ��
			��root1����������root2����������ͬ��root1����������root2����������ͬʱ�������Ŷ�����ͬ����ͬ��
  */
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1               //�������״̬����
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2        
typedef int Status;           //�������״̬����
typedef char TElemType;       //���������������Ԫ������

typedef struct BiTNode{      //����������Ķ�������洢��ʾ
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef BiTNode QElemType;     //��������е�����Ԫ������
#include"aa.h"                 //��Ӷ���.h�ļ�

Status createBiTree(BiTree *BT){        //��������������
	TElemType ch;
	scanf("%c",&ch);
	if(ch!='#'){
		*BT = (BiTree)malloc(sizeof(BiTNode));
		if(!(*BT))
			return OVERFLOW;
		(*BT)->data=ch;
		createBiTree(&(*BT)->lchild);
		createBiTree(&(*BT)->rchild);
	}	
	else
		*BT = NULL;
	return OK;
}//createBiTree

Status preOrder(BiTree BT){           //�������������
	if(BT){
		if(!(BT->data))
			return ERROR;
		printf("%c ",BT->data);
		preOrder(BT->lchild);
		preOrder(BT->rchild);
		return OK;
	}
	return ERROR;
}//preOrder

int main(){
	Queue *q = (Queue*)malloc(sizeof(Queue));
	initQueue(q);
	QElemType *e = (QElemType*)malloc(sizeof(QElemType)),ee;
	e->data='e';
	e->lchild=NULL;
	e->rchild=NULL;
	printf("ddddddd");
	enQueue(q,*e);
	deQueue(q,&ee);
	printf("%d ",ee.data);
	return 0;
}