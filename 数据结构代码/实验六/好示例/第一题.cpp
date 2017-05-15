/**
	题目：
		设计并验证如下算法。按先序序列输入建立两颗二叉链表结构，求双分支结点总数，判断两颗二叉树是否相等。
	分析：
		判断两颗二叉树是否相等：
			当root1的左子树与root2的左子树相同，root1的右子树与root2的右子树相同时，这两颗二叉树相同。
			当root1的左子树与root2的右子树相同，root1的右子树与root2的左子树相同时，这两颗二叉树同样相同。
  */
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1               //函数结果状态代码
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2        
typedef int Status;           //函数结果状态代码
typedef char TElemType;       //定义二叉树中数据元素类型

typedef struct BiTNode{      //定义二叉树的二叉链表存储表示
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef BiTNode QElemType;     //定义队列中的数据元素类型
#include"aa.h"                 //添加队列.h文件

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