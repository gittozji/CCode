#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	int weight;
	int parent, lchild, rchild;
}HTNode , *HuffmanTree; //¹ş·òÂüÊ÷
typedef char **HuffmanCode; //¹ş·òÂü±àÂë±í

void select(HuffmanTree HT,int m,int *s1,int *s2){
	int i=1,j=1;
	for(i;i<=m;i++){
		if(HT[i].parent==0){
			*s1=i;
			break;
		}	
	}
	for(i;i<=m;i++){
		if(HT[i].parent==0){
			if(i!=*s1){
				*s2=i;
				break;
			}
		}	
	}
	for(j;j<=m;j++){
		if(HT[j].parent==0&&HT[j].weight>0){
			if(HT[j].weight<HT[*s1].weight){
				*s2=*s1;
				*s1=j;
			}
			else{
				if(HT[j].weight<HT[*s2].weight&&*s1!=j){
					*s2=j;
				}
			}
		}
	}
}

int HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n){
	int i,m,s1,s2,start,c,f;
	char *cd;
	if(n<=1) return 0;
	m=2*n-1;
	(*HT) = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(i=1;i<=n;i++){
		(*HT)[i].weight=w[i-1];
		(*HT)[i].lchild=0;
		(*HT)[i].rchild=0;
		(*HT)[i].parent=0;
	}
	for(;i<=m;i++){
		(*HT)[i].weight=0;
		(*HT)[i].lchild=0;
		(*HT)[i].rchild=0;
		(*HT)[i].parent=0;
	}
	//½¨Á¢¹ş¸¥ÂüÊ÷
	for(i=n+1;i<=m;i++){
		select(*HT,m,&s1,&s2);
		(*HT)[s1].parent=i;
		(*HT)[s2].parent=i;
		(*HT)[i].lchild=s1;
		(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight+(*HT)[s1].weight;
	}
	
	//¹ş¸¥ÂüÒëÂë
	(*HC)=(HuffmanCode)malloc((n+1)*sizeof(char*));
	
	for(i=1;i<=n;i++){
		cd = (char*)malloc(n*sizeof(char));
		cd[n-1]='\0';
		start=n-1;
		for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)
			if((*HT)[f].lchild==c) cd[--start]='0';
			else cd[--start]='1';
		(*HC)[i]=(char*)malloc((n-start)*sizeof(char));
		strcpy((*HC)[i],&cd[start]);
		free(cd);
	}

	return 1;
}

void printHuffmanTree(HuffmanTree *HT,int m){
	for(int i=1;i<m;i++){
		printf("%3d: %3d %3d %3d %3d\n",i,(*HT)[i].weight,(*HT)[i].lchild,(*HT)[i].rchild,(*HT)[i].parent);
	}
}

void printHuffmanCoding(HuffmanCode *HC,int n){
	for(int i=1;i<=n;i++){
		printf("%s\n",(*HC)[i]);
	}
}

int main(){
	int w[8]={5,29,7,8,14,23,3,11};
	printf("¹ş¸¥ÂüÊ÷:\n");
	HuffmanTree HT = NULL;
	HuffmanCode HC = NULL;
	HuffmanCoding(&HT,&HC,w,8);
	printHuffmanTree(&HT,16);
	printf("¹ş¸¥ÂüÒëÂë:\n");
	printHuffmanCoding(&HC,8);
	return 0;
}