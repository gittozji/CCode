/*�˿�����Ϸ*/
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
    printf("�˿�����Ϸ���");
    gotoxy(20,15);
    printf("%c",14);                  /*��*/
    gotoxy(10,13);
    printf("%c",15);                  /*ʼ*/
    gotoxy(30,17);
    printf("%c",3);                   /*��*/
    gotoxy(34,18);
    printf("��ӭʹ�ã�");             /*��*/
    gotoxy(15,19);
    printf("***************************************************");
    gotoxy(10,20);
    printf("**************************************************************\n");
    getch();
    system("cls");
    gotoxy(27,8);
    printf(" *************************");     /*��*/
    gotoxy(30,10);
    printf("     1-��½�˺�");                /*ʼ*/
    gotoxy(30,13);
    printf("     2-ע���˺�");                /*��*/
    gotoxy(30,16);
    printf("     3-�˳���Ϸ");                /*��*/
    gotoxy(27,19);
    printf(" *************************\n");
    gotoxy(26,23);
    printf("��Ȩ��ph�����治��������ʹ��\n");
    choice=getch();                               /*�����û�ѡ��*/
    switch(choice)
    {
        case '1':
            system("cls");
            lonin(apply);
            printf(" �Ƿ������Ϸ��(y/n)\n");
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
        printf(" �������û�����\n");
        gets(namefb);
        fflush(stdin);
        printf(" ���������룺\n");
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
            printf(" �˺Ų����ڻ��������,�Ƿ��������룿(y/n)\n");
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
        printf(" ��½�ɹ���\n\n");
        printf(" ���֣�%s\n",apply->name);
        printf(" �ȼ���%d\n",apply->rank);
        printf(" �Ƹ���%d\n",apply->money);
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
    printf(" �������û�����\n");
    gets(namefb);
    fflush(stdin);
    while(judge==1)
    {
        printf(" ���������룺\n");
        fflush(stdin);
        gets(passwordfb);
        printf(" ��������һ�飺\n");
        fflush(stdin);
        gets(passwordfb1);
        if(strcmp(passwordfb,passwordfb1))
        {
            printf(" �����������벻ƥ�䡣\n");
            judge=1;
        }
        else
            judge=0;
    }
    printf(" �Ƿ񴴽����˺ţ�(y/n)\n");
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
        printf(" �ɹ�����");getch();
    }
    else
    {
        printf(" ��ȡ����");
    }

}
void enter()
{
    printf("HHH");
}
