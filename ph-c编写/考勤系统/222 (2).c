#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NULL 0
struct stud_node{
                    char num[10];
                    char name[20];
                    char clas[10];
                    char time[20];
                    char kecheng[10];
                    int Cyuyan,Math,English;
                    int chidao_num;
                    int quexi_num;
                    int zaotui_num;
                    int rate;
                    struct stud_node*next;
                };
void menu();
struct stud_node *add() ;
struct stud_node *del();
struct stud_node *search();
struct stud_node *modify();
struct stud_node *pri();
char c;
struct stud_node *add()        /*增加*/
{
    FILE *fp;
    struct stud_node p;
    char ch;
    int n;
    fp=fopen("c:\\stud_node.txt","a");
    if(fp==NULL)
    {
       printf("can't open the file!");
       return;
    }
    printf("do you want to input?please input 'Y' or 'N':\n");
    ch=getchar();
    while(ch=='Y')
   {
      printf("input clas num name kecheng chidao_num quexi_num zaotui_num :\n") ;
      scanf("%s%s%s%s%d%d%d",p.clas,p.num,p.name,p.kecheng,&p.chidao_num,&p.quexi_num,&p.zaotui_num);
      fprintf(fp,"%s %s %s %s %d %d %d",p.clas,p.num,p.name,p.kecheng,p.chidao_num,p.quexi_num,p.zaotui_num);
      printf("do you want to input?please input 'Y' or 'N':\n");
      ch=getchar();
   }

   fclose(fp);
}
struct stud_node * del()
{
    char*num=0;
    char*clas=NULL;
    char*name=NULL;
    char Cyuyan[10],Math[10],English[10];
    int zaotui_num=0,chidao_num=0,quexi_num=0;
    int rate=0;
    FILE*fp;
    struct stud_node*p1,*p2,*p;
    struct stud_node*head,*tail;
    head=p=tail=p1=p2=NULL;
    if((fp=fopen("c:\\stud_node.txt","a"))==NULL)
    {
        printf("File open error!");
        exit(0);
    }    
    while(!feof(fp))
    {
        if((p=(struct stud_node*)malloc(sizeof(struct stud_node)))==NULL)
        {
            printf("Can not malloc menmory!!");
            exit(0);
        }
        fprintf(fp,"%s %s %s %s %s %s %s %d %d %d %d",clas,num,name,Cyuyan,Math,English,zaotui_num,chidao_num,quexi_num,rate);
        p->next=NULL;

        if(head==NULL)
        {
            head=p;
        }
        else
        {
            tail->next=p;
        }
        tail=p;        
    }
    if(fclose(fp))
    {
        printf("Can not close the file!\n");
        getch();
        exit(1);
    }       
    if(strcmp(head->num,num)==0)
    {
        p=head;
        head=head->next;
        free(p);
    }
    for(p1=head,p=head->next,p2=p->next;p!=NULL;p1=p1->next,p=p->next,p2=p2->next)
    {
        if(strcmp(p->num,num)==0)
        {
            p1->next=p2;
            free(p);
            break;
        }
    }
    if((fp=fopen("c:\\stud_node.txt","a"))==NULL)
    {
        printf("File open error!");
        exit(0);
    }
    for(p=head;p!=NULL;p=p->next){
        if(p!=head){
           fputc(c,fp);
        }
    fprintf(fp,"%s %s %s %s %s %s %d %d %d %d ",clas,num,name,Cyuyan,Math,English,&zaotui_num,&chidao_num,&quexi_num,&rate);
    }
    if(fclose(fp)){
        printf("Can not close the file.");
        exit(0);
    }
}
struct stud_node *search()                                     /*查找学生信息*/
{
     char num[10];
     char name[20];
     char clas[10];
     char ch;
     int Cyuyan[10],Math[10],English[10];
     int zaotui_num,chidao_num,quexi_num;
     FILE*fp;
     struct stud_node*head=NULL,*p=NULL,*q;
     head=(struct stud_node*)malloc(sizeof(struct stud_node));
     p=head;

