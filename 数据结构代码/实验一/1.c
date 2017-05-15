/*
 *两递增有序的数列合拼成一非递增有序的数列
 *
 *
 */
#include<stdio.h>
#include<stdlib.h>
/*宏定义*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define TRUE 1
#define ERROR 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
/*构建一个结构体
    1、int型的指针用于存放int数组的首地址
    2、length为int数组的数据长度
    3、listsize为int数组的总长度

*/
typedef struct SqList{
    int *elem;
    int length;
    int listsize;
}SqList;
/*主函数*/
int main(){
    SqList sqlistA,sqlistB,sqlistC;
    int i;
    /*函数说明*/
    int InitList_Sq(SqList* L);
    int InitAdd(SqList* L);
    int Union(SqList *sqlistC,SqList sqlistA,SqList sqlistB);
    /*传递sqlist的指针进入，初始化sqlist对象（结构体）*/
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
/*初始化SqList实例的函数*/
int InitList_Sq(SqList* L){
    L->elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
    if(!L->elem)
        exit(OVERFLOW);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}
/*简单的初始化SqList实例的int数组数据*/
int InitAdd(SqList* L){
    int i,number,elem;
    printf("Input the length:\n");
    scanf("%d",&number);
    /*输入int数据初始化数据*/
    for(i=0;i<number;i++){
        scanf("%d",&elem);
        Add(L,elem);
    }
    printf("_________________________\n");
    return OK;
}
/*在int数组的表尾加入数据elem*/
int Add(SqList* L,int elem){
    int i;
    int *newbase;
    /*fflush(stdin);*/
    /*原int数组长度不够，增加空间分配*/
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
/*A,B合并于C*/
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
