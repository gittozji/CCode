/*
 *��������������к�ƴ��һ�ǵ������������
 *
 *
 */
#include<stdio.h>
#include<stdlib.h>
/*�궨��*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define TRUE 1
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
/*����һ���ṹ��
    1��int�͵�ָ�����ڴ��int������׵�ַ
    2��lengthΪint��������ݳ���
    3��listsizeΪint������ܳ���

*/
typedef struct SqList{
    int *elem;
    int length;
    int listsize;
}SqList;
/*������*/
int main(){
    SqList sqlistA,sqlistB,sqlistC;
    int i;
    /*����˵��*/
    int InitList_Sq(SqList* L);
    int InitAdd(SqList* L);
    int Union(SqList *sqlistC,SqList sqlistA,SqList sqlistB);
    /*����sqlist��ָ����룬��ʼ��sqlist���󣨽ṹ�壩*/
    InitList_Sq(&sqlistA);
    InitList_Sq(&sqlistB);
    InitList_Sq(&sqlistC);
    InitAdd(&sqlistA);
    InitAdd(&sqlistB);
    Union(&sqlistC,sqlistA,sqlistB);
    printf("The result as follow:\n");
    for(i=0;i<sqlistC.length;i++){
        printf("%d ",sqlistC.elem[i]);
    }
    getch();
    return 0;
}
/*��ʼ��SqListʵ���ĺ���*/
int InitList_Sq(SqList* L){
    L->elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
    if(!L->elem)
        exit(OVERFLOW);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}
/*�򵥵ĳ�ʼ��SqListʵ����int��������*/
int InitAdd(SqList* L){
    int i,number,elem;
    printf("Input the length:\n");
    scanf("%d",&number);
    /*����int���ݳ�ʼ������*/
    for(i=0;i<number;i++){
        scanf("%d",&elem);
        Add(L,elem);
    }
    printf("_________________________\n");
    return OK;
}
/*��int����ı�β��������elem*/
int Add(SqList* L,int elem){
    int i;
    int *newbase;
    /*fflush(stdin);*/
    /*ԭint���鳤�Ȳ��������ӿռ����*/
    if(L->length>=L->listsize){
        newbase=(int *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(int));
        if(!newbase)
            exit(OVERFLOW);
        L->elem=newbase;
        L->listsize=L->length;
    }
    L->elem[L->length]=elem;
    L->length++;
    return OK;
}
/*A,B�ϲ���C*/
int Union(SqList *sqlistC,SqList sqlistA,SqList sqlistB){
    int indexA,indexB;
    indexA=sqlistA.length;
    indexB=sqlistB.length;
    while(indexA>0&&indexB>0){
        if(sqlistA.elem[indexA-1]>sqlistB.elem[indexB-1]){
            Add(sqlistC,sqlistA.elem[--indexA]);
        }
        else{
            Add(sqlistC,sqlistB.elem[--indexB]);
        }
    }
    while(indexA>0){
        Add(sqlistC,sqlistA.elem[--indexA]);
    }
    while(indexB>0){
        Add(sqlistC,sqlistB.elem[--indexB]);
    }
    return OK;
}