     printf("Do you wang to continue searching?please input'Y'or'N'\n");
     ch=getchar();
      if(ch=='Y'){
         fp=fopen("c:\\stud_node.txt","r");
             if(fp==NULL){
                         printf("can't open the file");
                          }
             else {
               while(!feof(fp)){
                 q=(struct stud_node*)malloc(sizeof(struct stud_node));
                 fscanf(fp,"%s%s%s%s%s%s%d%d%d%d",
                 p->clas,p->num,p->name,p->Cyuyan,p->Math,p->English,p->zaotui_num,p->chidao_num,p->quexi_num,p->rate);
                 p->next=q;
                 p=p->next;
              }
            }
           p->next=NULL;
       }
       fclose(fp);
       printf("search the information by num,input '1'\n");
       printf("search the information by clas,input '2'\n");
       printf("search the information by kecheng,input '3'\n");
       fflush(stdin);
       ch=getchar();
       if(ch=='1'){                                                /*按学号查找*/
                         printf("please input your num");
                         fflush(stdin);
                         gets(num);
                         q=head;
                         while(q!=NULL)
                         {
                            if(!strcmp(q->num,num))
                            {
                                printf("clas=%s,num=%s,name=%s,Cyuyan=%s,Math=%s,English=%s,zaotui=%d,chidao=%d,quexi=%d,rate=%d",
                                                   p->clas,p->num,p->name,p->Cyuyan,p->Math,p->English,p->zaotui_num,p->chidao_num,p->quexi_num,p->rate);
                                getch();
                                break;
                            }
                            q=q->next;
                         }
                 }

       if(ch=='2'){                                                 /*按班级查找*/
                        printf("please input your clas");
                        scanf("%s",clas);
                        getchar();
                        q=(struct stud_node*)malloc(sizeof(struct stud_node));
                        p=(struct stud_node*)malloc(sizeof(struct stud_node));
                        q=head;
                        while(q!=NULL){
                                         if((*q->clas<=10)||(*q->clas>=0))
                                         {
                                            printf("clas=%s,num=%s,name=%s,Cyuyan=%s,Math=%s,English=%s,zaotui=%d,chidao=%d,quexi=%d,rate=%d",
                                                   p->clas,p->num,p->name,p->Cyuyan,p->Math,p->English,p->zaotui_num,p->chidao_num,p->quexi_num,p->rate);
                                         }
                                       q=q->next;
                                      }

                 }

