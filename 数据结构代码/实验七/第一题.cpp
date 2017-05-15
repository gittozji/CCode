#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef char TElemType;

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef BiTree SElemType;
#include"Stack.h"

Status preOrder(BiTree BT){           //ÏÈÐò±éÀú¶þ²æÊ÷
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

Status createBiTree(BiTree* BT){
	TElemType ch,chTemp;
	Stack *stack;
	BiTree temp=NULL,maybeTemp = NULL;
	stack=(Stack*)malloc(sizeof(Stack));
	initStack(stack);
	ch=getchar();
	while(ch!='#'){
		if(ch!='('&&ch!=')'&&ch!=','){
			(*BT)=(BiTree)malloc(sizeof(BiTNode));
			(*BT)->data=ch;
			(*BT)->lchild=NULL;
			(*BT)->rchild=NULL;
			temp=maybeTemp=(*BT);
			
		}
		if(ch=='('){
			if(maybeTemp!=temp){
				push(stack,temp);
				temp=maybeTemp;
			}
			if((chTemp=getchar())!=','){
				maybeTemp->lchild=(BiTree)malloc(sizeof(BiTNode));
				maybeTemp=maybeTemp->lchild;
				maybeTemp->data=chTemp;
				maybeTemp->lchild=NULL;
				maybeTemp->rchild=NULL;
			}
			else{
				ungetc(chTemp,stdin);
			}
		}
		if(ch==','){
			if((chTemp=getchar())!=')'){
				maybeTemp=temp->rchild=(BiTree)malloc(sizeof(BiTNode));
				maybeTemp->data=chTemp;
				maybeTemp->lchild=NULL;
				maybeTemp->rchild=NULL;
			}
			else{
				ungetc(chTemp,stdin);
			}
		}
		if(ch==')'){
				pop(stack,&temp);
				maybeTemp=temp;
		}
		ch=getchar();
	}
	return OK;
}
int main(){
	BiTree BT = NULL;
	
	createBiTree(&BT);
	preOrder(BT);
	return 0;
}