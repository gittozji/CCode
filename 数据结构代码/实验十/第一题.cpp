/**
	产生随机整数样本，进行8种排序，并比较
	各种排序算法的执行时间
*/


#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1

#define MAXSIZE 5000

typedef int Status;
typedef int KeyType;
typedef int InfoType;

typedef struct{
	KeyType key;
	InfoType otherinfo;
}RedType;

typedef struct{
	RedType *r;
	int length;
}SqList;

Status Output(SqList L,int count){
	int i;
	printf("\n\nphlofy~~~ %d Data is:\n",count);
	for(i=1;i<=L.length;i++){
		printf("%8d",L.r[i]);
	}
	printf("\n");
	return OK;
}


Status InitSqList(SqList *L);
Status CreatSqList(SqList *L);
Status CopySqList(SqList L_BAK, SqList *L);
Status OutputSqList(SqList L);
int LT(KeyType e1, KeyType e2);
void Swap(RedType *el,RedType *e2);

Status InsertSort(SqList *L);
Status BInsertSort(SqList *L);
Status ShellInsert(SqList *L,int dk);
Status ShellSort(SqList *L,int dlta[],int t);
Status BubbleSort(SqList *L);
int Partition(SqList *L,int low,int high);
void QSort(SqList *L,int low,int high);
Status QuickSort(SqList *L);
Status SelectSort(SqList *L);
Status HeapAdjust(SqList *H,int s,int m);
Status HeapSort(SqList *H);
Status Merge(SqList *L,int low,int mid,int high);
void MSort(SqList *L,int len);
Status MergeSort(SqList *L);

/*************************** main *******************************/

void main(){
	SqList L,L_BAK;
	int select,flag=1,t,dlta[MAXSIZE];
	double duration;
	clock_t start,finish;

	InitSqList(&L);
	InitSqList(&L_BAK);

	CreatSqList(&L_BAK);

	t=0;
	dlta[0] = L_BAK.length/2;
	while(dlta[t]>1){
		dlta[t+1] = dlta[t]/2;
		t++;
	}

	while(flag){
		CopySqList(L_BAK,&L);
		printf("Please select:\n");
		printf("1. InsertSort\n");
		printf("2. BInsertSort\n");
		printf("3. ShellSort\n");
		printf("4. BubbleSort\n");
		printf("5. QuickSort\n");
		printf("6. SelectSort\n");
		printf("7. HeapSort\n");
		printf("8. MergeSort\n");
		printf("9. Exit\n");

		scanf("%d",&select);
		switch(select){
		case 1:
			printf("\nNow is in InsertSort......");
			start = clock();
			InsertSort(&L);
			finish = clock();
			break;
			
		case 2:
			printf("\nNow is in BInsertSort......");
			start = clock();
			BInsertSort(&L);
			finish = clock();
			break;

		case 3:
			printf("\nNow is in ShellSort......");
			start = clock();
			ShellSort(&L,dlta,t+1);
			finish = clock();
			break;

		case 4:
			printf("\nNow is in BubbleSort......");
			start = clock();
			BubbleSort(&L);
			finish = clock();
			break;

		case 5:
			printf("\nNow is in QuickSort......");
			start = clock();
			QuickSort(&L);
			finish = clock();
			break;
		case 6:
			printf("\nNow is in SelectSort......");
			start = clock();
			SelectSort(&L);
			finish = clock();
			break;

		case 7:
			printf("\nNow is in HeapSort......");
			start = clock();
			HeapSort(&L);
			finish = clock();
			break;

		case 8:
			printf("\nNow is in MergeSort......");
			start = clock();
			MergeSort(&L);
			finish = clock();
			break;

		default:
			flag = 0;
			printf("Press any key to exit!\n");
			getch();
		}

		printf("\n最后输出：");
		OutputSqList(L);
		duration = (double)(finish - start);
		printf("\nThe Sort Spend: %lf seconds\n",duration);
	}	
}

Status InitSqList(SqList *L){
	L->r = (RedType*)malloc((MAXSIZE+1)*sizeof(RedType));
	if(!L->r)
		exit(OVERFLOW);
	L->length = 0;
	return OK;
}

Status CreatSqList(SqList *L){
	int i;
	srand(time(NULL));
	printf("\nPleas Input the Number of UnSorted Data: ");
	scanf("%d",&L->length);
	
	for(i=1;i<=L->length;i++){
		L->r[i].key = rand();
	}	
	printf("\n\nThe UnSorted data is:\n");
	for(i=1;i<=L->length;i++){
		printf("%8d",L->r[i]);
	}
	return OK;
}

