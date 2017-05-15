/**
	��ϣ��ʵ�ֹ�ϣ��Ĺ���Ͳ����㷨��Ҫ���ó����෨�����ϣ������
	�ֱ���һ��̽����ɢ�С�����̽����ɢ�н����ͻ
*/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
#define SIZE 100
#define NULLKEY -100

typedef int ElemType;
typedef int Status;

typedef struct {
	//��ϣ��洢�ṹ
	ElemType *elem;
	int count;
	int size;
}HashTable;

int Hash(int k){
	//��ϣ����
	return k%SIZE;
}

void collision1(int &p,int c){
	//һ��̽����ɢ��
	p = (p+c)%SIZE;
}

void collision2(int &p,int c){
	//����̽����ɢ��
	int a = c%2;
	if(a){
		p = (p+(a+c/2)*(a+c/2))%SIZE;
	}
	else
		p = (p-1*(c/2)*(c/2))%SIZE;
}

Status searchHash(HashTable H,int k,int &p,int &c){
	//��ϣ�����
	p = Hash(k);
	int pTemp = p;
	while(H.elem[p] != NULLKEY && H.elem[p] != k){
		p = pTemp;
		collision1(p,++c);
	}
	if(H.elem[p] == k)
		return SUCCESS;
	else
		return UNSUCCESS;
}//searchHash

Status insertHash(HashTable &H,ElemType e){
	//��ϣ�����
	int c = 0;
	int p;
	if(searchHash(H,e,p,c)){
		return DUPLICATE;
	}
	else{
		H.elem[p] = e;
		++H.count;
		return SUCCESS;
	}
}

int main(){
	HashTable* H;
	int p,c=0;

	H = (HashTable*)malloc(sizeof(HashTable));
	H->elem = (int *)malloc(SIZE*sizeof(int));
	H->size = SIZE;
	for(int i=0;i<H->size;i++){
		H->elem[i] = NULLKEY;
	}
	insertHash(*H,1);
	insertHash(*H,101);
	insertHash(*H,201);
	
	searchHash(*H,1,p,c);
	printf("%d\n",p);
	c=0;
	searchHash(*H,101,p,c);
	printf("%d\n",p);
	c=0;
	searchHash(*H,201,p,c);
	printf("%d\n",p);
	return 0;
}