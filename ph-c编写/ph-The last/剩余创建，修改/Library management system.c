/*ͼ��ݹ���ϵͳ*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define left 0x4b00
#define right 0x4d00
#define mm malloc(sizeof(ldata))
typedef struct data     /*����ṹ�����鼮��Ϣ*/
{
    char isbn[20];      /*ISBN��*/
    char bname[30];     /*����*/
    char aname[20];     /*������*/
    char style[3];      /*ns(��Ȼ��ѧ��ss(����ѧ)*/
    char department[20];/*���浥λ*/
    char time[11];      /*����ʱ��*/
    double money;       /*�۸�*/
    long int number;    /*��������*/
    struct data *next;  /*�ڵ�*/
}ldata;
void create();    /*�鼮��⺯��*/
void alter();     /*�鼮��Ϣ�޸ĺ���*/
void delet();     /*�鼮��Ϣɾ������*/
void seek(int inlet);      /*�鼮����*/
int fuzzy(char *a,char *b);  /*ģ����ѯ��ں���*/
void main()                  /*������*/
{
    FILE *fp;
    int ph1,ph2,ph3,phi;
    char account[9],accountfb[12];  /*�˺�*/
    char choice;
    char c;
    int inclec,i;                     /*1-������2-��������3-���ͣ�4-�����磬5-ISBN��*/
    char password[7],passwordfb[7]; /*����*/
    system( "graftabl 936");        /*��ʾ����*/
    do
    {
        phi=0;
        do           /*do-while������ڷ�����һ���湦��,����Ϊȡ��goto��䣨��ͬ��*/
        {
            ph1=0;                      /*ph1=1Ϊ�˳�do-while�������*/
            clrscr();
            gotoxy(29,7);
            printf("       ��ӭʹ��");
            gotoxy(27,8);
            printf("**************************");         /*��*/
            gotoxy(30,10);
            printf("1-ѡ�� VIP �˻���¼");                /*ʼ*/
            gotoxy(30,13);
            printf("2-ѡ����ͨ���˻���¼");               /*��*/
            gotoxy(30,16);
            printf("���������˳���ѯϵͳ");               /*��*/
            gotoxy(27,19);
            printf("**************************\n");
            gotoxy(26,23);
            printf("��Ȩ��ph�����治��������ʹ��\n");
            choice=getch();
            clrscr();
            if(choice=='1')
            {
                if((fp=fopen("acco_pass.dat","rb"))==NULL)            /*�򿪴����VIP�˺ż�������ļ�*/
                {
                    printf(" �޷��򿪡�acco_pass.dat���ļ�\n");
                    getch();
                    exit(0);
                }
                fread(account,sizeof(account),1,fp);
                fread(password,sizeof(password),1,fp);
                do
                {
                    system("CLS");
                    ph3=0;
                    gotoxy(30,10);                                            /*��*/
                    printf("�������˺�:\n");                                  /*½*/
                    gotoxy(30,12);                                            /*��*/
                    scanf("%s",accountfb);                                    /*��*/
                    gotoxy(30,14);
                    printf("����������(6λ�ַ�):\n");
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
                            printf("��ѡ��");
                            gotoxy(14,12);
                            printf("****************************************************");
                            gotoxy(22,14);
                            printf("1-ͼ�����           2-ɾ���鼮");
                            gotoxy(22,16);
                            printf("3-����ͼ��           4-�޸��鼮");
                            gotoxy(22,18);
                            printf("5-������һ����       �������˳�");
                            gotoxy(14,20);
                            printf("****************************************************\n");
                            c=getch();
                            switch(c)
                            {
                                case '1':clrscr();create();break;
                                case '2':clrscr();delet();break;
                                case '4':clrscr();alter();break;
                                case '5':ph1=1;break;                        /*phϵ��=1����־����do-while���ѭ��*/
                                case '3':clrscr();
                                        gotoxy(35,10);
                                        printf("��ѡ��");
                                        gotoxy(14,12);
                                        printf("****************************************************");
                                        gotoxy(22,14);
                                        printf("1-����������           2-������������");
                                        gotoxy(22,16);
                                        printf("3-��������           4-�����������");
                                        gotoxy(22,18);
                                        printf("5-��ISBN�����         6-������һ����");
                                        gotoxy(22,20);
                                        printf("7-���������˳�");
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
                                            case '6':ph2=1;break;              /*phϵ��=1����־����do-while���ѭ��*/
                                            default:break;
                                        }
                            }
                        }while(ph2==1);

                    }
                    else
                    {
                        system("CLS");
                        gotoxy(30,10);
                        printf("�˺Ż������������");
                        gotoxy(30,12);
                        printf("c-���������˺�����");
                        gotoxy(30,14);
                        printf("������������һ����\n");
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
                    printf(" �޷��رա�acco_pass.dat���ļ�\n");
                    exit(0);
                }
            }
            else
            {
                if(choice=='2')
                {
                    clrscr();
                    gotoxy(35,10);
                    printf("��ѡ��");
                    gotoxy(14,12);
                    printf("****************************************************");
                    gotoxy(22,14);
                    printf("1-����������           2-������������");
                    gotoxy(22,16);
                    printf("3-��������           4-�����������");
                    gotoxy(22,18);
                    printf("5-��ISBN�����         6-������һ����");
                    gotoxy(22,20);
                    printf("7-���������˳�");
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
        printf("c-������ʼҳ");
        gotoxy(30,12);
        printf("���������˳�");
        fflush(stdin);
        c=getch();
        if(c=='c')
            phi=1;
    }while(phi==1);
}
void create()  /*ͼ�����*/
{
    FILE *fp;
    ldata *head,*p,*p1;
    char c='y';
    char cc;
    char isbnfb[20];      /*ISBN�븱��*/
    char bnamefb[30];     /*��������*/
    char anamefb[20];     /*����������*/
    char stylefb[3];      /*ns(��Ȼ��ѧ��ss(����ѧ)����*/
    char departmentfb[20];/*���浥λ����*/
    char timefb[11];      /*����ʱ�丱��*/
    double moneyfb;       /*�۸񸱱�*/
    long int numberfb;    /*������������*/
    if((fp=fopen("data.dat","ab"))==NULL)
    {
        printf("�޷��򿪡�data.dat���ļ�");
        exit(0);
    }
    head=mm;
    p=head;
    printf(" ����������ISBN�롢ͼ�����ͣ�ns��ss�����۸񡢷�����:\n");
    scanf("%s%s%lf%ld",isbnfb,stylefb,&moneyfb,&numberfb);
    printf(" ����������:\n");fflush(stdin);gets(bnamefb);
    printf(" ������������:\n");fflush(stdin);gets(anamefb);
    printf(" ��������浥λ:\n");fflush(stdin);gets(departmentfb);
    printf(" ���������ʱ��:\n");fflush(stdin);gets(timefb);

    while(c=='y')                /*����������Ϣ*/
    {
        strcpy(p->isbn,isbnfb);
        strcpy(p->bname,bnamefb);
        strcpy(p->aname,anamefb);
        strcpy(p->style,stylefb);
        strcpy(p->department,departmentfb);
        strcpy(p->time,timefb);
        p->money=moneyfb;
        p->number=numberfb;

        printf("\n�Ƿ�������룿y/n\n");
        fflush(stdin);
        c=getch();
        if(c=='y')
        {
            p1=mm;
            p->next=p1;
            p=p->next;
            printf("\n����������ISBN�롢ͼ�����ͣ�ns��ss�����۸񡢷�����:\n");
            scanf("%s%s%lf%ld",isbnfb,stylefb,&moneyfb,&numberfb);
            printf(" ����������:\n");fflush(stdin);gets(bnamefb);
            printf(" ������������:\n");fflush(stdin);gets(anamefb);
            printf(" ��������浥λ:\n");fflush(stdin);gets(departmentfb);
            printf(" ���������ʱ��:\n");fflush(stdin);gets(timefb);
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
    system("CLS");           /*��������*/

    if(fclose(fp))
        {
            printf(" �޷��رա�acco_pass.dat���ļ�\n");
            exit(0);  
        }
    gotoxy(33,10);
    printf("����ɹ�");
    gotoxy(24,13);
    printf("        ������˳�\n");
    getch();
}
void alter()               /*�޸�ͼ����Ϣ���*/
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
        printf("�޷��򿪡�data.dat���ļ�");
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
        printf(" �޷��رա�data.dat���ļ�\n");
        exit(0);
    }
    p1=NULL;
    do
    {
        ph2=0;
        ph1=0;
        system("CLS");
        gotoxy(30,10);
        printf(" ������Ҫ�޸�ͼ���ISBN��\n");
        fflush(stdin);
        gets(isbnfb);
        p1=head;
        while(p1!=NULL)
        {
            if(!(strcmp(p1->isbn,isbnfb)))
            {
                system("CLS");
                printf("\n\n\n\n\n\n");
                printf("                      %c ISBNΪ%s��ͼ����Ϣ���� %c\n",14,head->isbn,14);printf("--------------------------------------------------------------------------------");
                printf("|     ISBN     |              ����               |        ������       |  ���� |\n|     �۸�     |           ���浥λ              |       ����ʱ��      |  ���� |\n");
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
                printf("\n�Ƿ��޸�������Ϣ?(Y/N)\n");
                fflush(stdin);
                realy=getch();
                if(realy=='y'||realy=='Y')
                {
                    system("CLS");
                    ph2=1;                          /*phϵ��=1����־����do-while���ѭ��*/
                    gotoxy(1,1);
                    printf(" ����������ISBN�롢ͼ�����ͣ�ns��ss�����۸񡢷�����:\n");
                    scanf("%s%s%lf%ld",isbnfb,stylefb,&moneyfb,&numberfb);
                    printf(" ����������:\n");fflush(stdin);gets(bnamefb);
                    printf(" ������������:\n");fflush(stdin);gets(anamefb);
                    printf(" ��������浥λ:\n");fflush(stdin);gets(departmentfb);
                    printf(" ���������ʱ��:\n");fflush(stdin);gets(timefb);
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
                    printf("�޸���ȡ��!");
                    fflush(stdin);
                    getch();
                }
            }
            p1=p1->next;

        }

        if(judge==1&&ph2==1)
        {
            gotoxy(20,30);
            printf("�Ƿ�ȷ���޸�(Y/N)\n");
            fflush(stdin);
            realy=getch();
            if(realy=='Y'||realy=='y')
            {
                if((fp=fopen("data.dat","wb"))==NULL)
                {
                    printf("�޷��򿪡�data.dat���ļ�");
                    exit(0);
                }
                while(head!=NULL)
                {
                    fwrite(head,sizeof(ldata),1,fp);
                    head=head->next;
                }
                if(fclose(fp))
                {
                printf(" �޷��رա�data.dat���ļ�\n");
                exit(0);
                }
                clrscr();
                gotoxy(30,10);
                printf("�޸ĳɹ�!");
                fflush(stdin);
                getch();
            }
            else
            {
                clrscr();
                gotoxy(30,10);
                printf("�޸���ȡ��!");
                fflush(stdin);
                getch();
            }
        }
        if(judge==0)
        {
            system("CLS");
            gotoxy(30,10);
            printf("δ�ҵ�ISBN��%s",isbnfb);
            gotoxy(30,12);
            printf("c-������һ����");
            gotoxy(30,14);
            printf("���������˳�");
            fflush(stdin);
            cc=getch();
            if(cc=='c')
                ph1=1;                             /*phϵ��=1����־����do-while���ѭ��*/
        }
    }while(ph1==1);
}
void delet()        /*ɾ��ͼ����Ϣ�������*/
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
        printf("�޷��򿪡�data.dat���ļ�");
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
        printf(" �޷��رա�data.dat���ļ�\n");
        exit(0);
    }
    do
    {
        ph2=0;                                 /*ph2=1ʱ,���������ҵ���Ϊ0ʱ,˵��û�ҵ�*/
        zhao=0;                                /*zhao=1ʱ��˵��������ϢΪ������ͷ*/
        ph1=0;
        clrscr();
        gotoxy(30,10);
        printf(" ������Ҫ����ͼ���ISBN��\n");
        fflush(stdin);
        gets(isbnfb);
        if(head!=NULL&&(!strcmp(head->isbn,isbnfb)))
        {
            ph2=1;
            zhao=1;
            system("CLS");
            printf("\n\n\n\n\n\n");
            printf("                      %c ISBNΪ%s��ͼ����Ϣ���� %c\n",14,head->isbn,14);printf("--------------------------------------------------------------------------------");
            printf("|     ISBN     |              ����               |        ������       |  ���� |\n|     �۸�     |           ���浥λ              |       ����ʱ��      |  ���� |\n");
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
            printf("�Ƿ�����ɾ�������鼮��Ϣ?(Y/N)\n");
            fflush(stdin);
            realy=getch();
            if(realy=='y'||realy=='Y')
            {
                if((fp=fopen("data.dat","wb"))==NULL)
                {
                    printf("�޷��򿪡�data.dat���ļ�");
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
                    printf(" �޷��رա�data.dat���ļ�\n");
                    exit(0);
                    printf("ϵͳ�ѳ���");
                    fflush(stdin);
                    getch();
                }
                system("CLS");
                gotoxy(30,10);
                printf("ɾ���ɹ�!");
                fflush(stdin);
                getch();
            }
            system("CLS");
            gotoxy(30,12);
            printf("c-������һ����");
            gotoxy(30,14);
            printf("���������˳�");
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
                    printf("                      %c ISBNΪ%s��ͼ����Ϣ���� %c\n",14,p2->isbn,14);printf("--------------------------------------------------------------------------------");
                    printf("|     ISBN     |              ����               |        ������       |  ���� |\n|     �۸�     |           ���浥λ              |       ����ʱ��      |  ���� |\n");
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
                    printf("�Ƿ�����ɾ�������鼮��Ϣ?(Y/N)\n");
                    fflush(stdin);
                    realy=getch();
                    if(realy=='y'||realy=='Y')
                    {   
                        if((fp=fopen("data.dat","wb"))==NULL)
                        {
                            printf("�޷��򿪡�data.dat���ļ�");
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
                            printf(" �޷��رա�data.dat���ļ�\n");
                            exit(0);
                            printf("ϵͳ�ѳ���");
                            fflush(stdin);
                            getch();
                        }
                        system("CLS");
                        gotoxy(30,10);
                        printf("ɾ���ɹ�!");
                        fflush(stdin);
                        getch();
                    }
                    system("CLS");
                    gotoxy(30,12);
                    printf("c-������һ����");
                    gotoxy(30,14);
                    printf("���������˳�");
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
                printf("δ�ҵ�ISBN��%s",isbnfb);
                gotoxy(30,12);
                printf("c-������һ����");
                gotoxy(30,14);
                printf("���������˳�");
                fflush(stdin);
                cc=getch();
                if(cc=='c')
                    ph1=1;
            }
        }
    }while(ph1==1);
}
void seek(int inlet)       /*��ISBN���ѯ���*/
{
    FILE *fp;
    char isbnfb[20];      /*ISBN�븱��*/
    char bnamefb[30];     /*��������*/
    char anamefb[20];     /*����������*/
    char stylefb[3];      /*ns(��Ȼ��ѧ��ss(����ѧ)����*/
    char departmentfb[20];/*���浥λ����*/
    char timefb[11];      /*����ʱ�丱��*/
    double moneyfb;       /*�۸񸱱�*/
    long int numberfb;    /*������������*/
    char cc;
    int outlet,key;
    int judge,ph1,i,ii,s1,leftfb,jie,chukou;
    ldata *head,*p1,*pm,*save[10];
    head=mm;
    p1=head;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷��򿪡�data.dat���ļ�");
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
        printf(" �޷��رա�data.dat���ļ�\n");
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
            printf("������Ҫ����ͼ���ISBN��\n");
            fflush(stdin);
            gets(isbnfb);
        }
        if(inlet==1)
        {
            printf("������Ҫ����ͼ�������\n");
            fflush(stdin);
            gets(bnamefb);   
        }
        if(inlet==2)
        {
            printf("������Ҫ���ҵ�������\n");
            fflush(stdin);
            gets(anamefb);
        }
        if(inlet==3)
        {
            gotoxy(17,10);
            printf("������Ҫ����ͼ������ͣ�ss-����ѧ��ns-���ȿ�ѧ��\n");
            fflush(stdin);
            gets(stylefb);
        }
        if(inlet==4)
        {
            printf("������Ҫ���ҵĳ��浥λ\n");
            fflush(stdin);
            gets(departmentfb);
        }
        clrscr();
        while(p1!=NULL)
        {
            if(inlet==5)
            if(!strcmp(p1->isbn,isbnfb))     /*�����Ϣ*/
            {
                chukou=1;
                printf("\n\n\n\n\n\n");
                printf("                      %c ISBNΪ%s��ͼ����Ϣ���� %c\n",14,p1->isbn,14);printf("--------------------------------------------------------------------------------");
                printf("|     ISBN     |              ����               |        ������       |  ���� |\n|     �۸�     |           ���浥λ              |       ����ʱ��      |  ���� |\n");
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
                gotoxy(40,i);printf("|����:%s",p1->bname);
                gotoxy(1,i+1);printf("|������:%s",p1->aname);
                gotoxy(1,i+2);printf("|����:%s",p1->style);
                gotoxy(40,i+2);printf("|�۸�:%.2lf",p1->money);
                gotoxy(40,i+1);printf("|���浥λ:%s",p1->department);
                gotoxy(18,i+2);printf("|����ʱ��:%s",p1->time);
                gotoxy(60,i+2);printf("|��������:%ld",p1->number);
                gotoxy(1,i+3);
                printf("--------------------------------------------------------------------------------");
                judge=1;
                i+=4;
                ii++;
                if(ii==6)
                {

                    printf("������<-������->�����з�ҳ");
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
                        printf(" �������һҳ\n\n");
                        printf(" ����<-��������һҳ������->������\n\n");
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
            printf("�Ƿ��������?(Y/N)\n");
            fflush(stdin);
            cc=getch();
            if(cc=='y'||cc=='Y')
                ph1=1;                                         /*phϵ��=1����־����do-while���ѭ��*/
        }

        if(judge==0)
        {
            gotoxy(30,10);
            if(inlet==5)
                printf("δ�ҵ�ISBN��%s\n",isbnfb);
            if(inlet==1)
                printf("δ�ҵ�������%s\n",bnamefb);
            if(inlet==2)
                printf("δ�ҵ����ߣ�\n",anamefb);
            if(inlet==3)
                printf("δ�ҵ����ͣ�\n",stylefb);
            if(inlet==4)
                printf("δ�ҵ������磺\n",departmentfb);
            gotoxy(30,12);
            printf("c-��������           \n\n                             �����������˳�\n");
            fflush(stdin);
            cc=getch();
            if(cc=='c')
            ph1=1;                                                     /*phϵ��=1����־����do-while���ѭ��*/
        }
        }while(ph1==1);
}