Status CopySqList(SqList L_BAK, SqList *L){
	int i;
	if(!L_BAK.length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	for(i=0;i<=L_BAK.length;i++){
		L->r[i].key = L_BAK.r[i].key;
	}
	L->length = L_BAK.length;

	return OK;
}

Status OutputSqList(SqList L){
	int i;
	printf("\nThe Length of SqList is:%d\n",L.length);
	printf("\n\nThe Sorted Data is:\n");
	for(i=1;i<=L.length;i++){
		printf("%8d",L.r[i]);
	}
	printf("\n");
	return OK;
}

int LT(KeyType e1, KeyType e2){
	if(e1<e2)
		return 1;
	else 
		return 0;
}
void Swap(RedType *e1,RedType *e2){
	RedType e;
	e = *e1;
	*e1 = *e2;
	*e2 = e;
}

Status InsertSort(SqList *L){
	int i,j,count=1;

	if(!L->length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	for(i=2;i<=L->length;i++){
		if(LT(L->r[i].key,L->r[i-1].key)){
			L->r[0] = L->r[i];
			L->r[i] = L->r[i-1];
			for(j=i-2;LT(L->r[0].key,L->r[j].key);j--){
				L->r[j+1] = L->r[j];
			}
			L->r[j+1] = L->r[0];
		}Output(*L,count++);
	}
	return OK;
}

Status BInsertSort(SqList *L){
	int i,j,mid,low,high,count=1;

	if(!L->length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	for(i=2;i<=L->length;i++){
		L->r[0] = L->r[i];
		low = 1;
		high = i-1;
		while(low<=high){
			mid = (low+high)/2;
			if(LT(L->r[0].key,L->r[mid].key))
				high = mid-1;
			else 
				low = mid+1;
		}	
		for(j=i-1;j>=high+1;j--){
			L->r[j+1] = L->r[j];
		}
		L->r[high+1]=L->r[0];
		Output(*L,count++);
	}
	return OK;
}

Status ShellInsert(SqList *L,int dk){
	int i,j;

	for(i=dk+1;i<=L->length;i++){
		if(LT(L->r[i].key,L->r[i-dk].key)){
			L->r[0] = L->r[i];
			for(j=i-dk;j>0&&LT(L->r[0].key,L->r[j].key);j-=dk){
				L->r[j+dk] = L->r[j];
			}
			L->r[j+dk] = L->r[0];
		}
	}
	return OK;
}

Status ShellSort(SqList *L,int dlta[],int t){
	int k,count=1;

	if(!L->length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	for(k=0;k<t;k++){
		ShellInsert(L,dlta[k]);
		Output(*L,count++);
	}
	return OK;

}
Status BubbleSort(SqList *L){
	int i,j,count=1;

	if(!L->length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	for(i=1;i<L->length;i++){
		for(j=1;j<=L->length-i;j++){
			if(!LT(L->r[j].key,L->r[j+1].key)){
				Swap(&L->r[j],&L->r[j+1]);
			}
		}	
		Output(*L,count++);
	}
	return OK;
}

int Partition(SqList *L,int low,int high){
	int pivotkey;

	L->r[0] = L->r[low];
	pivotkey = L->r[low].key;

	while(low<high){
		while(low<high && L->r[high].key>=pivotkey){
			high--;
		}
		L->r[low] = L->r[high];
		while(low<high && L->r[low].key<=pivotkey){
			low++;
		}
		L->r[high] = L->r[low];
	}
	L->r[low] = L->r[0];
	return low;
}

void QSort(SqList *L,int low,int high){
	int pivotloc;
	if(low<high){
		pivotloc = Partition(L,low,high);

		QSort(L,low,pivotloc-1);
		QSort(L,pivotloc+1,high);
	}	
}

Status QuickSort(SqList *L){
	if(!L->length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	QSort(L,1,L->length);
	return OK;
}

Status SelectSort(SqList *L){
	int i,j,min,count=1;

	if(!L->length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	for(i=1;i<L->length;i++){
		min = i;
		for(j=i+1;j<=L->length;j++){
			if(LT(L->r[j].key,L->r[min].key)){
				min = j;
			}
		}
		if(min!=i){
			Swap(&L->r[i],&L->r[min]);
		}
				Output(*L,count);
	}
	return OK;
}

Status HeapAdjust(SqList *H,int s,int m){
	int j;
	H->r[0] = H->r[s];

	for(j=2*s; j<=m; j*=2){
		if(j<m && LT(H->r[j].key,H->r[j+1].key)){
			j++;
		}
		if(!LT(H->r[0].key,H->r[j].key))
			break;
		H->r[s] = H->r[j];
		s = j;
	}

	H->r[s] = H->r[0];

	return OK;
}

Status HeapSort(SqList *H){
	int i;
	
	if(!H->length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	for(i=H->length/2;i>0;i--){
		HeapAdjust(H,i,H->length);
	}
	
	for(i=H->length;i>1;i--){
		Swap(&H->r[1],&H->r[i]);
		HeapAdjust(H,1,i-1);
	}

	return OK;
	
}

Status Merge(SqList *L,int low,int mid,int high){
	int i=low,j=mid+1,k=0;
	SqList L1;
	L1.r = (RedType*)malloc((high-low+1)*sizeof(RedType));
	if(!L1.r)
		exit(OVERFLOW);

	while(i<=mid && j<=high){
		L1.r[k++] = LT(L->r[i].key,L->r[j].key) ? L->r[i++]:L->r[j++];
	}

	while(i<=mid){
		L1.r[k++] = L->r[i++];
	}

	while(j<=high){
		L1.r[k++] = L->r[j++];
	}

	for(k=0,i=low;i<=high;k++,i++){
		L->r[i].key = L1.r[k].key;
	}
	return OK;
}

void MSort(SqList *L,int len){
	int i;

	for(i=1;i+2*len-1<=L->length;i=i+2*len)
		Merge(L,i,i+len-1,L->length);
	if(i+len-1<L->length)
		Merge(L,i,i+len-1,L->length);
}

Status MergeSort(SqList *L){
	int len;

	if(!L->length){
		printf("The SqList is Empty!");
		return ERROR;
	}

	for(len=1;len<L->length;len*=2){	
		MSort(L,len);
	}
	return OK;
}