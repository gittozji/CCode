/*×Ö·û´®µÄ²âÊÔ*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(){
	char *s=(char*)malloc(3*sizeof(char));
	char *cd=(char*)malloc(6*sizeof(char));
	
	cd[5]='\0';
	cd[4]='q';
	cd[3]='w';
	strcpy(s,&cd[3]);
	printf("%s",s);
	return 0;
}