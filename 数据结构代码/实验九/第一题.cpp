/**
	��Ʋ���֤�����㷨�����������ö�������ṹ��ʾ��������Ĺؼ������н���һ����������������ɾ���ö����������ϵ�ĳ�����
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
	//���key��data��ȷ���1��
	//���򷵻�0��
	if(key == data)
		return 1;
	return 0;
}

int LT(TElemType key,TElemType data){
	//���key����data��ȷ���1��
	//���򷵻�0��
	if(key > data)
		return 0;
	return 1;
}
Status searchBST(BiTree T,TElemType key,BiTree f,BiTree *p){
	//�ڸ�ָ��T��ָ��Ķ����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ������ҳɹ���
	//��ָ��pָ�������Ԫ�ؽ�㣬������TRUE������ָ��pָ�����·���Ϸ��ʵ�
	//���һ����㲢����FALSE��ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
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

Status preOrder(BiTree BT){           //�������������
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
	//�Ӷ�����������ɾ�����p�������½�������������
	BiTree q,s;
	if(!(*p)->rchild){ // ��������
		q = *p;
		(*p) = (*p)->lchild;
		free(q);
	}
	else if(!(*p)->lchild){  // ֻ�����½�����������
		q = *p;
		(*p) = (*p)->rchild;
		free(q);
	}
	else{ // ������������Ϊ��
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