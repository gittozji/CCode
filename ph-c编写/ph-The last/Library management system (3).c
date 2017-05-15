/*图书馆管理系统*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define left 0x4b00
#define right 0x4d00
#define mm (ldata *)malloc(sizeof(ldata))
typedef struct data     /*定义结构体存放书籍信息*/
{
    char isbn[20];      /*ISBN码*/
    char bname[30];     /*书名*/
    char aname[20];     /*作者名*/
    char style[3];      /*ns(自然科学）ss(社会科学)*/
    char department[30];/*出版单位*/
    char time[11];      /*出版时间*/
    double money;       /*价格*/
    long int number;    /*发行数量*/
    struct data *next;  /*节点*/
}ldata;
void create();              /*书籍入库函数*/
void alter();               /*书籍信息修改函数*/
void delet();               /*书籍信息删除函数*/
void seek(int inlet);       /*书籍查找*/
void main()                 /*主函数*/
{
    FILE *fp;
    int ph1,ph2,ph3,ph4;
    char account[9],accountfb[12];    /*账号*/
    char choice;
    char c;                           /*用于密码输入*/
    int i;
    char password[7],passwordfb[7];   /*密码*/
    system( "graftabl 936");          /*显示中文*/
    system("cls");                    /*清屏*/
    gotoxy(20,15);
    printf("%c",14);                  /*起*/
    gotoxy(10,13);
    printf("%c",15);                  /*始*/
    gotoxy(30,17);
    printf("%c",3);                   /*界*/
    gotoxy(34,18);
    printf("欢迎使用！");             /*面*/
    gotoxy(15,19);
    printf("***************************************************");
    gotoxy(10,20);
    printf("**************************************************************\n");
    getch();
    do
    {
        ph4=0;        /*设置ph系列初始值为0，（下同）*/
        do            /*do-while语句用于返回上一界面功能,初衷为取代goto语句（下同）*/
        {
            ph1=0;
            system("cls");
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
            choice=getch();                               /*接收用户选择*/
            clrscr();
            if(choice=='1')                               /*进入VIP系统界面*/
            {
                if((fp=fopen("acco_pass.dat","rb"))==NULL)           /*打开存放VIP账号及密码的文件*/
                {
                    system("cls");
                    gotoxy(25,15);
                    printf(" 无法打开”acco_pass.dat“文件!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
                    exit(0);
                }
                fread(account,sizeof(account),1,fp);                 /*读取账号*/
                fread(password,sizeof(password),1,fp);               /*读取密码*/
                do
                {
                    system("CLS");
                    ph3=0;
                    gotoxy(29,6);
                    printf("登录数据管理系统");
                    gotoxy(21,8);
                    printf("*********************************");
                    gotoxy(21,18);
                    printf("*********************************");
                    gotoxy(30,10);
                    printf("请输入账号:\n");
                    gotoxy(30,12);
                    scanf("%s",accountfb);
                    gotoxy(30,14);
                    printf("请输入密码(6位字符):\n");
                    gotoxy(30,16);
                    for(i=0;i<6;i++)                       /*for语句完成输入密码功能*/
                    {
                        fflush(stdin);                     /*清空缓冲流（下同）*/
                        passwordfb[i]=getch();printf("*");
                    }
                    passwordfb[6]='\0';
                    if(strcmp(password,passwordfb)==0&&(strcmp(account,accountfb)==0))   /*账户，密码正确，进行if语句*/
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
                                case '1':                                /*进入图书入库函数*/
                                    clrscr();create();break;
                                case '2':                                /*进入图书删除函数*/
                                    clrscr();delet();break;
                                case '4':                                /*进入图书修改函数*/
                                    clrscr();alter();break;
                                case '5':
                                    ph1=1;break;                         /*进行do-while循环，返回上一界面*/
                                case '3':                                /*进入图书查找功能*/
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
                                        case '1':                      /*按书名查找*/
                                            clrscr();seek(1);break;
                                        case '2':                      /*按作者名查找*/
                                            clrscr();seek(2);break;
                                        case '4':                      /*按图书类型查找*/
                                            clrscr();seek(3);break;
                                        case '3':                      /*按出版社查找*/
                                            clrscr();seek(4);break;
                                        case '5':                      /*按ISBN码查找*/
                                            clrscr();seek(5);break;
                                        case '6':
                                            ph2=1;break;               /*返回上一界面*/
                                        default:break;
                                    }
                            }
                        }while(ph2==1);

                    }
                    else                                      /*密码或账号不匹配*/
                    {
                        system("CLS");
                        gotoxy(30,10);
                        printf("账号或密码输入错误");
                        gotoxy(30,12);
                        printf("1-重新输入账号密码");
                        gotoxy(30,14);
                        printf("其他键返回上一界面\n");
                        fflush(stdin);
                        c=getch();
                        if(c=='1')
                            ph3=1;
                        else
                            ph1=1;
                    }

                }while(ph3==1);
                if(fclose(fp))
                {                                           /*关闭文件*/
                    system("cls");
                    gotoxy(25,15);
                    printf(" 无法关闭”acco_pass.dat“文件!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
                    exit(0);
                }
            }
            else                                           /*普通人员进入*/
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
                        case '1':
                            clrscr();seek(1);break;
                        case '2':
                            clrscr();seek(2);break;
                        case '4':
                            clrscr();seek(4);break;
                        case '3':
                            clrscr();seek(3);break;
                        case '5':
                            clrscr();seek(5);break;
                        case '6':
                            ph1=1;break;
                        default:break;
                    }
                }
            }


        }while(ph1==1);
        system("CLS");
        gotoxy(23,9);
        printf("****************************");
        gotoxy(30,10);
        printf("1-返回起始页");
        gotoxy(30,12);
        printf("按其他键退出");
        gotoxy(23,13);
        printf("****************************\n");
        gotoxy(42,17);
        printf("         ---Ph\n");
        fflush(stdin);
        c=getch();
        if(c=='1')
            ph4=1;
    }while(ph4==1);
}
void create()  /*图书入库*/
{
    FILE *fp;
    ldata *head,*pm,*p1,*p2,*pc,*pls;
    char isbnfb[20];       /*ISBN码副本【副本为用户输入的信息（下同）】*/
    char bnamefb[30];     /*书名副本*/
    char anamefb[20];     /*作者名副本*/
    char stylefb[3];      /*ns(自然科学）ss(社会科学)副本*/
    char departmentfb[30];/*出版单位副本*/
    char timefb[11];      /*出版时间副本*/
    double moneyfb;       /*价格副本*/
    long int numberfb;    /*发行数量副本*/
    char ch;
    int ph1,cjbz,bcbz=0;
    char cc;
    if((fp=fopen("data.dat","ab+"))==NULL)             /*打开保存图书信息的文件*/
    {
        system("cls");
        gotoxy(25,15);
        printf(" 无法打开”data.dat“文件!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
        exit(0);
    }
    head=mm;                              /*其中mm为(ldata *)malloc(sizeof(ldata))*/
    p1=head;
    ch=fgetc(fp);                         /*接收文件第一个字符*/
    if(ch!=EOF)                           /*文件非空，进入if语句*/
    {
        rewind(fp);                       /*文件指针指向文件头*/
        fread(p1,sizeof(ldata),1,fp);     /*从文件读取一个结构体于p1*/
        pm=mm;                            /*pm接收申请到的结构体首地址*/
        p1->next=pm;                      /*将pm赋予p1->next*/
        p1=p1->next;                      /*p1指向p1->next*/
        while(!feof(fp))                  /*文件到尾时结束*/
        {
            fread(p1,sizeof(ldata),1,fp);
            pm=mm;
            p1->next=pm;
            p1=p1->next;
            pc=p1;                       /*pc指向新链表，用于存进文件*/
        }
    }
    else
    {
        pc=p1;
    }
    do
    {
        cjbz=1;
        ph1=0;
        system("CLS");
        printf("  请输入ISBN码:\n");scanf("%s",isbnfb);
        while(strlen(isbnfb)>19)          /*控制isbnfb长度不大于19(下同)*/
        {
            printf(" 输入的数据超出预设范围，请重新输入:\n");
            scanf("%s",isbnfb);
        }
        printf(" 请次输入图书类型（ns、ss）:\n");
        scanf("%s",stylefb);
        while(strlen(stylefb)>2)
        {
            printf(" 输入的数据超出预设范围，请重新输入:\n");
            scanf("%s",stylefb);
        }
        printf(" 请输入书名:\n");fflush(stdin);gets(bnamefb);
        while(strlen(bnamefb)>29)
        {
            printf(" 输入的数据超出预设范围，请重新输入:\n");
            fflush(stdin);
            gets(bnamefb);
        }
        printf(" 请输入作者名:\n");fflush(stdin);gets(anamefb);
        while(strlen(anamefb)>19)
        {
            printf(" 输入的数据超出预设范围，请重新输入:\n");
            fflush(stdin);
            gets(anamefb);
        }
        printf(" 请输入出版单位:\n");fflush(stdin);gets(departmentfb);
        while(strlen(departmentfb)>29)
        {
            printf(" 输入的数据超出预设范围，请重新输入:\n");
            fflush(stdin);
            gets(departmentfb);
        }
        printf(" 请输入出版时间:\n");fflush(stdin);gets(timefb);
        while(strlen(timefb)>10)
        {
            printf(" 输入的数据超出预设范围，请重新输入:\n");
            fflush(stdin);
            gets(timefb);
        }
        printf(" 请输入书籍价格:\n");
        scanf("%lf",&moneyfb);
        printf(" 请输入书籍发行量:\n");
        scanf("%ld",&numberfb);
        p2=head;
        while(p2!=p1)                          /*核对新书ISBN码是否已存在*/
        {
            if(!strcmp(p2->isbn,isbnfb))
            {
                cjbz=0;                        /*ISBN码已存在，令cjbz(创建标志)=0*/
                break;
            }
            p2=p2->next;
        }
        if(cjbz==1)                            /*cjbz==1，进行创建结构体*/
        {
            bcbz=1;                            /*创建了结构体，则令bcbz（保存标志）=1*/
            strcpy(p1->isbn,isbnfb);
            strcpy(p1->bname,bnamefb);
            strcpy(p1->aname,anamefb);
            strcpy(p1->style,stylefb);
            strcpy(p1->department,departmentfb);
            strcpy(p1->time,timefb);
            p1->money=moneyfb;
            p1->number=numberfb;
            pm=mm;
            p1->next=pm;
            pls=p1;
            p1=p1->next;
            printf("\n是否继续输入?y/n\n");
            fflush(stdin);
            cc=getch();
            if(cc=='y'||cc=='Y')
                ph1=1;                         /*ph系列=1，进行do-while循环*/

        }
        if(cjbz==0)
        {
            system("CLS");
            gotoxy(27,9);
            printf("___________________");
            gotoxy(27,13);
            printf("___________________");
            gotoxy(30,10);
            printf("ISBN:%s已存在");
            gotoxy(30,12);
            printf("是否继续输入Y/N\n");
            fflush(stdin);
            cc=getch();
            if(cc=='y'||cc=='Y')
                ph1=1;                         /*ph系列=1，进行do-while循环*/
        }
    }while(ph1==1);
    pls->next=NULL;
    if(bcbz==1)                               /*保存标志=1，进行保存进文件操作*/
    {
        gotoxy(30,10);
        printf("正在保存数据\n");
        while(pc!=NULL)                       /*将创建的链表追加进文件*/
        {
            fwrite(pc,sizeof(ldata),1,fp);
            pc=pc->next;

        }
         while(head!=NULL)                        /*释放链表内存*/
        {
            pc=head;
            head=head->next;
            free(pc);
        }

        system("CLS");

        if(fclose(fp))                            /*关闭文件*/
        {
            system("cls");
            gotoxy(25,15);
            printf(" 无法关闭”data.dat“文件!\n");
            gotoxy(17,14);
            printf("***************************************************");
            gotoxy(7,16);
            printf("***************************************************\n");
            getch();
            exit(0);
        }
        gotoxy(30,9);
        printf("______________");
        gotoxy(30,14);
        printf("______________");
        gotoxy(33,10);
        printf("保存成功");
        gotoxy(24,13);
        printf("        任意键退出\n");
        getch();
    }

}
void alter()               /*修改图书信息入口*/
{
    FILE *fp;
    char cc,realy;
    char bnamefb[30];
    char anamefb[20];
    char stylefb[3];
    char departmentfb[30];
    char timefb[11];
    double moneyfb;
    long int numberfb;
    char isbnfb[20];
    int judge=0,ph1,ph2,ph3,jixu;
    ldata *head,*p1,*pm,*pls,*pc;
    head=mm;
    p1=head;
    pc=head;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        system("cls");
        gotoxy(25,15);
        printf(" 无法打开”data.dat“文件!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
        exit(0);
    }
    fread(p1,sizeof(ldata),1,fp);
    pm=mm;
    p1->next=pm;
    p1=p1->next;
    while(!feof(fp))
    {
        fread(p1,sizeof(ldata),1,fp);
        pm=mm;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    if(fclose(fp))
    {
        system("cls");
        gotoxy(25,15);
        printf(" 无法关闭”data.dat“文件!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
        exit(0);
    }
    pls->next=NULL;
    do
    {
        jixu=0;
        ph2=0;
        ph1=0;
        system("CLS");
        gotoxy(25,10);
        printf("%c 请输入要修改图书的ISBN码 %c\n",14,14);
        gotoxy(24,13);
        printf("______________________________");
        gotoxy(35,12);
        fflush(stdin);
        gets(isbnfb);
        p1=head;
        while(p1!=NULL)
        {
            if(!(strcmp(p1->isbn,isbnfb)))
            {
                system("CLS");
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
                judge=1;                                    /*查找到信息，令judge=1以做标志*/
                printf("\n是否修改以上信息?(Y/N)\n");
                fflush(stdin);
                realy=getch();
                do
                {
                    ph3=0;
                    if(realy=='y'||realy=='Y')
                    {
                        system("CLS");
                        ph2=1;                          /*ph系列=1，标志进行do-while语句循环*/
                        gotoxy(1,1);
                        printf("  请输入ISBN码:\n");scanf("%s",isbnfb);
                        while(strlen(isbnfb)>19)
                        {
                            printf(" 输入的数据超出预设范围，请重新输入:\n");
                            scanf("%s",isbnfb);
                        }
                        printf(" 请次输入图书类型（ns、ss）:\n");
                        scanf("%s",stylefb);
                        while(strlen(stylefb)>2)
                        {   
                            printf(" 输入的数据超出预设范围，请重新输入:\n");
                            scanf("%s",stylefb);
                        }
                        printf(" 请输入书名:\n");fflush(stdin);gets(bnamefb);
                        while(strlen(bnamefb)>29)
                        {
                            printf(" 输入的数据超出预设范围，请重新输入:\n");
                            fflush(stdin);
                            gets(bnamefb);
                        }
                        printf(" 请输入作者名:\n");fflush(stdin);gets(anamefb);
                        while(strlen(anamefb)>19)
                        {
                            printf(" 输入的数据超出预设范围，请重新输入:\n");
                            fflush(stdin);
                            gets(anamefb);
                        }
                        printf(" 请输入出版单位:\n");fflush(stdin);gets(departmentfb);
                        while(strlen(departmentfb)>29)
                        {
                            printf(" 输入的数据超出预设范围，请重新输入:\n");
                            fflush(stdin);
                            gets(departmentfb);
                        }
                        printf(" 请输入出版时间:\n");fflush(stdin);gets(timefb);
                        while(strlen(timefb)>10)
                        {
                            printf(" 输入的数据超出预设范围，请重新输入:\n");
                            fflush(stdin);
                            gets(timefb);
                        }
                        printf(" 请输入书籍价格:\n");
                        scanf("%lf",&moneyfb);
                        printf(" 请输入书籍发行量:\n");
                        scanf("%ld",&numberfb);
                        while(pc!=NULL)
                        {
                            if(pc!=p1)
                            {
                                if(!strcmp(pc->isbn,isbnfb))
                                    jixu=1;                        /*若ISBN已存在，jixu=1*/
                            }
                            pc=pc->next;
                        }
                        if(jixu==0)                                /*ISBN不存在，可以创建结构体*/
                        {
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
                            system("CLS");
                            gotoxy(27,9);
                            printf("___________________");
                            gotoxy(27,13);
                            printf("___________________");
                            gotoxy(30,10);
                            printf("ISBN:%s已存在");
                            gotoxy(30,12);
                            printf("是否继续输入Y/N\n");
                            fflush(stdin);
                            cc=getch();
                            if(cc=='y'||cc=='Y')
                                ph3=1;
                        }
                    }
                    else
                    {
                        clrscr();
                        gotoxy(30,10);
                        printf("修改已取消!");
                        gotoxy(27,11);
                        printf("  *************");
                        fflush(stdin);
                        getch();
                    }


                }while(ph3==1);


            }
            p1=p1->next;

        }

        if(judge==1&&ph2==1)
        {
            gotoxy(20,30);
            printf("是否确定以上操作(Y/N)\n");
            fflush(stdin);
            realy=getch();
            if(realy=='Y'||realy=='y')
            {
                if((fp=fopen("data.dat","wb"))==NULL)
                {
                    system("cls");
                    gotoxy(25,15);
                    printf(" 无法打开”data.dat“文件!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
                    exit(0);
                }
                while(head!=NULL)
                {
                    fwrite(head,sizeof(ldata),1,fp);
                    head=head->next;
                }
                if(fclose(fp))
                {
                    system("cls");
                    gotoxy(25,15);
                    printf(" 无法关闭”data.dat“文件!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
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
            gotoxy(30,8);
            printf("未找到ISBN：%s",isbnfb);
            gotoxy(23,7);
            printf("****************************");
            gotoxy(30,10);
            printf("1-返回上一界面");
            gotoxy(30,12);
            printf("按其他键退出");
            gotoxy(23,13);
            printf("****************************\n");
            gotoxy(42,17);
            printf("         ---Ph\n");
            fflush(stdin);
            cc=getch();
            if(cc=='1')
                ph1=1;                             /*ph系列=1，标志进行do-while语句循环*/
        }
    }while(ph1==1);
    while(head!=NULL)                        /*释放链表内存*/
    {
        pc=head;
        head=head->next;
        free(pc);
    }
}
void delet()        /*删除图书信息功能入口*/
{
    FILE *fp;
    char isbnfb[20];
    char realy,cc;
    int ph1,ph2,zhao;
    ldata *head,*p1,*p2,*pm,*pls;
    head=mm;
    p1=head;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        system("cls");
        gotoxy(25,15);
        printf(" 无法打开”data.dat“文件!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
        exit(0);
    }
    fread(p1,sizeof(ldata),1,fp);
    pm=mm;
    p1->next=pm;
    p1=p1->next;
    while(!feof(fp))
    {
        fread(p1,sizeof(ldata),1,fp);
        pm=mm;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    pls->next=NULL;
    if(fclose(fp))
    {
        system("cls");
        gotoxy(25,15);
        printf(" 无法关闭”data.dat“文件!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
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
            gotoxy(80,12);printf("|\n");
            printf("是否永久删除以上书籍信息?(Y/N)\n");
            fflush(stdin);
            realy=getch();
            if(realy=='y'||realy=='Y')
            {
                if((fp=fopen("data.dat","wb"))==NULL)
                {
                    system("cls");
                    gotoxy(25,15);
                    printf(" 无法打开”data.dat“文件!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
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
                    system("cls");
                    gotoxy(25,15);
                    printf(" 无法关闭”data.dat“文件!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
                    exit(0);
                }
                system("CLS");
                gotoxy(30,10);
                printf("删除成功!");
                fflush(stdin);
                getch();
            }
            system("CLS");
            gotoxy(23,9);
            printf("____________________________");
            gotoxy(30,10);
            printf(" 1-重新输入");
            gotoxy(30,12);
            printf(" 按其他键退出");
            gotoxy(23,13);
            printf("____________________________\n");
            gotoxy(42,17);
            printf("         ---Ph\n");
            fflush(stdin);
            cc=getch();
            if(cc=='1')
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
                    gotoxy(80,12);printf("|\n");
                    printf("是否永久删除以上书籍信息?(Y/N)\n");
                    fflush(stdin);
                    realy=getch();
                    if(realy=='y'||realy=='Y')
                    {   
                        if((fp=fopen("data.dat","wb"))==NULL)
                        {
                            system("cls");
                            gotoxy(25,15);
                            printf(" 无法打开”data.dat“文件!\n");
                            gotoxy(17,14);
                            printf("***************************************************");
                            gotoxy(7,16);
                            printf("***************************************************\n");
                            getch();
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
                            system("cls");
                            gotoxy(25,15);
                            printf(" 无法关闭”data.dat“文件!\n");
                            gotoxy(17,14);
                            printf("***************************************************");
                            gotoxy(7,16);
                            printf("***************************************************\n");
                            getch();
                            exit(0);
                        }
                        system("CLS");
                        gotoxy(30,10);
                        printf("删除成功!");
                        fflush(stdin);
                        getch();
                    }
                    system("CLS");
                    gotoxy(30,12);
                    printf("1-返回上一界面");
                    gotoxy(30,14);
                    printf("按其他键退出");
                    fflush(stdin);
                    cc=getch();
                    if(cc=='1')
                        ph1=1;
                }
                p1=p1->next;                                  /*未找到,p1、p2指向下一地址*/
                p2=p1->next;
            }
            if(ph2==0)
            {
                system("CLS");
                gotoxy(30,8);
                printf("未找到ISBN：%s",isbnfb);
                gotoxy(23,7);
                printf("****************************");
                gotoxy(30,10);
                printf("1-重新输入");
                gotoxy(30,12);
                printf("按其他键退出");
                gotoxy(23,13);
                printf("****************************\n");
                gotoxy(42,17);
                printf("         ---Ph\n");
                fflush(stdin);
                cc=getch();
                if(cc=='1')
                    ph1=1;
            }
        }
    }while(ph1==1);
    while(head!=NULL)                        /*释放链表内存*/
    {
        p1=head;
        head=head->next;
        free(p1);
    }
}
void seek(int inlet)
{
    FILE *fp;
    char isbnfb[20];      /*ISBN码副本*/
    char bnamefb[30];     /*书名副本*/
    char anamefb[20];     /*作者名副本*/
    char stylefb[3];      /*ns(自然科学）ss(社会科学)副本*/
    char departmentfb[30];/*出版单位副本*/
    char timefb[11];      /*出版时间副本*/
    double moneyfb;       /*价格副本*/
    long int numberfb;    /*发行数量副本*/
    char cc; char ch;
    int outlet,key;
    int judge,ph1,i,ii,s1,leftfb,jie,chukou;
    ldata *head,*p1,*pm,*save[20],*pq,*pls;
    head=mm;
    p1=head;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        system("cls");
        gotoxy(25,15);
        printf(" 无法打开”data.dat“文件!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
        exit(0);
    }
    fread(p1,sizeof(ldata),1,fp);
    pm=mm;
    p1->next=pm;
    p1=p1->next;
    while(!feof(fp))
    {
        fread(p1,sizeof(ldata),1,fp);
        pm=mm;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    pls->next=NULL;
    if(fclose(fp))
    {
        system("cls");
        gotoxy(25,15);
        printf(" 无法关闭”data.dat“文件!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
        exit(0);
    }


    do
    {
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
            printf("请输入要查找图书的类型（ss-社会科学、ns-自然科学）\n");
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
                p1=save[s1];              /*保存一页的书籍信息*/
                leftfb=0;                 /*充当钥匙作用，为1进行保存，为0，不进行*/
                system("CLS");
            }

            if(inlet==1)
                if(strstr(p1->bname,bnamefb)==NULL)
                    outlet=1;
                else
                    outlet=0;
            if(inlet==2)
                if(strstr(p1->aname,anamefb)==NULL)
                    outlet=1;
                else
                    outlet=0;
            if(inlet==3)
                if(strstr(p1->style,stylefb)==NULL)
                    outlet=1;
                else
                    outlet=0;
            if(inlet==4)
                if(strstr(p1->department,departmentfb)==NULL)
                    outlet=1;
                else
                    outlet=0;


            if(!outlet)
            {
                chukou=1;
                judge=1;
                if(ii==0&&s1>=0&&jie==0)         /*jie充当钥匙功能，为0时才有权进入if*/
                                                 /*从而将信息保存给save*/
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
                ii++;                  /*记录一页的书籍数目，最大值为6*/
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
                            s1=0;
                        i=1;
                        leftfb=1;
                    }
                    if(key==right)
                    {
                        ii=0;
                        i=1;
                        s1++;
                        if(s1>19)
                            s1=0;
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
            gotoxy(30,8);
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
            gotoxy(23,7);
            printf("****************************");
            gotoxy(30,10);
            printf("1-重新输入");
            gotoxy(30,12);
            printf("按其他键退出");
            gotoxy(23,13);
            printf("****************************\n");
            gotoxy(42,17);
            printf("         ---Ph\n");
            fflush(stdin);
            cc=getch();
            if(cc=='1')
            ph1=1;                                                     /*ph系列=1，标志进行do-while语句循环*/
        }
    }while(ph1==1);
    while(head!=NULL)                        /*释放链表内存*/
    {
        p1=head;
        head=head->next;
        free(p1);
    }

}

