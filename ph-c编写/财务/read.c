#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define mm1 (information *)malloc(sizeof(information))
#define mm2 (people *)malloc(sizeof(people))
typedef struct information
{
    char account[15];/*账号，用于判断此结构体归属哪个用户*/
    int year;
    int month;
    int day;
    int in_out;     /*0为收入，1为支出*/
    double money;   /*记录此条信息的金钱*/
    char aim[30];   /*备注*/
    struct information *next;
}information;
typedef struct people
{
    char account[15];
    char password[15];
}people;
int deng();                /*登陆*/
int sign();                /*注册新用户*/
int creat(people *pq);     /*增加收入支出信息*/
int look(people *pq);      /*查看*/
int xs(information *p1);   /*显示功能*/
int tong(people *pq);      /*统计余额*/
int sc(people *pq);        /*删除修改函数*/
int ftime(information *p,int year1,int month1,int day1,int year2,int month2,int day2);/*比较时间先后*/
int main()
{
    FILE *fp;
    char c;
    system("graftable 936");       /*显示中文*/
    system("cls");                 /*清屏(下同)*/
    printf(" 1-账号登陆\n");
    printf(" 2-注册账号\n");
    fflush(stdin);
    c=getch();
    switch(c)
    {
        case '1':
            deng();break;
        case '2':
            sign();break;
        default:break;
    }
    return main();              /*返回主函数，用于循环*/
}
int deng()
{
    FILE *fp;
    int qql=0;
    char accountfb[15];
    char passwordfb[15];
    int judge=0;
    char c;
    people *ptr;
    ptr=mm2;                   /*申请内存，下同*/
    system("cls");
    printf(" 请输入账号\n");
    fflush(stdin);
    gets(accountfb);
    printf("请输入密码\n");
    fflush(stdin);
    gets(passwordfb);
    if((fp=fopen("a_p.dat","rb"))==NULL)     /*打开存放账号密码文件*/
    {
        printf("无法打开\n");
        getch();
    }
    while(!feof(fp))                          /*与文件内容核对，匹配，则judge=1进行登录*/
    {
        fread(ptr,sizeof(people),1,fp);
        if(!(strcmp(ptr->account,accountfb))&&!(strcmp(ptr->password,passwordfb)))
        {
            judge=1;
            break;
        }
    }

    do
    {
        system("cls");
        qql=0;
        if(judge==1)
        {
            printf(" 登陆成功\n");
            printf("1-添加信息\n2-删除修改\n3-查看信息\n4-统计信息\n");
            fflush(stdin);
            c=getch();
            switch(c)
            {
                case '1':
                    creat(ptr);break;
                case '2':
                    sc(ptr);break;
                case '3':
                    look(ptr);break;
                case '4':
                    tong(ptr);break;
                default:break;
            }

        }
        else
        {
            printf(" 登陆失败，将返回\n");
            fflush(stdin);
            getch();
        }
        printf(" 1-返回,2-结束\n");
        fflush(stdin);
        c=getch();
        if(c=='1')
            qql=1;
        else
            qql=0;
    }while(qql==1);
}
int sign()
{
    FILE *fp;
    people *ptr1;
    char accountfb[15];
    char passwordfb[15];
    int judge=0;
    ptr1=mm2;
    system("cls");
    if((fp=fopen("a_p.dat","ab+"))==NULL)
    {
        printf("无法打开\n");
        getch();
    }
    printf(" 输入账号\n");
    do
    {
        judge=0;
        fflush(stdin);
        gets(accountfb);
        rewind(fp);
        while(!feof(fp))
        {
            fread(ptr1,sizeof(people),1,fp);
            if(!(strcmp(ptr1->account,accountfb)))
            {
                judge=1;
                printf(" 此号码已存在，请重新输入\n");
                break;
            }
        }
    }while(judge==1);
    fclose(fp);
    printf(" 输入密码\n");
    fflush(stdin);
    gets(passwordfb);
    strcpy(ptr1->account,accountfb);
    strcpy(ptr1->password,passwordfb);
    if((fp=fopen("a_p.dat","ab+"))==NULL)
    {
        printf("无法打开，将返回");
        getch();
        return sign();
    }
    fwrite(ptr1,sizeof(people),1,fp);         /*写进文件*/
    fclose(fp);
    printf(" 保存成功");
    fflush(stdin);
    getch();
}
int creat(people *pq)
{
    FILE *fp;
    char c;
    char accountfb[15];
    int in_outfb;
    double moneyfb;
    char aimfb[30];
    information *ptr;
    int year,month,day;
    time_t nowtime;
    struct tm *timeinf;
    time(&nowtime);
    timeinf=localtime(&nowtime);
    year=timeinf->tm_year+1900;
    month=timeinf->tm_mon+1;
    day=timeinf->tm_mday;
    ptr=mm1;
    system("cls");
    strcpy(ptr->account,pq->account);
    printf(" 0-收入，1-支出\n");
    scanf("%d",&in_outfb);
    printf(" 请输入金额\n");
    scanf("%lf",&moneyfb);
    printf(" 请输入备注\n");
    fflush(stdin);
    gets(aimfb);
    strcpy(ptr->aim,aimfb);
    ptr->money=moneyfb;
    ptr->in_out=in_outfb;
    ptr->year=year;
    ptr->month=month;
    ptr->day=day;
    if((fp=fopen("data.dat","ab+"))==NULL)
    {
        printf("无法打开，将返回");
        getch();
        return deng();
    }
    fwrite(ptr,sizeof(information),1,fp);
    fclose(fp);
    printf(" 保存成功");
    printf(" 是否继续增添y/n\n");
    fflush(stdin);
    c=getch();
    if(c=='y')
        return creat(pq);
    else
        return main();
}
int look(people *pq)
{
    FILE *fp;
    information *head,*p1,*p2,*pm,*pls1,*pls=NULL;
    int hang=0;
    int year1,year2,month1,month2,day1,day2;
    system("cls");
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    head=mm1;
    p1=head;
    printf(" 请输入起始时间\n");
    scanf("%d%d%d",&year1,&month1,&day1);
    printf(" 请输入终止时间\n");
    scanf("%d%d%d",&year2,&month2,&day2);
    printf("____________________________________________________________________________\n");
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(information),1,fp);
        pm=mm1;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举*/
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls1->next=NULL;               /*链表尾部赋为空*/
    p1=head;
    while(p1!=NULL)
    {
        if(!(strcmp(p1->account,pq->account))&&ftime(p1,year1,month1,day1,year2,month2,day2))
        {
            xs(p1);
            hang++;
            if(hang>5)
            {
                fflush(stdin);
                hang=0;
                getch();
                system("cls");
            }
        }
        p1=p1->next;
    }
    fflush(stdin);                      /*清除缓冲流，下同*/
    getch();   
}
int xs(information *p1)
{
    printf(" 时间：%d年%d月%d日\n",p1->year,p1->month,p1->day);
    if(p1->in_out==0)
        printf(" 收入：%.2lf\n",p1->money);
    if(p1->in_out==1)
        printf(" 支出：%.2lf\n",p1->money);
    printf(" 备注： %s\n",p1->aim);
    printf("____________________________________________________________________________\n");
}
int tong(people *pq)
{
    FILE *fp;
    information *head,*p1,*p2,*pm,*pls1,*pls=NULL;
    int year1,year2,month1,month2,day1,day2;
    double sum1=0,sum2=0;
    system("cls");
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    head=mm1;
    p1=head;
    printf(" 请输入起始时间\n");
    scanf("%d%d%d",&year1,&month1,&day1);
    printf(" 请输入终止时间\n");
    scanf("%d%d%d",&year2,&month2,&day2);
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(information),1,fp);
        pm=mm1;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举*/
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls1->next=NULL;               /*链表尾部赋为空*/
    p1=head;
    while(p1!=NULL)
    {
        if(!(strcmp(p1->account,pq->account))&&ftime(p1,year1,month1,day1,year2,month2,day2))
        {
            if(p1->in_out==0)
                sum1=sum1+p1->money;
            if(p1->in_out==1)
                sum2=sum2+p1->money;
        }
        p1=p1->next;
    }
    printf(" 总收入：%.2lf\n",sum1);
    printf(" 总支出：%.2lf\n",sum2);
    printf(" 余额为：%.2lf\n",sum1-sum2);
    fflush(stdin);                      /*清除缓冲流*/
    getch();
}
int sc(people *pq)
{
    FILE *fp;
    int i=0;
    char accountfb[15];
    int year1,year2,month1,month2,day1,day2;
    int in_outfb;     /*0为收入，1为支出*/
    double moneyfb;
    char aimfb[30];
    information *head,*p1,*p2,*pm,*pls1,*pls=NULL;
    char c;
    long int date1,date2;
    system("cls");
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    head=mm1;
    p1=head;
    printf(" 请输入起始时间\n");
    scanf("%d%d%d",&year1,&month1,&day1);
    printf(" 请输入终止时间\n");
    scanf("%d%d%d",&year2,&month2,&day2);
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(information),1,fp);
        pm=mm1;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举*/
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls1->next=NULL;               /*链表尾部赋为空*/
    p1=head;
    while(p1!=NULL)
    {

        i++;
        if(!(strcmp(p1->account,pq->account))&&ftime(p1,year1,month1,day1,year2,month2,day2))
        {
            xs(p1);
            printf(" 1-删除，2-修改\n\n");
            fflush(stdin);
            c=getch();
            if(c=='1')
            {
                if(i<=1)
                {
                    head=p1->next;
                    i=0;
                }

                else
                    pls->next=p1->next;

            }
            if(c=='2')
            {
                printf(" 0-收入，1-支出\n");
                scanf("%d",&in_outfb);
                printf(" 请输入金额\n");
                scanf("%lf",&moneyfb);
                printf(" 请输入备注\n");
                fflush(stdin);
                gets(aimfb);
                strcpy(p1->aim,aimfb);
                p1->in_out=in_outfb;
            }   
        }
        pls=p1;
        p1=p1->next;
    }
    if((fp=fopen("data.dat","wb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    while(head!=NULL)
    {
        fwrite(head,sizeof(information),1,fp);
        head=head->next;
    }
    fclose(fp);
    fflush(stdin);                      /*清除缓冲流*/
    getch();   
}
int ftime(information *p,int year1,int month1,int day1,int year2,int month2,int day2)
{
    long int date1=0;
    long int date2=0;
    long int date=0;
    date1=year1*10000+month1*100+day1;
    date2=year2*10000+month2*100+day2;
    date=p->year*10000+p->month*100+p->day;
    if(date>=date1&&date<=date2)
        return 1;
    else
        return 0;
}
