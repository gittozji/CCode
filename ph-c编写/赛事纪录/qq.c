#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>
#define mm (team *)malloc(sizeof(team)) 
typedef struct team
{
    int fnumber;            /*比赛场数*/
    char name[20];          /*队名*/
    int win;                /*赢场*/
    int flat;               /*平场*/
    int lose;               /*负场*/
    int goal;               /*进球*/
    int fumble;             /*失球*/
    int score;              /*积分*/
    struct team *next;
}team;
int creat();                 /*新建球队*/
int inlet();                 /*赛况更新*/
int pai();                   /*排名*/
int xs(team*p1,int i);             /*显示排名情况*/
int main()
{
        int n=0;
        system("graftabl 936");
        do
        {
        system("cls");
        printf("   ***************************球队信息管理系统**************************\n");
        printf("   *                          1.新建球队信息                           *\n");        
        printf("   *                          2.比赛近况更新                           *\n");
        printf("   *                          3.最新球队排名                           *\n");
        printf("   *                          0.退出系统                               *\n");            
        printf("   *********************************************************************\n");
        printf("   *********************************************************************\n");
        printf("   请输入功能序号: ");
        scanf("%d",&n);    
        switch(n)
        {
            case 1: creat();break;
            case 2: inlet();break;
            case 3: pai();break;
            default:break;
        }
        }while(n);
}
int creat()
{
    FILE *fp;
    int fnumber;        
    char name[20];            
    int win;
    int flat;
    int lose;
    int goal;
    int fumble;
    int score; 
    int n;
    int i=0;
    team *head,*p,*pm,*p1;
    head=mm;
    p=head;

    fp=fopen("data.dat","wb");
    printf("输入球队数\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        p1=p;
        printf("输入第%d个队队名\n",i+1);
        fflush(stdin); 
        gets(p->name);
        p->fnumber=0;
        p->win=0;
        p->flat=0;
        p->lose=0;
        p->fumble=0;
        p->score=0;
        p->goal=0;
        pm=mm;
        p->next=pm;
        p=p->next;
    }
    p1->next=NULL;                     /*令链表尾为空*/
    while(head!=NULL)                  /*写入文件*/
    {
        fwrite(head,sizeof(team),1,fp);
        p1=head;
        head=head->next;
        free(p1);                     /*释放内存*/
    }
    printf(" 保存成功\n");
    fclose(fp);
    fflush(stdin);
    getch();
}
int inlet()
{
    FILE *fp;
    int i=0,j;
    int w;
    int l;
    team *head,*p1,*pcl1,*pcl=NULL,*pm;
    if((fp=fopen("data.dat","rb"))==NULL)      /*以“rb”方式打开文件*/
    {
        printf("无法打开");
        getchar();
    }
    head=mm;                                  /*申请内存*/
    p1=head;
    while(!feof(fp))                         /*读文件*/
    {
        i++;
        fread(p1,sizeof(team),1,fp);
        pm=mm;
        pcl1=pcl;           
        pcl=p1;
        p1->next=pm;
        p1=p1->next;
    }
    fclose(fp);
    pcl1->next=NULL;
    p1=head;
    for(j=0;j<i-1;j++)
    {
        printf("请输入“%s“的进球数，失球数：\n",p1->name);
        scanf("%d%d",&w,&l);
        if(w>l)
        {
            p1->win++;
            p1->score+=3;
        }
        if(l==w)
        {
            p1->flat++;
            p1->score+=1;
        }
        if(l>w)
        {
            p1->lose++;
        }
        p1->fnumber++;
        p1->goal+=w;
        p1->fumble+=l;
        p1=p1->next;
    }
    if((fp=fopen("data.dat","wb"))==NULL)
    {
        printf("无法打开");
        getchar();
    }
    while(head!=NULL)
    {
        fwrite(head,sizeof(team),1,fp);
        p1=head;
        head=head->next;
        free(p1);
    }
    printf("保存成功");
    fflush(stdin);
    getch();
    fclose(fp);   
}
int pai()
{
    FILE *fp;
    int hang=0;
    int i=1;
    team *head,*h=NULL,*p1,*ptr,*ptr1,*ptr2,*pm,*pls=NULL,*pls1;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(team),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    p1=head;
    while(p1!=NULL)                  /*排序核心算法*/
    {
        ptr=p1;
        p1=p1->next;
        ptr2=h;
        if(h==NULL)
        {
            h=ptr;
            h->next=NULL;
        }
        else
        {
            while((ptr->score<ptr2->score)&&(ptr2->next!=NULL))
            {
                ptr1=ptr2;
                ptr2=ptr2->next;
            }
            if(ptr->score>=ptr2->score)
            {
                if(ptr->score>ptr2->score)
                {
                    if(h==ptr2)
                        h=ptr;
                    else
                        ptr1->next=ptr;
                    ptr->next=ptr2;
                }
                if(ptr->score==ptr2->score)
                {
                    while((ptr->goal-ptr->fumble)<(ptr2->goal-ptr2->fumble)&&(ptr2->next!=NULL))
                    {
                        ptr1=ptr2;
                        ptr2=ptr2->next;
                    }
                    if((ptr->goal-ptr->fumble)>=(ptr2->goal-ptr2->fumble))
                    {
                        if(h==ptr2)
                            h=ptr;
                        else
                            ptr1->next=ptr;
                        ptr->next=ptr2;   
                    }
                    else
                    {
                        ptr2->next=ptr;
                        ptr->next=NULL;
                    }
                }
            }
            else
            {
                ptr2->next=ptr;
                ptr->next=NULL;
            }
        }

    }
    system("cls");
    printf("______________________________________________________________\n");
    printf(" 名次 ┃  队名  ┃赛场┃赢场┃负场┃平场┃进球┃失球┃积分┃\n");
    printf("______________________________________________________________\n");

    while(h!=NULL)
    {
        xs(h,i++);
        h=h->next;
        hang++;
        if(hang>8)
        {
            fflush(stdin);
            hang=0;
            getch();
            system("cls");
            printf("______________________________________________________________\n");
            printf(" 名次 ┃  队名  ┃赛场┃赢场┃负场┃平场┃进球┃失球┃积分┃\n");
            printf("______________________________________________________________\n");
        }
    }
    fflush(stdin);
    getch();
    fclose(fp);
}
int xs(team *p1,int i)
{

    printf("第%-2d名┃%-8s┃%-4d┃%-4d┃%-4d┃%-4d┃%-4d┃%-4d┃%-4d┃\n",i,p1->name,p1->fnumber,p1->win,p1->lose,p1->flat,p1->goal,p1->fumble,p1->score);
    printf("______________________________________________________________\n");
}


