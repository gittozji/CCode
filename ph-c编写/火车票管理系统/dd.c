#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define mm (data *)malloc(sizeof(data))          /*申请内存*/
#define mm1 (people *)malloc(sizeof(people))
typedef struct data
{   long int date;       /*发车日期*/
    int fh;              /*发车时间，小时*/
    int fm;              /*分钟*/
    int dh;              /*到站时间，小时*/
    int dm;              /*分钟*/
    char num[7];         /*车次号， 如T11*/
    char mdd[15];        /*目的地*/
    char qsd[15];        /*起始地*/
    double money;        /*硬座价格，硬卧和软卧可由此乘以2与3*/
    int rw;              /*软卧余票*/
    int yw;              /*硬卧余票*/
    int yz;              /*硬座余票*/
    struct data *next;   /*下一节点*/
}data;                   /*结构体名称*/
typedef struct people
{
    long int date;       /*发车日期*/
    char account[15];    /*账号*/
    char password[15];   /*密码*/
    char name[15];       /*姓名*/
    char num[7];         /*车次*/
    int zuowei;          /*座位，1表示硬座，2表示硬卧，3表示软卧*/
    struct people *next;
}people;
int creat();             /*创建火车票*/
int look();              /*查看火车票*/
int xs(data *head);      /*显示函数*/
int sign();              /*注册函数*/
int deng();              /*登陆*/
int ding();              /*订票*/
int tui();               /*退票*/
int main()
{
    char c;
    system("graftable 936");       /*显示中文*/
    system("cls");                 /*清屏(下同)*/
    printf("\n\n\t\t   欢迎使用火车票订票系统\n");    /*界面*/
    printf("\t\t\t1-创建火车票\n");
    printf("\t\t\t2-查看\n");
    printf("\t\t\t3-用户登陆\n");
    printf("\t\t\t4-用户注册\n");
    printf("\t\t\t5-订票\n");
    printf("\t\t\t6-退票\n");
    printf("\t\t\t其他键退出\n");
    c=getch();
    switch(c)                     /*选择*/
    {
        case '1':creat();break;
        case '2':look();break;
        case '3':deng();break;
        case '4':sign();break;
        case '5':ding();break;
        case '6':tui();break;
    }
    getch();
    return main();
}
int creat()
{
    FILE *fp;
    char c;
    int i;
    char num[7];
    char mdd[15];
    char qsd[15];
    double money;
    data *head=mm;
    system("cls");
    printf("请输入编号\n");
    fflush(stdin);
    gets(num);
    printf("输入起始点\n");
    fflush(stdin);
    gets(qsd);
    printf("输入目的地\n");
    fflush(stdin);            /*一般写getch（）和gets（）等语句之前都要写fflush（）*/
    gets(mdd);
    printf("请输入日期（20140501）\n");
    scanf("%ld",&head->date);
    printf("请输入发车时间（9 30）\n");
    scanf("%d%d",&head->fh,&head->fm);
    printf("请输入到站时间（19 00）\n");
    scanf("%d%d",&head->dh,&head->dm);
    printf("输入硬座价格\n");
    scanf("%lf",&money);
    strcpy(head->mdd,mdd);
    strcpy(head->qsd,qsd);
    head->money=money;
    strcpy(head->num,num);
    head->rw=30;                  /*系统默认软卧余票30*/
    head->yw=30;
    head->yz=40;
    if((fp=fopen("data.dat","ab+"))==NULL)      /*打开存放火车票信息的文件*/
    {
        printf("无法打开，将返回");
        getch();
    }
    fwrite(head,sizeof(data),1,fp);             /*将结构体写入文件*/
    fclose(fp);
    printf(" 保存成功");
    printf("是否继续创建?(y/n)\n");
    c=getch();
    if(c=='y')
        return creat();                        /*返回creat（）函数，即实现循环*/
    else
        return main();
}
int look()
{
    FILE *fp;
    data *head=mm,*p1,*pls=NULL,*pm;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    p1=head;
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(data),1,fp);
        pm=mm;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls->next=NULL;              /*链表尾部赋为空*/
    p1=head;
    system("cls");
    while(p1->next!=NULL)
    {
        xs(p1);getch();system("cls");     /*显示火车票信息*/
        p1=p1->next;
    }
}
int xs(data *head)                        /*显示火车票信息*/
{
    printf("车次：%s   路途：%s->%s    日期：%ld\n",head->num,head->qsd,head->mdd,head->date);
    printf("发车时间 %d:%d,到站时间 %d:%d\n",head->fh,head->fm,head->dh,head->dm);
    printf("硬座:%.2lf元,硬卧:%.2lf元,软卧:%.2lf元\n",head->money,head->money*2,head->money*3);
    printf("硬座余票:%d,硬卧余票:%d,软卧余票:%d\n",head->yz,head->yw,head->rw);
    printf("\n");

}
int sign()
{
    char account[15];
    int judge=0;                        /*用于判断具体判断什么，看代码*/
    char num1[7]="0";
    FILE *fp,*fp1;
    people *head,*head1,*pm,*pls,*p1;    /*定义指针变量*/
    head=mm1;
    if((fp1=fopen("yonhu.dat","ab+"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    head1=mm1;
    p1=head1;
    while(!feof(fp1))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(people),1,fp1);
        pm=mm1;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp1);
    pls->next=NULL;              /*链表尾部赋为空*/
    p1=head1;
    system("cls");
    printf("请输入申请账号\n");
    fflush(stdin);
    gets(account);
    pm=p1;
    do                                  /*以下实现判断账号是否存在*/
    {   judge=0;
        p1=pm;
        while(p1->next!=NULL)
        {
            if(strcmp(p1->account,account)==0)
            {
                judge=1;
                break;
            }
            p1=p1->next;

        }
        if(judge==1)
        {
            printf("%s已经存在，请更改，重新输入\n",account);
            fflush(stdin);
            gets(account);
        }
    }while(judge==1);
    strcpy(head->account,account);
    printf("请输入密码\n");
    fflush(stdin);
    gets(head->password);
    printf("请输入名字\n");
    fflush(stdin);
    gets(head->name);
    strcpy(head->num,num1);
    head->date=0;
    head->zuowei=0;
    if((fp=fopen("yonhu.dat","ab+"))==NULL)
    {
        printf("无法打开，将返回");
        getch();
    }
    fwrite(head,sizeof(people),1,fp);
    fclose(fp);
    printf("注册成功");

}
int deng()
{
    FILE *fp;
    int judge=0;
    char account[15],password[15];
    people *head=mm1,*p1,*pls=NULL,*pm;
    if((fp=fopen("yonhu.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    p1=head;
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(people),1,fp);
        pm=mm1;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls->next=NULL;              /*链表尾部赋为空*/
    p1=head;
    system("cls");
    printf("请输入账号\n");
    fflush(stdin);
    gets(account);
    printf("请输入密码\n");
    fflush(stdin);
    gets(password);
    while(p1->next!=NULL)           /*在链表中找到输入的用户*/
    {
        if(strcmp(p1->password,password)==0&&(strcmp(p1->account,account)==0))
        {
            judge=1;              /*用于给下面说明已经找到*/
            break;
        }
        p1=p1->next;
    }
    system("cls");
    if(judge==1)                   /*找到该用户，可进行以下操作*/
    {
        printf("姓名:%s\n",p1->name);
        printf("已定的票:%s车次,日期:%ld，",p1->num,p1->date);
        if(p1->zuowei==1)
            printf("硬座");
        if(p1->zuowei==2)
            printf("硬卧");
        if(p1->zuowei==3)
            printf("软卧");
    }
    else
    {
        printf("账号或密码错误\n");
    }
    getch();

}
int ding()
{
    char c;
    int cc;
    char qsd[15],mdd[15];
    people *head=mm1,*p1,*pls=NULL,*pm;
    int judge=0,judge1=0;
    FILE *fp;
    char account[15],password[15];
    char num[7];
    long int date=0;
    data *dhead=mm,*dp1,*dpls=NULL,*dpm;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    dp1=dhead;
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(dp1,sizeof(data),1,fp);
        dpm=mm;
        dp1->next=dpm;
        dpls=dp1;
        dp1=dp1->next;
    }
    fclose(fp);
    dpls->next=NULL;              /*链表尾部赋为空*/
    dp1=dhead;
    system("cls");
    if((fp=fopen("yonhu.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    p1=head;
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(people),1,fp);
        pm=mm1;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls->next=NULL;              /*链表尾部赋为空*/
    p1=head;
    system("cls");
    printf("请先登录\n");
    printf("请输入账号\n");
    fflush(stdin);
    gets(account);
    printf("请输入密码\n");
    fflush(stdin);
    gets(password);
    while(p1->next!=NULL)                /*找用户*/
    {
        if(strcmp(p1->password,password)==0&&(strcmp(p1->account,account)==0))
        {
            judge=1;                      /*judge=1表示找到*/
            break;
        }
        p1=p1->next;
    }
    system("cls");
    if(judge==1)                          /*找到该用户*/
    {
        printf("姓名:%s\n",p1->name);

    }
    else
    {
        printf("账号或密码错误\n");
    }
    if(judge==1)
    {
        printf("1-按车次号订票\n");
        printf("2-按起始地，目的地订票\n");
        fflush(stdin);
        c=getch();
        if(c=='1')
        {
            printf("请输入车次号\n");
            gets(num);
            printf("请输入日期\n");
            scanf("%ld",&date);
            dpm=dhead;
            while(dpm!=NULL)             /*找到该火车票信息存放的结构体*/
            {
                if(strcmp(dpm->num,num)==0&&dpm->date==date)
                {
                    judge1=1;
                    break;
                }
                dpm=dpm->next;
            }
        }
        if(c=='2')
        {
            printf("请输入起始地\n");
            fflush(stdin);
            gets(qsd);
            printf("输入目的地\n");
            fflush(stdin);
            gets(mdd);
            printf("请输入日期\n");
            scanf("%ld",&date);
            dpm=dp1;
            while(dpm!=NULL)
            {
                if(strcmp(dpm->qsd,qsd)==0&&strcmp(dpm->mdd,mdd)==0&&dpm->date==date)
                {
                    judge1=1;
                    break;
                }
                dpm=dpm->next;
            }
        }
        if(judge1!=1)
        {
            printf("未找到符合车次\n");
        }
        if(judge1==1)
        {
            xs(dpm);
            printf("1-购买硬座，2-购买硬卧，3-购买软卧\n");
            scanf("%d",&cc);
            if(cc==1)
            {
                dpm->yz--;            /*硬座余票减掉1*/
                p1->zuowei=1;
            }
            if(cc==2)
            {
                dpm->yw--;
                p1->zuowei=2;
            }
            if(cc==3)
            {
                dpm->rw--;
                p1->zuowei=3;
            }
            p1->date=dpm->date;              /*用户中的日期更变为火车票的日期*/
            strcpy(p1->num,dpm->num);

            if((fp=fopen("yonhu.dat","wb"))==NULL)       /*以下操作位保存信息于文件*/
            {
                printf("无法打开");
                getch();
            }
            while(head!=NULL)
            {
                fwrite(head,sizeof(people),1,fp);
                head=head->next;
            }
            fclose(fp);


            if((fp=fopen("data.dat","wb"))==NULL)
            {
                printf("无法打开");
                getch();
            }
            while(dhead->next!=NULL)
            {
                fwrite(dhead,sizeof(data),1,fp);
                dhead=dhead->next;
            }
            fclose(fp);
            printf("订票成功");
        }
    }

}
int tui()
{
    FILE*fp;
    int judge=0;
    char c;
    char num1[7]="0";
    char account[15],password[15];
    data *dhead=mm,*dp1,*dpls=NULL,*dpm;
    people *head=mm1,*p1,*pls=NULL,*pm;  
    if((fp=fopen("yonhu.dat","rb"))==NULL)
    {
        printf("无法打开");
        getch();
    }
    p1=head;
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(people),1,fp);
        pm=mm1;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls->next=NULL;              /*链表尾部赋为空*/
    p1=head;
    system("cls");
    printf("请先登录\n");
    printf("请输入账号\n");
    fflush(stdin);
    gets(account);
    printf("请输入密码\n");
    fflush(stdin);
    gets(password);
    while(p1->next!=NULL)
    {
        if(strcmp(p1->password,password)==0&&(strcmp(p1->account,account)==0))
        {
            judge=1;
            break;
        }
        p1=p1->next;
    }
    system("cls");
    if(judge==1)
    {
        printf("姓名:%s\n",p1->name);
        printf("已定的票:%s车次,日期:%ld，",p1->num,p1->date);
        if(p1->zuowei==1)
            printf("硬座");
        if(p1->zuowei==2)
            printf("硬卧");
        if(p1->zuowei==3)
            printf("软卧");
        printf("是否退票(y/n)\n");
        c=getch();
        if(c=='y')
        {
            if((fp=fopen("data.dat","rb"))==NULL)
            {
                printf("无法打开");
                getch();
            }
            dp1=dhead;
            while(!feof(fp))                /*将文件信息读进链表*/
            {
                fread(dp1,sizeof(data),1,fp);
                dpm=mm;
                dp1->next=dpm;
                dpls=dp1;
                dp1=dp1->next;
            }
            fclose(fp);
            dpls->next=NULL;              /*链表尾部赋为空*/
            dp1=dhead;   
            while(dp1!=NULL)
            {
                if(strcmp(dp1->num,p1->num)==0&&dp1->date==p1->date)
                    break;
                dp1=dp1->next;
            }
            if(p1->zuowei==1)
                dp1->yz++;                 /*硬座余票加上1*/
            if(p1->zuowei==2)
                dp1->yw++;
            if(p1->zuowei==3)
                dp1->rw++;
            strcpy(head->num,num1);
            head->date=0;
            head->zuowei=0;
            if((fp=fopen("yonhu.dat","wb"))==NULL)
            {
                printf("无法打开");
                getch();
            }
            while(head!=NULL)
            {
                fwrite(head,sizeof(people),1,fp);
                head=head->next;
            }
            fclose(fp);


            if((fp=fopen("data.dat","wb"))==NULL)
            {
                printf("无法打开");
                getch();
            }
            while(dhead->next!=NULL)
            {
                fwrite(dhead,sizeof(data),1,fp);
                dhead=dhead->next;
            }
            fclose(fp);
            printf("退票成功");
        }
        else
            printf("已退出");
    }
    else
    {
        printf("账号或密码错误\n");
    }
}

