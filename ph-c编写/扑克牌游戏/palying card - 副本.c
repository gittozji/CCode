/*扑克牌游戏*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct user
{
    char name[20];
    char password[20];
    int money;
    int rank;
}user;
void lonin(user* apply);
void sign();
void enter();
void main()
{
    user *apply;
    char choice;
    apply=(user *)malloc(sizeof(user));
    system("graftabl 936");
    system("cls");
    gotoxy(31,7);
    printf("扑克牌游戏软件");
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
    system("cls");
    gotoxy(27,8);
    printf(" *************************");     /*初*/
    gotoxy(30,10);
    printf("     1-登陆账号");                /*始*/
    gotoxy(30,13);
    printf("     2-注册账号");                /*界*/
    gotoxy(30,16);
    printf("     3-退出游戏");                /*面*/
    gotoxy(27,19);
    printf(" *************************\n");
    gotoxy(26,23);
    printf("版权属ph，盗版不究，放心使用\n");
    choice=getch();                               /*接收用户选择*/
    switch(choice)
    {
        case '1':
            system("cls");
            lonin(apply);
            printf(" 是否进入游戏？(y/n)\n");
            fflush(stdin);
            choice=getch();
            if(choice=='y')
                enter();
            break;
        case '2':
            system("cls");sign();break;
        default:break;
    }
    getch();
}
void lonin(user *apply)
{
    FILE *fp;
    char namefb[20];
    char passwordfb[20];
    int moneyfb;
    int rankfb;
    int judge=1;
    char choice;
    user apply[1];
    int ph;
    do
    {
        ph=0;
        printf(" 请输入用户名：\n");
        gets(namefb);
        fflush(stdin);
        printf(" 请输入密码：\n");
        fflush(stdin);
        gets(passwordfb);
        fp=fopen("data.dat","rb");
        while(!feof(fp))
        {
            fread(apply,sizeof(user),1,fp);
            if(!strcmp(namefb,apply->name)&&!strcmp(passwordfb,apply->password))
            {
                *rankfb=apply->rank;
                *moneyfb=apply->money;
                judge=0;
                break;
            }
        }
        if(judge==1)
        {
            printf(" 账号不存在或密码错误,是否重新输入？(y/n)\n");
            fflush(stdin);
            choice=getch();
            if(choice=='y')
                ph=1;
            else
                ph=0;
        }
    }while(ph==1);
    if(judge==0)
    {
        system("cls");
        printf(" 登陆成功！\n\n");
        printf(" 名字：%s\n",apply->name);
        printf(" 等级：%d\n",apply->rank);
        printf(" 财富：%d\n",apply->money);
    }
}
void sign()
{
    FILE *fp;
    char namefb[20],passwordfb[20],passwordfb1[20];
    int moneyfb=1000,rankfb=1;
    int judge=1;
    char choice;
    user apply[1];
    printf(" 请输入用户名：\n");
    gets(namefb);
    fflush(stdin);
    while(judge==1)
    {
        printf(" 请输入密码：\n");
        fflush(stdin);
        gets(passwordfb);
        printf(" 请再输入一遍：\n");
        fflush(stdin);
        gets(passwordfb1);
        if(strcmp(passwordfb,passwordfb1))
        {
            printf(" 两次密码输入不匹配。\n");
            judge=1;
        }
        else
            judge=0;
    }
    printf(" 是否创建此账号？(y/n)\n");
    fflush(stdin);
    choice=getch();
    if(choice=='y')
    {
        strcpy(apply->name,namefb);
        strcpy(apply->password,passwordfb);
        apply->money=moneyfb;
        apply->rank=rankfb;
        fp=fopen("data.dat","ab+");
        fwrite(apply,sizeof(user),1,fp);
        fclose(fp);
        printf(" 成功创建");getch();
    }
    else
    {
        printf(" 已取消。");
    }

}
void enter()
{
    printf("HHH");
}
