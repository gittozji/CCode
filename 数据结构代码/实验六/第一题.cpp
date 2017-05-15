/**
	��Ŀ��
		1����Ʋ���֤�����㷨���������������뽨�����Ŷ�������ṹ����˫��֧����������ж����Ŷ������Ƿ���ȡ�
	    2����Ʋ���֤�����㷨������α�������������ӡ������ڵĲ�Σ�����������Ŀ�ȡ�
	������
		�ж����Ŷ������Ƿ���ȣ�
			��root1����������root2����������ͬ��root1����������root2����������ͬʱ�������Ŷ�������ͬ��
			��root1����������root2����������ͬ��root1����������root2����������ͬʱ�������Ŷ�����ͬ����ͬ��	
  */
#include<stdio.h>
#include<stdlib.h>
typedef char TElemType;       //���������������Ԫ������

typedef struct BiTNode{      //����������Ķ�������洢��ʾ
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

#include"Queue.h"                //��Ӷ���.h�ļ�

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

Status TwoBranchCount(BiTree BT,int *count){    //��˫��֧�����Ŀ
	Queue *q = (Queue*)malloc(sizeof(Queue));
	QElemType *e = (QElemType*)malloc(sizeof(QElemType));
	initQueue(q);
	enQueue(q,*BT);
	while(queueLength(*q)){
		deQueue(q,e);
		if(e->lchild!=NULL&&e->rchild!=NULL){
			(*count)++;
		}
		if(e->lchild!=NULL)
			enQueue(q,*(e->lchild));
		if(e->rchild!=NULL)
			enQueue(q,*(e->rchild));
	}
	return OK;
}

Status equalsTree(BiTree BT1,BiTree BT2){
	if(BT1&&BT2){   //��Ϊ��
		if(BT1->data!=BT2->data)    //ֵ�����
			return 0;
		else{     //ֵ��ȵ������
			if((equalsTree(BT1->lchild,BT2->lchild)&&equalsTree(BT1->rchild,BT2->rchild))||(equalsTree(BT1->lchild,BT2->rchild)&&equalsTree(BT1->rchild,BT2->lchild)))    //����������������Ӧ���
				return 1;
			else
				return 0;
		}
	}
	else{
		if(BT1==NULL&&BT2==NULL){    //��Ϊ��
			return 1;
		}else{    //����Ϊ��
			return 0;
		}
	}
}

int getWidthAttachPrint(BiTree B) {   //���Ⱥʹ�ӡÿһ�������
	int layer=1,width=0,tempWidth=0,lastWidth=0,currentWidth=0;//���屣����һ�㣬�ò㼰������
	Queue *q = (Queue*)malloc(sizeof(Queue));
	QElemType *e = (QElemType*)malloc(sizeof(QElemType));
	initQueue(q);
	if(B==NULL)
		return 0;
	enQueue(q,*B);
	width=lastWidth=1;
	while(queueLength(*q)){
		tempWidth=lastWidth;
		printf("��%d������ݣ�",layer++);
		while(tempWidth!=0){
			deQueue(q,e);
			if(e->lchild!=NULL)
				enQueue(q,*(e->lchild));
			if(e->rchild!=NULL)
				enQueue(q,*(e->rchild));
			tempWidth--;
			printf("%c ",e->data);
		}
		printf("\n");
		currentWidth=queueLength(*q);
		width=currentWidth>width?currentWidth:width;
		lastWidth=currentWidth;
	}
	return width;
}
int main(){
	BiTree BT1 = NULL,BT2 = NULL;
	int count=0;
	printf("������BT1�����������У�");
	createBiTree(&BT1);
	printf("BT1�����������");
	preOrder(BT1);
	TwoBranchCount(BT1,&count);
	printf("\nBT1��˫��֧���������%d",count);
	fflush(stdin);
	printf("\n\n������BT2�����������У�");
	createBiTree(&BT2);
	printf("BT2�����������");
	preOrder(BT2);
	count=0;
	TwoBranchCount(BT2,&count);
	printf("\nBT2��˫��֧���������%d",count);
	if(equalsTree(BT1,BT2)){
		printf("\n\n��������ȣ�\n\n");
	}
	else
		printf("\n\n����������ȣ�\n\n");
	printf("\nBT1�Ŀ�ȣ�%d\n\n",getWidthAttachPrint(BT1));

	return 0;
}