        if(ch=='3'){                                          /*按课程*/
                        printf("please input Cyuyan,Math,English");
                        scanf("%s%s%s",Cyuyan,Math,English);
                        getchar();
                        q=(struct stud_node*)malloc(sizeof(struct stud_node));
                        p=(struct stud_node*)malloc(sizeof(struct stud_node));
                        q=head;
                        while(q!=NULL){
                                         if((q->Cyuyan)||q->Math||q->English)
                                         {
                                             printf("clas=%s,num=%s,name=%s,kecheng=%s,Cyuyan=%s,Math=%s,English=%s,zaotui=%d,chidao=%d,quexi=%d,rate=%d",
                                                   p->clas,p->num,p->name,p->Cyuyan,p->Math,p->English,p->zaotui_num,p->chidao_num,p->quexi_num,p->rate);
                                         }
                                      q=q->next;
                                      }
                 }

}
struct stud_node * modify()
{
    FILE*fp;
    char num[10];
    char name[20];
    char clas[10];
    char kecheng[20];
    int i,j,k=1,m=0,p=0,snum;
    int chidao_num=0,quexi_num=0,zaotui_num=0;
    int rate=0;
    if((fp=fopen("c:\\stud_node.txt","a"))==NULL)
    {
       printf("can not open\n");
       return;
    }
    while(!feof(fp))
        if((fp=fopen("c:\\stud_node.txt","a"))==NULL){
           m++;
        }
        if(m==0){
           printf("No record!\n");
           return;
        }
    printf("please input the number of the student which do you want to modify!\n:");
    scanf("%d",&snum);
    for(i=0;i<m;i++)
       if(i<m)
       {
           while(k==1)
           {
                    printf("1.clas\n2.name\n3.num\n4.kecheng\n5.chidao_num\n6.zaotui_num\n7.quexi_num\n8.rate\n");
                    scanf("%d",&k);
                    switch(p)
                    {
                        case 1:printf("please input new clas:");fprintf(fp,"%s",clas);scanf("%s",clas);
                                printf("weather continue modify this student node?\n1.yes\n2.no\n");scanf("%d",&k);break;

                        case 2:printf("please input new name:");fprintf(fp,"%s",name);scanf("%s",name);
                                printf("weather continue modify this student node?\n1.yes\n2.no\n");scanf("%d",&k);break;

                        case 3:printf("please input new num:");fprintf(fp,"%s",num);scanf("%s",num);
                                printf("weather continue modify this student node?\n1.yes\n2.no\n");scanf("%d",&k);break;

                        case 4:printf("please input new kecheng:");fprintf(fp,"%s",kecheng);scanf("%s",kecheng);
                                printf("weather continue modify this student node?\n1.yes\n2.no\n");scanf("%d",&k);break;

                        case 5:printf("please input new chidao_num:");fprintf(fp,"%d",chidao_num);scanf("%s",&chidao_num);
                                printf("weather continue modify this student node?\n1.yes\n2.no\n");scanf("%d",&k);break;

                        case 6:printf("please input new zaotui_num:");fprintf(fp,"%s",zaotui_num);scanf("%s",&zaotui_num);
                                printf("weather continue modify this student node?\n1.yes\n2.no\n");scanf("%d",&k);break;

                        case 7:printf("please input new quexi_num:");fprintf(fp,"%s",quexi_num);scanf("%s",&quexi_num);
                                printf("weather continue modify this student node?\n1.yes\n2.no\n");scanf("%d",&k);break;

                        case 8:printf("please input new rate:");fprintf(fp,"%s",rate);scanf("%s",&rate);
                                printf("weather continue modify this student node?\n1.yes\n2.no\n");scanf("%d",&k);break;
                    }
           }
       }
       else
       {
           printf("can not find!");
           getchar();
           return;
       }
       if((fp=fopen("c:\\stud_node.txt","a"))==NULL)
       {
           printf("can not open\n");
           return;
       }
       fprintf(fp,"%s %s %s %s %d %d %d %d",clas,num,name,kecheng,chidao_num,zaotui_num,quexi_num,rate);
       printf("can not sate!");
       getch();
       exit(0);
}
struct stud_node * pri()
{
     FILE*fp;
     char num[10];
     char name[20];
     char clas[10];
     char kecheng[20];
     int chidao_num=0,quexi_num=0,zaotui_num=0;
     int i,rate=0;
     int time=0;
     int n=100;
     if((fp=fopen("c:\\stud_node.txt","a"))==NULL){
         printf("File oper error!\n");
         exit(0);
     }
     for(i=0;i<n;i++)
     {
         fscanf(fp,"%d%s%s%s%s%d%d%d%d",&time,clas,num,name,kecheng,&chidao_num,&quexi_num,&zaotui_num,rate);
         printf("%d%s%s%s%s%s%d%d%d%d",time,clas,num,name,kecheng,chidao_num,quexi_num,zaotui_num,rate);
     }
     if(fclose(fp)){
        printf("Can not close the file.");
        exit(0);
    }
}
void menu()
{
    system("cls");
    printf("\n\n\n\n");
    printf("\t\t|---welcome to the student attendance system-----|\n");
    printf("\t\t|                                                |\n");
    printf("\t\t|\t 1:add                                   |\n");
    printf("\t\t|\t 2:del                                   |\n");
    printf("\t\t|\t 3:search                                |\n");
    printf("\t\t|\t 4:modify                                |\n");
    printf("\t\t|\t 5:pri                                   |\n");
    printf("\t\t|\t 6:count                                 |\n");
    printf("\t\t|\t 0:exit                                  |\n");
    printf("\t\t|------------------------------------------------|\n\n");
    printf("\n\n\n");
    printf("\t\t\tchoose(0-6):");
}
int main()
{
    int n;
    menu();
    scanf("%d",&n);
    system("cls");
    system("graftabl 936");
    clrscr();
    while(n){
        switch(n){
                        case 1:add();break;
                        case 2:del();break;
                        case 3:search();break;
                        case 4:modify();break;
                        case 5:pri();break;
                        case 6:break;
                        default:printf("you input a wrong number\n");break;

        }
    getch();
    menu();
    scanf("%d",&n);
   }
}

