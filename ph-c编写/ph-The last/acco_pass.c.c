/*图书馆管理系统*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
    FILE *fp;
    char account[]="13207109";
    char password[]="ph1234";


    if((fp=fopen("acco_pass.dat","w"))==NULL)

        printf("HKJ");

    fwrite(account,sizeof(account),1,fp);
    fwrite(password,sizeof(password),1,fp);
    fclose(fp);


    getch();

}
