#include<stdio.h>
#include<string.h>
#define mm (ldata *)malloc(sizeof(ldata))
typedef struct data     /*定义结构体存放书籍信息*/
{
    char isbn[20];      /*ISBN码*/

    struct data *next;  /*节点*/
}ldata;
main()
{
int i=7,j=0;
     FILE *fp;
    ldata *head,*p1,*pm,*p2,*ls;
    char isbnfb[20];      /*ISBN码副本*/

    fp=fopen("pheorr.dat","wb");
    head=mm;
    p1=head;
    system("graftabl 936");
        p1=head;
    while(i==7)
    {
        printf(" 请依次输入ISBN码:\n");
        scanf("%s",isbnfb);
            strcpy(p1->isbn,isbnfb);
            printf("input n\n");
            scanf("%d",&i);
            pm=mm;
            p1->next=pm; ls=p1;
            p1=p1->next;





   }
   ls->next=NULL;

   p1=head;
   while(p1!=NULL)
   {
        fwrite(p1,sizeof(ldata),1,fp);
        p1=p1->next;

   }

   fclose(fp);
   fp=fopen("pheorr.dat","rb");
   while(!feof(fp))
   {
        fread(head,sizeof(ldata),1,fp);   printf("%s\n",head->isbn);
        head->next;
   }
   getch();
}
