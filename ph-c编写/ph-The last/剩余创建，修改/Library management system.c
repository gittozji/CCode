/*图书馆管理系统*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define left 0x4b00
#define right 0x4d00
#define mm malloc(sizeof(ldata))
typedef struct data     /*定义结构体存放书籍信息*/
{
    char isbn[20];      /*ISBN码*/
    char bname[30];     /*书名*/
    char aname[20];     /*作者名*/
    char style[3];      /*ns(自然科学）ss(社会科学)*/
    char department[20];/*出版单位*/
    char time[11];      /*出版时间*/
    double money;       /*价格*/
    long int number;    /*发行数量*/
    struct data *next;  /*节点*/
}ldata;
void create();    /*书籍入库函数*/
void alter();     /*书籍信息修改函数*/
void delet();     /*书籍信息删除函数*/
void seek(int inlet);      /*书籍查找*/
int fuzzy(char *a,char *b);  /*模糊查询入口函数*/
void main()                  /*主函数*/
{
    FILE *fp;
    int ph1,ph2,ph3,phi;
    char account[9],accountfb[12];  /*账号*/
    char choice;
    char c;
    int inclec,i;                     /*1-书名，2-作者名，3-类型，4-出版社，5-ISBN吗*/
    char password[7],passwordfb[7]; /*密码*/
    system( "graftabl 936");        /*显示中文*/
    do
    {
        phi=0;
        do           /*do-while语句用于返回上一界面功能,初衷为取代goto语句（下同）*/
        {
            ph1=0;                      /*ph1=1为退出do-while语句条件*/
            clrscr();
            gotoxy(29,7);
            printf("       欢迎使用");
            gotoxy(27,8);
            printf("**************************");         /*初*/
            gotoxy(30,10);
            printf("1-选择 VIP 账户登录");                /*始*/
            gotoxy(30,13);
            printf("2-选择普通账账户登录");               /*界*/
            gotoxy(30,16);
            printf("按其他键退出此询系统");               /*面*/
            gotoxy(27,19);
            printf("**************************\n");
            gotoxy(26,23);
            printf("版权属ph，盗版不究，放心使用\n");
            choice=getch();
            clrscr();
            if(choice=='1')
            {
                if((fp=fopen("acco_pass.dat","rb"))==NULL)            /*打开存放着VIP账号及密码的文件*/
                {
                    printf(" 无法打开”acco_pass.dat“文件\n");
                    getch();
                    exit(0);
                }
                fread(account,sizeof(account),1,fp);
                fread(password,sizeof(password),1,fp);
                do
                {
                    system("CLS");
                    ph3=0;
                    gotoxy(30,10);                                            /*登*/
                    printf("请输入账号:\n");                                  /*陆*/
                    gotoxy(30,12);                                            /*界*/
                    scanf("%s",accountfb);                                    /*面*/
                    gotoxy(30,14);
                    printf("请输入密码(6位字符):\n");
                    gotoxy(30,16);
                    for(i=0;i<6;i++)
                    {
                        fflush(stdin);
                        passwordfb[i]=getch();printf("*");
                    }
                    passwordfb[6]='\0';
                    if(strcmp(password,passwordfb)==0&&(strcmp(account,accountfb)==0))
                    {
                        do
                        {
                            ph2=0;
                            clrscr();
                            gotoxy(35,10);
                            printf("请选择");
                            gotoxy(14,12);
                            printf("****************************************************");
                            gotoxy(22,14);
                            printf("1-图书入库           2-删除书籍");
                            gotoxy(22,16);
                            printf("3-查找图书           4-修改书籍");
                            gotoxy(22,18);
                            printf("5-返回上一界面       其他键退出");
                            gotoxy(14,20);
                            printf("****************************************************\n");
                            c=getch();
                            switch(c)
                            {
                                case '1':clrscr();create();break;
                                case '2':clrscr();delet();break;
                                case '4':clrscr();alter();break;
                                case '5':ph1=1;break;                        /*ph系列=1，标志进行do-while语句循环*/
                                case '3':clrscr();
                                        gotoxy(35,10);
                                        printf("请选择");
                                        gotoxy(14,12);
                                        printf("****************************************************");
                                        gotoxy(22,14);
                                        printf("1-按书名查找           2-按作者名查找");
                                        gotoxy(22,16);
                                        printf("3-按类别查找           4-按出版社查找");
                                        gotoxy(22,18);
                                        printf("5-按ISBN码查找         6-返回上一界面");
                                        gotoxy(22,20);
                                        printf("7-按其他键退出");
                                        gotoxy(14,22);
                                        printf("****************************************************\n");
                                        c=getch();
                                        switch(c)
                                        {  
                                            case '1':clrscr();seek(1);break;
                                            case '2':clrscr();seek(2);break;
                                            case '4':clrscr();seek(3);break;
                                            case '3':clrscr();seek(4);break;
                                            case '5':clrscr();seek(5);break;
                                            case '6':ph2=1;break;              /*ph系列=1，标志进行do-while语句循环*/
                                            default:break;
                                        }
                            }
                        }while(ph2==1);

                    }
                    else
                    {
                        system("CLS");
                        gotoxy(30,10);
                        printf("账号或密码输入错误");
                        gotoxy(30,12);
                        printf("c-重新输入账号密码");
                        gotoxy(30,14);
                        printf("其他键返回上一界面\n");
                        fflush(stdin);
                        c=getch();
                        if(c=='c')
                            ph3=1;
                        else
                            ph1=1;
                    }

                }while(ph3==1);
                if(fclose(fp))
                {
                    printf(" 无法关闭”acco_pass.dat“文件\n");
                    exit(0);
                }
            }
            else
            {
                if(choice=='2')
                {
                    clrscr();
                    gotoxy(35,10);
                    printf("请选择");
                    gotoxy(14,12);
                    printf("****************************************************");
                    gotoxy(22,14);
                    printf("1-按书名查找           2-按作者名查找");
                    gotoxy(22,16);
                    printf("3-按类别查找           4-按出版社查找");
                    gotoxy(22,18);
                    printf("5-按ISBN码查找         6-返回上一界面");
                    gotoxy(22,20);
                    printf("7-按其他键退出");
                    gotoxy(14,22);
                    printf("****************************************************\n");
                    c=getch();
                    switch(c)
                    {
                        case '1':clrscr();seek(1);break;
                        case '2':clrscr();seek(2);break;
                        case '4':clrscr();seek(4);break;
                        case '3':clrscr();seek(3);break;
                        case '5':clrscr();seek(5);break;
                        case '6':ph1=1;break;
                        default:break;
                    }
                }
            }


        }while(ph1==1);
        system("CLS");
        gotoxy(30,10);
        printf("c-返回起始页");
        gotoxy(30,12);
        printf("按其他键退出");
        fflush(stdin);
        c=getch();
        if(c=='c')
            phi=1;
    }while(phi==1);
}
void create()  /*图书入库*/
{
    FILE *fp;
    ldata *head,*p,*p1;
    char c='y';
    char cc;
    char isbnfb[20];      /*ISBN码副本*/
    char bnamefb[30];     /*书名副本*/
    char anamefb[20];     /*作者名副本*/
    char stylefb[3];      /*ns(自然科学）ss(社会科学)副本*/
    char departmentfb[20];/*出版单位副本*/
    char timefb[11];      /*出版时间副本*/
    double moneyfb;       /*价格副本*/
    long int numberfb;    /*发行数量副本*/
    if((fp=fopen("data.dat","ab"))==NULL)
    {
        printf("无法打开“data.dat”文件");
        exit(0);
    }
    head=mm;
    p=head;
    printf(" 请依次输入ISBN码、图书类型（ns、ss）、价格、发行量:\n");
    scanf("%s%s%lf%ld",isbnfb,stylefb,&moneyfb,&numberfb);
    printf(" 请输入书名:\n");fflush(stdin);gets(bnamefb);
    printf(" 请输入作者名:\n");fflush(stdin);gets(anamefb);
    printf(" 请输入出版单位:\n");fflush(stdin);gets(departmentfb);
    printf(" 请输入出版时间:\n");fflush(stdin);gets(timefb);

    while(c=='y')                /*继续输入信息*/
    {
        strcpy(p->isbn,isbnfb);
        strcpy(p->bname,bnamefb);
        strcpy(p->aname,anamefb);
        strcpy(p->style,stylefb);
        strcpy(p->department,departmentfb);
        strcpy(p->time,timefb);
        p->money=moneyfb;
        p->number=numberfb;

        printf("\n是否继续输入？y/n\n");
        fflush(stdin);
        c=getch();
        if(c=='y')
        {
            p1=mm;
            p->next=p1;
            p=p->next;
            printf("\n请依次输入ISBN码、图书类型（ns、ss）、价格、发行量:\n");
            scanf("%s%s%lf%ld",isbnfb,stylefb,&moneyfb,&numberfb);
            printf(" 请输入书名:\n");fflush(stdin);gets(bnamefb);
            printf(" 请输入作者名:\n");fflush(stdin);gets(anamefb);
            printf(" 请输入出版单位:\n");fflush(stdin);gets(departmentfb);
            printf(" 请输入出版时间:\n");fflush(stdin);gets(timefb);
        }
    }
    p->next=NULL;
    while(head!=NULL)
    {
        fwrite(head,sizeof(ldata),1,fp);
        p=head;
        head=head->next;
        free(p);
    }
    system("CLS");           /*清屏函数*/

    if(fclose(fp))
        {
            printf(" 无法关闭”acco_pass.dat“文件\n");
            exit(0);  
        }
    gotoxy(33,10);
    printf("保存成功");
    gotoxy(24,13);
    printf("        任意键退出\n");
    getch();
}
void alter()               /*修改图书信息入口*/
{
    FILE *fp;
    char cc,realy;
    char bnamefb[30];
    char anamefb[20];
    char stylefb[3];
    char departmentfb[20];
    char timefb[11];
    double moneyfb;
    long int numberfb;
    char isbnfb[20];
    int judge=0,ph1,ph2;
    ldata *head,*p1,*pm;
    head=mm;
    p1=head;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开“data.dat”文件");
        exit(0);
    }

    while(!feof(fp))
    {
        fread(p1,sizeof(ldata),1,fp);
        pm=mm;
        p1->next=pm;
        p1=p1->next;
    }
    if(fclose(fp))
    {
        printf(" 无法关闭”data.dat“文件\n");
        exit(0);
    }
    p1=NULL;
    do
    {
        ph2=0;
        ph1=0;
        system("CLS");
        gotoxy(30,10);
        printf(" 请输入要修改图书的ISBN码\n");
        fflush(stdin);
        gets(isbnfb);
        p1=head;
        while(p1!=NULL)
        {
            if(!(strcmp(p1->isbn,isbnfb)))
            {
                system("CLS");
                printf("\n\n\n\n\n\n");
                printf("                      %c ISBN为%s的图书信息如下 %c\n",14,head->isbn,14);printf("--------------------------------------------------------------------------------");
                printf("|     ISBN     |              书名               |        作者名       |  分类 |\n|     价格     |           出版单位              |       出版时间      |  数量 |\n");
                printf("--------------------------------------------------------------------------------");
                gotoxy(1,10);printf("|%s",p1->isbn);
                gotoxy(16,10);printf("| %s",p1->bname);
                gotoxy(50,10);printf("| %s",p1->aname);
                gotoxy(72,10);printf("|   %s  |",p1->style);
                gotoxy(1,12);printf("|%.2lf",p1->money);
                gotoxy(16,12);printf("| %s",p1->department);
                gotoxy(50,12);printf("|      %s",p1->time);
                gotoxy(72,12);printf("| %ld",p1->number);
                gotoxy(80,12);printf("|");
                judge=1;
                printf("\n是否修改以上信息?(Y/N)\n");
                fflush(stdin);
                realy=getch();
                if(realy=='y'||realy=='Y')
                {
                    system("CLS");
                    ph2=1;                          /*ph系列=1，标志进行do-while语句循环*/
                    gotoxy(1,1);
                    printf(" 请依次输入ISBN码、图书类型（ns、ss）、价格、发行量:\n");
                    scanf("%s%s%lf%ld",isbnfb,stylefb,&moneyfb,&numberfb);
                    printf(" 请输入书名:\n");fflush(stdin);gets(bnamefb);
                    printf(" 请输入作者名:\n");fflush(stdin);gets(anamefb);
                    printf(" 请输入出版单位:\n");fflush(stdin);gets(departmentfb);
                    printf(" 请输入出版时间:\n");fflush(stdin);gets(timefb);
                    strcpy(p1->isbn,isbnfb);
                    strcpy(p1->bname,bnamefb);
                    strcpy(p1->aname,anamefb);
                    strcpy(p1->style,stylefb);
                    strcpy(p1->department,departmentfb);
                    strcpy(p1->time,timefb);
                    p1->money=moneyfb;
                    p1->number=numberfb;
                    fflush(stdin);
                    break;
                }
                else
                {
                    clrscr();
                    gotoxy(30,10);
                    printf("修改已取消!");
                    fflush(stdin);
                    getch();
                }
            }
            p1=p1->next;

        }

        if(judge==1&&ph2==1)
        {
            gotoxy(20,30);
            printf("是否确定修改(Y/N)\n");
            fflush(stdin);
            realy=getch();
            if(realy=='Y'||realy=='y')
            {
                if((fp=fopen("data.dat","wb"))==NULL)
                {
                    printf("无法打开“data.dat”文件");
                    exit(0);
                }
                while(head!=NULL)
                {
                    fwrite(head,sizeof(ldata),1,fp);
                    head=head->next;
                }
                if(fclose(fp))
                {
                printf(" 无法关闭”data.dat“文件\n");
                exit(0);
                }
                clrscr();
                gotoxy(30,10);
                printf("修改成功!");
                fflush(stdin);
                getch();
            }
            else
            {
                clrscr();
                gotoxy(30,10);
                printf("修改已取消!");
                fflush(stdin);
                getch();
            }
        }
        if(judge==0)
        {
            system("CLS");
            gotoxy(30,10);
            printf("未找到ISBN：%s",isbnfb);
            gotoxy(30,12);
            printf("c-返回上一界面");
            gotoxy(30,14);
            printf("按其他键退出");
            fflush(stdin);
            cc=getch();
            if(cc=='c')
                ph1=1;                             /*ph系列=1，标志进行do-while语句循环*/
        }
    }while(ph1==1);
}
void delet()        /*删除图书信息功能入口*/
{
    FILE *fp;
    char isbnfb[20];
    char realy,cc;
    int ph1,ph2,zhao;
    ldata *head,*p1,*p2,*pm;
    head=mm;
    p1=head;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开“data.dat”文件");
        exit(0);
    }

    while(!feof(fp))
    {
        fread(p1,sizeof(ldata),1,fp);
        pm=mm;
        p1->next=pm;
        p1=p1->next;
    }
    p1=NULL;
    if(fclose(fp))
    {
        printf(" 无法关闭”data.dat“文件\n");
        exit(0);
    }
    do
    {
        ph2=0;                                 /*ph2=1时,在链表中找到，为0时,说明没找到*/
        zhao=0;                                /*zhao=1时，说明所找信息为在链表头*/
        ph1=0;
        clrscr();
        gotoxy(30,10);
        printf(" 请输入要查找图书的ISBN码\n");
        fflush(stdin);
        gets(isbnfb);
        if(head!=NULL&&(!strcmp(head->isbn,isbnfb)))
        {
            ph2=1;
            zhao=1;
            system("CLS");
            printf("\n\n\n\n\n\n");
            printf("                      %c ISBN为%s的图书信息如下 %c\n",14,head->isbn,14);printf("--------------------------------------------------------------------------------");
            printf("|     ISBN     |              书名               |        作者名       |  分类 |\n|     价格     |           出版单位              |       出版时间      |  数量 |\n");
            printf("--------------------------------------------------------------------------------");
            gotoxy(1,10);printf("|%s",head->isbn);
            gotoxy(16,10);printf("| %s",head->bname);
            gotoxy(50,10);printf("| %s",head->aname);
            gotoxy(72,10);printf("|   %s  |",head->style);
            gotoxy(1,12);printf("|%.2lf",head->money);
            gotoxy(16,12);printf("| %s",head->department);
            gotoxy(50,12);printf("|      %s",head->time);
            gotoxy(72,12);printf("| %ld",head->number);
            gotoxy(80,12);printf("|");
            fflush(stdin);
            getch();
            gotoxy(25,15);
            printf("是否永久删除以上书籍信息?(Y/N)\n");
            fflush(stdin);
            realy=getch();
            if(realy=='y'||realy=='Y')
            {
                if((fp=fopen("data.dat","wb"))==NULL)
                {
                    printf("无法打开“data.dat”文件");
                    exit(0);
                }
                p1=head;
                head=head->next;
                free(p1);
                p1=head;
                while(p1!=NULL)
                {
                    fwrite(p1,sizeof(ldata),1,fp);
                    p1=p1->next;
                }
                if(fclose(fp))
                {
                    system("CLS");
                    printf(" 无法关闭”data.dat“文件\n");
                    exit(0);
                    printf("系统已出错！");
                    fflush(stdin);
                    getch();
                }
                system("CLS");
                gotoxy(30,10);
                printf("删除成功!");
                fflush(stdin);
                getch();
            }
            system("CLS");
            gotoxy(30,12);
            printf("c-返回上一界面");
            gotoxy(30,14);
            printf("按其他键退出");
            fflush(stdin);
            cc=getch();
            if(cc=='c')
                ph1=1;
        }
        if(zhao==0)
        {
            p1=head;
            p2=p1->next;
            while(p2!=NULL)
            {
                if(!strcmp(p2->isbn,isbnfb))
                {
                    ph2=1;
                    system("CLS");
                    printf("\n\n\n\n\n\n");
                    printf("                      %c ISBN为%s的图书信息如下 %c\n",14,p2->isbn,14);printf("--------------------------------------------------------------------------------");
                    printf("|     ISBN     |              书名               |        作者名       |  分类 |\n|     价格     |           出版单位              |       出版时间      |  数量 |\n");
                    printf("--------------------------------------------------------------------------------");
                    gotoxy(1,10);printf("|%s",p2->isbn);
                    gotoxy(16,10);printf("| %s",p2->bname);
                    gotoxy(50,10);printf("| %s",p2->aname);
                    gotoxy(72,10);printf("|   %s  |",p2->style);
                    gotoxy(1,12);printf("|%.2lf",p2->money);
                    gotoxy(16,12);printf("| %s",p2->department);
                    gotoxy(50,12);printf("|      %s",p2->time);
                    gotoxy(72,12);printf("| %ld",p2->number);
                    gotoxy(80,12);printf("|");
                    fflush(stdin);
                    getch();
                    gotoxy(25,15);
                    printf("是否永久删除以上书籍信息?(Y/N)\n");
                    fflush(stdin);
                    realy=getch();
                    if(realy=='y'||realy=='Y')
                    {   
                        if((fp=fopen("data.dat","wb"))==NULL)
                        {
                            printf("无法打开“data.dat”文件");
                            exit(0);
                        }
                        p1->next=p2->next;
                        p1=head;
                        while(p1!=NULL)
                        {   
                            fwrite(p1,sizeof(ldata),1,fp);
                            p1=p1->next;
                        }
                        if(fclose(fp))
                        {
                            system("CLS");
                            printf(" 无法关闭”data.dat“文件\n");
                            exit(0);
                            printf("系统已出错！");
                            fflush(stdin);
                            getch();
                        }
                        system("CLS");
                        gotoxy(30,10);
                        printf("删除成功!");
                        fflush(stdin);
                        getch();
                    }
                    system("CLS");
                    gotoxy(30,12);
                    printf("c-返回上一界面");
                    gotoxy(30,14);
                    printf("按其他键退出");
                    fflush(stdin);
                    cc=getch();
                    if(cc=='c')
                        ph1=1;
                }
                p1=p1->next;
                p2=p1->next;
            }
            if(ph2==0)
            {
                system("CLS");
                gotoxy(30,10);
                printf("未找到ISBN：%s",isbnfb);
                gotoxy(30,12);
                printf("c-返回上一界面");
                gotoxy(30,14);
                printf("按其他键退出");
                fflush(stdin);
                cc=getch();
                if(cc=='c')
                    ph1=1;
            }
        }
    }while(ph1==1);
}
void seek(int inlet)       /*按ISBN码查询入口*/
{
    FILE *fp;
    char isbnfb[20];      /*ISBN码副本*/
    char bnamefb[30];     /*书名副本*/
    char anamefb[20];     /*作者名副本*/
    char stylefb[3];      /*ns(自然科学）ss(社会科学)副本*/
    char departmentfb[20];/*出版单位副本*/
    char timefb[11];      /*出版时间副本*/
    double moneyfb;       /*价格副本*/
    long int numberfb;    /*发行数量副本*/
    char cc;
    int outlet,key;
    int judge,ph1,i,ii,s1,leftfb,jie,chukou;
    ldata *head,*p1,*pm,*save[10];
    head=mm;
    p1=head;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("无法打开“data.dat”文件");
        exit(0);
    }

    while(!feof(fp))
    {
        fread(p1,sizeof(ldata),1,fp);
        pm=mm;
        p1->next=pm;
        p1=p1->next;
    }
    p1=NULL;
    if(fclose(fp))
    {
        printf(" 无法关闭”data.dat“文件\n");
        exit(0);
    }


    do{
        chukou=0;
        leftfb=0;
        s1=0;
        ii=0;
        jie=0;
        outlet=1;
        i=1;
        p1=head;
        ph1=0;
        judge=0;
        clrscr();
        gotoxy(30,10);
        if(inlet==5)
        {
            printf("请输入要查找图书的ISBN码\n");
            fflush(stdin);
            gets(isbnfb);
        }
        if(inlet==1)
        {
            printf("请输入要查找图书的名字\n");
            fflush(stdin);
            gets(bnamefb);   
        }
        if(inlet==2)
        {
            printf("请输入要查找的作者名\n");
            fflush(stdin);
            gets(anamefb);
        }
        if(inlet==3)
        {
            gotoxy(17,10);
            printf("请输入要查找图书的类型（ss-社会科学、ns-自热科学）\n");
            fflush(stdin);
            gets(stylefb);
        }
        if(inlet==4)
        {
            printf("请输入要查找的出版单位\n");
            fflush(stdin);
            gets(departmentfb);
        }
        clrscr();
        while(p1!=NULL)
        {
            if(inlet==5)
            if(!strcmp(p1->isbn,isbnfb))     /*输出信息*/
            {
                chukou=1;
                printf("\n\n\n\n\n\n");
                printf("                      %c ISBN为%s的图书信息如下 %c\n",14,p1->isbn,14);printf("--------------------------------------------------------------------------------");
                printf("|     ISBN     |              书名               |        作者名       |  分类 |\n|     价格     |           出版单位              |       出版时间      |  数量 |\n");
                printf("--------------------------------------------------------------------------------");
                gotoxy(1,10);printf("|%s",p1->isbn);
                gotoxy(16,10);printf("| %s",p1->bname);
                gotoxy(50,10);printf("| %s",p1->aname);
                gotoxy(72,10);printf("|   %s  |",p1->style);
                gotoxy(1,12);printf("|%.2lf",p1->money);
                gotoxy(16,12);printf("| %s",p1->department);
                gotoxy(50,12);printf("|      %s",p1->time);
                gotoxy(72,12);printf("| %ld",p1->number);
                gotoxy(80,12);printf("|");
                judge=1;
                fflush(stdin);
                getch();
                break;
            }

            if(leftfb==1)
            {
                p1=save[s1];
                leftfb=0;
                system("CLS");
            }
            if(inlet==1)
                outlet=strcmp(p1->bname,bnamefb);
            if(inlet==2)
                outlet=strcmp(p1->aname,anamefb);
            if(inlet==3)
                outlet=strcmp(p1->style,stylefb);
            if(inlet==4)
                outlet=strcmp(p1->department,departmentfb);


            if(!outlet)
            {
                chukou=1;
                judge=1;
                if(ii==0&&s1>=0&&jie==0)
                {
                    save[s1]=p1;
                    jie=1;
                }
                gotoxy(1,i);printf("|ISBN:%s",p1->isbn);
                gotoxy(40,i);printf("|书名:%s",p1->bname);
                gotoxy(1,i+1);printf("|作者名:%s",p1->aname);
                gotoxy(1,i+2);printf("|类型:%s",p1->style);
                gotoxy(40,i+2);printf("|价格:%.2lf",p1->money);
                gotoxy(40,i+1);printf("|出版单位:%s",p1->department);
                gotoxy(18,i+2);printf("|出版时间:%s",p1->time);
                gotoxy(60,i+2);printf("|发行数量:%ld",p1->number);
                gotoxy(1,i+3);
                printf("--------------------------------------------------------------------------------");
                judge=1;
                i+=4;
                ii++;
                if(ii==6)
                {

                    printf("操作“<-”、“->”进行翻页");
                    key=bioskey(0);
                    system("CLS");

                    if(key==left)
                    {
                        ii=0;
                        s1--;
                        if(s1<0)
                            s1=1;
                        i=1;
                        leftfb=1;
                    }
                    if(key==right)
                    {
                        ii=0;
                        i=1;
                        s1++;
                        if(s1>9)
                            s1=9;
                        leftfb=0;
                        jie=0;
                    }
                }

            }
            if(p1->next->next==NULL)
            {
                if(chukou==0);
                else
                {
                    key=bioskey(0);
                    if(key==left)
                    {
                        ii=0;
                        s1--;
                        if(s1<0)
                            s1=0;
                        i=1;
                        leftfb=1;
                    }
                    if(key==right)
                    {
                        printf(" 已是最后一页\n\n");
                        printf(" 按“<-”返回上一页，按“->”继续\n\n");
                        key=bioskey(0);
                        if(key==left)
                        {
                            ii=0;
                            s1--;
                            if(s1<0)
                                s1=0;
                            i=1;
                            leftfb=1;

                        }
                    }
                }
            }
            p1=p1->next;
        }
        if(judge==1)
        {
            system("CLS");
            gotoxy(30,10);
            printf("是否继续查找?(Y/N)\n");
            fflush(stdin);
            cc=getch();
            if(cc=='y'||cc=='Y')
                ph1=1;                                         /*ph系列=1，标志进行do-while语句循环*/
        }

        if(judge==0)
        {
            gotoxy(30,10);
            if(inlet==5)
                printf("未找到ISBN：%s\n",isbnfb);
            if(inlet==1)
                printf("未找到书名：%s\n",bnamefb);
            if(inlet==2)
                printf("未找到作者：\n",anamefb);
            if(inlet==3)
                printf("未找到类型：\n",stylefb);
            if(inlet==4)
                printf("未找到出版社：\n",departmentfb);
            gotoxy(30,12);
            printf("c-重新输入           \n\n                             按任其他键退出\n");
            fflush(stdin);
            cc=getch();
            if(cc=='c')
            ph1=1;                                                     /*ph系列=1，标志进行do-while语句循环*/
        }
        }while(ph1==1);
}

