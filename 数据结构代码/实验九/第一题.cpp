/**
	设计并验证如下算法：二叉树采用二叉链表结构表示，按输入的关键字序列建立一个二叉排序树，并删除该二叉排序树上的某个结点
*/
#include<stdlib.h>
#include<stdio.h>
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1

typedef int TElemType;
typedef int Status;

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

int EQ(TElemType key,TElemType data){
	//如果key和data相等返回1，
	//否则返回0。
	if(key == data)
		return 1;
	return 0;
}

int LT(TElemType key,TElemType data){
	//如果key大于data相等返回1，
	//否则返回0。
	if(key > data)
		return 0;
	return 1;
}
Status searchBST(BiTree T,TElemType key,BiTree f,BiTree *p){
	//在根指针T所指向的二叉排序数中递归地查找其关键字等于key的数据元素，若查找成功，
	//则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上访问的
	//最后一个结点并返回FALSE，指针f指向T的双亲，其初始调用值为NULL
	if(!T){
		(*p) = f;
		return FALSE;
	}
	else if(EQ(key,T->data)){
		*p = T;
		return TRUE;
	}
	else if(LT(key,T->data)){
		return searchBST(T->lchild,key,T,p);
	}
	else 
		return searchBST(T->rchild,key,T,p);
}//searchBST

Status insertBST(BiTree *T,TElemType e){
	BiTree p = NULL;
	BiTree s;
	if(!searchBST(*T,e,NULL,&p)){
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;
		s->lchild=s->rchild=NULL;
		if(!p){
			*T = s;
		}
		else if(LT(e,p->data))
			p->lchild = s;
		else
			p->rchild = s;
		return TRUE;
	}
	else 
		return FALSE;
}

Status preOrder(BiTree BT){           //先序遍历二叉树
	if(BT){
		if(!(BT->data))
			return ERROR;
		printf("%d ",BT->data);
		preOrder(BT->lchild);
		preOrder(BT->rchild);
		return OK;
	}
	return ERROR;
}//preOrder

Status del(BiTree *p){
	//从二叉排序树中删除结点p，并重新接他的左右子树
	BiTree q,s;
	if(!(*p)->rchild){ // 右子树空
		q = *p;
		(*p) = (*p)->lchild;
		free(q);
	}
	else if(!(*p)->lchild){  // 只需重新接他的右子树
		q = *p;
		(*p) = (*p)->rchild;
		free(q);
	}
	else{ // 左右子树都不为空
		q = (*p);
		s = (*p)->lchild;
		while(s->rchild){
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;
		if(q!=(*p))
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;
		delete s;
	}
	return TRUE;
}//del

Status deleteBST(BiTree*T,TElemType key){
	if(!T)
		return FALSE;
	else{
		if(EQ(key,(*T)->data))
			return del(T);
		else if(LT(key,(*T)->data))
			return deleteBST(&((*T)->lchild),key);
		else
			return deleteBST(&((*T)->rchild),key);
	}
}//deleteBST

int main(){
	BiTree BT = NULL;
	insertBST(&BT,100);
	insertBST(&BT,200);
	insertBST(&BT,50);
	//insertBST(&BT,52);
	preOrder(BT);
	printf("\n");
	deleteBST(&BT,200);
	preOrder(BT);
	return 0;
}