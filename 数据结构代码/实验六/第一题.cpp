/**
	题目：
		1、设计并验证如下算法。按先序序列输入建立两颗二叉链表结构，求双分支结点总数，判断两颗二叉树是否相等。
	    2、设计并验证如下算法。按层次遍历二叉树，打印结点所在的层次，并求二叉树的宽度。
	分析：
		判断两颗二叉树是否相等：
			当root1的左子树与root2的左子树相同，root1的右子树与root2的右子树相同时，这两颗二叉树相同。
			当root1的左子树与root2的右子树相同，root1的右子树与root2的左子树相同时，这两颗二叉树同样相同。	
  */
#include<stdio.h>
#include<stdlib.h>
typedef char TElemType;       //定义二叉树中数据元素类型

typedef struct BiTNode{      //定义二叉树的二叉链表存储表示
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

#include"Queue.h"                //添加队列.h文件

Status createBiTree(BiTree *BT){        //创建二叉树函数
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

Status preOrder(BiTree BT){           //先序遍历二叉树
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

Status TwoBranchCount(BiTree BT,int *count){    //求双分支结点数目
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
	if(BT1&&BT2){   //不为空
		if(BT1->data!=BT2->data)    //值不相等
			return 0;
		else{     //值相等的情况下
			if((equalsTree(BT1->lchild,BT2->lchild)&&equalsTree(BT1->rchild,BT2->rchild))||(equalsTree(BT1->lchild,BT2->rchild)&&equalsTree(BT1->rchild,BT2->lchild)))    //左子树或右子树对应相等
				return 1;
			else
				return 0;
		}
	}
	else{
		if(BT1==NULL&&BT2==NULL){    //都为空
			return 1;
		}else{    //不都为空
			return 0;
		}
	}
}

int getWidthAttachPrint(BiTree B) {   //求宽度和打印每一层的数据
	int layer=1,width=0,tempWidth=0,lastWidth=0,currentWidth=0;//定义保存上一层，该层及缓存宽度
	Queue *q = (Queue*)malloc(sizeof(Queue));
	QElemType *e = (QElemType*)malloc(sizeof(QElemType));
	initQueue(q);
	if(B==NULL)
		return 0;
	enQueue(q,*B);
	width=lastWidth=1;
	while(queueLength(*q)){
		tempWidth=lastWidth;
		printf("第%d层的数据：",layer++);
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
	printf("请输入BT1树的先序序列：");
	createBiTree(&BT1);
	printf("BT1的先序遍历：");
	preOrder(BT1);
	TwoBranchCount(BT1,&count);
	printf("\nBT1的双分支结点总数：%d",count);
	fflush(stdin);
	printf("\n\n请输入BT2树的先序序列：");
	createBiTree(&BT2);
	printf("BT2的先序遍历：");
	preOrder(BT2);
	count=0;
	TwoBranchCount(BT2,&count);
	printf("\nBT2的双分支结点总数：%d",count);
	if(equalsTree(BT1,BT2)){
		printf("\n\n两棵树相等！\n\n");
	}
	else
		printf("\n\n两棵树不相等！\n\n");
	printf("\nBT1的宽度：%d\n\n",getWidthAttachPrint(BT1));

	return 0;
}