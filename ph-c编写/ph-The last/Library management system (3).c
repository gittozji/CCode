/*ͼ��ݹ���ϵͳ*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define left 0x4b00
#define right 0x4d00
#define mm (ldata *)malloc(sizeof(ldata))
typedef struct data     /*����ṹ�����鼮��Ϣ*/
{
    char isbn[20];      /*ISBN��*/
    char bname[30];     /*����*/
    char aname[20];     /*������*/
    char style[3];      /*ns(��Ȼ��ѧ��ss(����ѧ)*/
    char department[30];/*���浥λ*/
    char time[11];      /*����ʱ��*/
    double money;       /*�۸�*/
    long int number;    /*��������*/
    struct data *next;  /*�ڵ�*/
}ldata;
void create();              /*�鼮��⺯��*/
void alter();               /*�鼮��Ϣ�޸ĺ���*/
void delet();               /*�鼮��Ϣɾ������*/
void seek(int inlet);       /*�鼮����*/
void main()                 /*������*/
{
    FILE *fp;
    int ph1,ph2,ph3,ph4;
    char account[9],accountfb[12];    /*�˺�*/
    char choice;
    char c;                           /*������������*/
    int i;
    char password[7],passwordfb[7];   /*����*/
    system( "graftabl 936");          /*��ʾ����*/
    system("cls");                    /*����*/
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
    do
    {
        ph4=0;        /*����phϵ�г�ʼֵΪ0������ͬ��*/
        do            /*do-while������ڷ�����һ���湦��,����Ϊȡ��goto��䣨��ͬ��*/
        {
            ph1=0;
            system("cls");
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
            choice=getch();                               /*�����û�ѡ��*/
            clrscr();
            if(choice=='1')                               /*����VIPϵͳ����*/
            {
                if((fp=fopen("acco_pass.dat","rb"))==NULL)           /*�򿪴��VIP�˺ż�������ļ�*/
                {
                    system("cls");
                    gotoxy(25,15);
                    printf(" �޷��򿪡�acco_pass.dat���ļ�!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
                    exit(0);
                }
                fread(account,sizeof(account),1,fp);                 /*��ȡ�˺�*/
                fread(password,sizeof(password),1,fp);               /*��ȡ����*/
                do
                {
                    system("CLS");
                    ph3=0;
                    gotoxy(29,6);
                    printf("��¼���ݹ���ϵͳ");
                    gotoxy(21,8);
                    printf("*********************************");
                    gotoxy(21,18);
                    printf("*********************************");
                    gotoxy(30,10);
                    printf("�������˺�:\n");
                    gotoxy(30,12);
                    scanf("%s",accountfb);
                    gotoxy(30,14);
                    printf("����������(6λ�ַ�):\n");
                    gotoxy(30,16);
                    for(i=0;i<6;i++)                       /*for�������������빦��*/
                    {
                        fflush(stdin);                     /*��ջ���������ͬ��*/
                        passwordfb[i]=getch();printf("*");
                    }
                    passwordfb[6]='\0';
                    if(strcmp(password,passwordfb)==0&&(strcmp(account,accountfb)==0))   /*�˻���������ȷ������if���*/
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
                                case '1':                                /*����ͼ����⺯��*/
                                    clrscr();create();break;
                                case '2':                                /*����ͼ��ɾ������*/
                                    clrscr();delet();break;
                                case '4':                                /*����ͼ���޸ĺ���*/
                                    clrscr();alter();break;
                                case '5':
                                    ph1=1;break;                         /*����do-whileѭ����������һ����*/
                                case '3':                                /*����ͼ����ҹ���*/
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
                                        case '1':                      /*����������*/
                                            clrscr();seek(1);break;
                                        case '2':                      /*������������*/
                                            clrscr();seek(2);break;
                                        case '4':                      /*��ͼ�����Ͳ���*/
                                            clrscr();seek(3);break;
                                        case '3':                      /*�����������*/
                                            clrscr();seek(4);break;
                                        case '5':                      /*��ISBN�����*/
                                            clrscr();seek(5);break;
                                        case '6':
                                            ph2=1;break;               /*������һ����*/
                                        default:break;
                                    }
                            }
                        }while(ph2==1);

                    }
                    else                                      /*������˺Ų�ƥ��*/
                    {
                        system("CLS");
                        gotoxy(30,10);
                        printf("�˺Ż������������");
                        gotoxy(30,12);
                        printf("1-���������˺�����");
                        gotoxy(30,14);
                        printf("������������һ����\n");
                        fflush(stdin);
                        c=getch();
                        if(c=='1')
                            ph3=1;
                        else
                            ph1=1;
                    }

                }while(ph3==1);
                if(fclose(fp))
                {                                           /*�ر��ļ�*/
                    system("cls");
                    gotoxy(25,15);
                    printf(" �޷��رա�acco_pass.dat���ļ�!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
                    exit(0);
                }
            }
            else                                           /*��ͨ��Ա����*/
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
        printf("1-������ʼҳ");
        gotoxy(30,12);
        printf("���������˳�");
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
void create()  /*ͼ�����*/
{
    FILE *fp;
    ldata *head,*pm,*p1,*p2,*pc,*pls;
    char isbnfb[20];       /*ISBN�븱��������Ϊ�û��������Ϣ����ͬ����*/
    char bnamefb[30];     /*��������*/
    char anamefb[20];     /*����������*/
    char stylefb[3];      /*ns(��Ȼ��ѧ��ss(����ѧ)����*/
    char departmentfb[30];/*���浥λ����*/
    char timefb[11];      /*����ʱ�丱��*/
    double moneyfb;       /*�۸񸱱�*/
    long int numberfb;    /*������������*/
    char ch;
    int ph1,cjbz,bcbz=0;
    char cc;
    if((fp=fopen("data.dat","ab+"))==NULL)             /*�򿪱���ͼ����Ϣ���ļ�*/
    {
        system("cls");
        gotoxy(25,15);
        printf(" �޷��򿪡�data.dat���ļ�!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
        exit(0);
    }
    head=mm;                              /*����mmΪ(ldata *)malloc(sizeof(ldata))*/
    p1=head;
    ch=fgetc(fp);                         /*�����ļ���һ���ַ�*/
    if(ch!=EOF)                           /*�ļ��ǿգ�����if���*/
    {
        rewind(fp);                       /*�ļ�ָ��ָ���ļ�ͷ*/
        fread(p1,sizeof(ldata),1,fp);     /*���ļ���ȡһ���ṹ����p1*/
        pm=mm;                            /*pm�������뵽�Ľṹ���׵�ַ*/
        p1->next=pm;                      /*��pm����p1->next*/
        p1=p1->next;                      /*p1ָ��p1->next*/
        while(!feof(fp))                  /*�ļ���βʱ����*/
        {
            fread(p1,sizeof(ldata),1,fp);
            pm=mm;
            p1->next=pm;
            p1=p1->next;
            pc=p1;                       /*pcָ�����������ڴ���ļ�*/
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
        printf("  ������ISBN��:\n");scanf("%s",isbnfb);
        while(strlen(isbnfb)>19)          /*����isbnfb���Ȳ�����19(��ͬ)*/
        {
            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
            scanf("%s",isbnfb);
        }
        printf(" �������ͼ�����ͣ�ns��ss��:\n");
        scanf("%s",stylefb);
        while(strlen(stylefb)>2)
        {
            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
            scanf("%s",stylefb);
        }
        printf(" ����������:\n");fflush(stdin);gets(bnamefb);
        while(strlen(bnamefb)>29)
        {
            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
            fflush(stdin);
            gets(bnamefb);
        }
        printf(" ������������:\n");fflush(stdin);gets(anamefb);
        while(strlen(anamefb)>19)
        {
            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
            fflush(stdin);
            gets(anamefb);
        }
        printf(" ��������浥λ:\n");fflush(stdin);gets(departmentfb);
        while(strlen(departmentfb)>29)
        {
            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
            fflush(stdin);
            gets(departmentfb);
        }
        printf(" ���������ʱ��:\n");fflush(stdin);gets(timefb);
        while(strlen(timefb)>10)
        {
            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
            fflush(stdin);
            gets(timefb);
        }
        printf(" �������鼮�۸�:\n");
        scanf("%lf",&moneyfb);
        printf(" �������鼮������:\n");
        scanf("%ld",&numberfb);
        p2=head;
        while(p2!=p1)                          /*�˶�����ISBN���Ƿ��Ѵ���*/
        {
            if(!strcmp(p2->isbn,isbnfb))
            {
                cjbz=0;                        /*ISBN���Ѵ��ڣ���cjbz(������־)=0*/
                break;
            }
            p2=p2->next;
        }
        if(cjbz==1)                            /*cjbz==1�����д����ṹ��*/
        {
            bcbz=1;                            /*�����˽ṹ�壬����bcbz�������־��=1*/
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
            printf("\n�Ƿ��������?y/n\n");
            fflush(stdin);
            cc=getch();
            if(cc=='y'||cc=='Y')
                ph1=1;                         /*phϵ��=1������do-whileѭ��*/

        }
        if(cjbz==0)
        {
            system("CLS");
            gotoxy(27,9);
            printf("___________________");
            gotoxy(27,13);
            printf("___________________");
            gotoxy(30,10);
            printf("ISBN:%s�Ѵ���");
            gotoxy(30,12);
            printf("�Ƿ��������Y/N\n");
            fflush(stdin);
            cc=getch();
            if(cc=='y'||cc=='Y')
                ph1=1;                         /*phϵ��=1������do-whileѭ��*/
        }
    }while(ph1==1);
    pls->next=NULL;
    if(bcbz==1)                               /*�����־=1�����б�����ļ�����*/
    {
        gotoxy(30,10);
        printf("���ڱ�������\n");
        while(pc!=NULL)                       /*������������׷�ӽ��ļ�*/
        {
            fwrite(pc,sizeof(ldata),1,fp);
            pc=pc->next;

        }
         while(head!=NULL)                        /*�ͷ������ڴ�*/
        {
            pc=head;
            head=head->next;
            free(pc);
        }

        system("CLS");

        if(fclose(fp))                            /*�ر��ļ�*/
        {
            system("cls");
            gotoxy(25,15);
            printf(" �޷��رա�data.dat���ļ�!\n");
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
        printf("����ɹ�");
        gotoxy(24,13);
        printf("        ������˳�\n");
        getch();
    }

}
void alter()               /*�޸�ͼ����Ϣ���*/
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
        printf(" �޷��򿪡�data.dat���ļ�!\n");
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
        printf(" �޷��رա�data.dat���ļ�!\n");
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
        printf("%c ������Ҫ�޸�ͼ���ISBN�� %c\n",14,14);
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
                judge=1;                                    /*���ҵ���Ϣ����judge=1������־*/
                printf("\n�Ƿ��޸�������Ϣ?(Y/N)\n");
                fflush(stdin);
                realy=getch();
                do
                {
                    ph3=0;
                    if(realy=='y'||realy=='Y')
                    {
                        system("CLS");
                        ph2=1;                          /*phϵ��=1����־����do-while���ѭ��*/
                        gotoxy(1,1);
                        printf("  ������ISBN��:\n");scanf("%s",isbnfb);
                        while(strlen(isbnfb)>19)
                        {
                            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
                            scanf("%s",isbnfb);
                        }
                        printf(" �������ͼ�����ͣ�ns��ss��:\n");
                        scanf("%s",stylefb);
                        while(strlen(stylefb)>2)
                        {   
                            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
                            scanf("%s",stylefb);
                        }
                        printf(" ����������:\n");fflush(stdin);gets(bnamefb);
                        while(strlen(bnamefb)>29)
                        {
                            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
                            fflush(stdin);
                            gets(bnamefb);
                        }
                        printf(" ������������:\n");fflush(stdin);gets(anamefb);
                        while(strlen(anamefb)>19)
                        {
                            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
                            fflush(stdin);
                            gets(anamefb);
                        }
                        printf(" ��������浥λ:\n");fflush(stdin);gets(departmentfb);
                        while(strlen(departmentfb)>29)
                        {
                            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
                            fflush(stdin);
                            gets(departmentfb);
                        }
                        printf(" ���������ʱ��:\n");fflush(stdin);gets(timefb);
                        while(strlen(timefb)>10)
                        {
                            printf(" ��������ݳ���Ԥ�跶Χ������������:\n");
                            fflush(stdin);
                            gets(timefb);
                        }
                        printf(" �������鼮�۸�:\n");
                        scanf("%lf",&moneyfb);
                        printf(" �������鼮������:\n");
                        scanf("%ld",&numberfb);
                        while(pc!=NULL)
                        {
                            if(pc!=p1)
                            {
                                if(!strcmp(pc->isbn,isbnfb))
                                    jixu=1;                        /*��ISBN�Ѵ��ڣ�jixu=1*/
                            }
                            pc=pc->next;
                        }
                        if(jixu==0)                                /*ISBN�����ڣ����Դ����ṹ��*/
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
                            printf("ISBN:%s�Ѵ���");
                            gotoxy(30,12);
                            printf("�Ƿ��������Y/N\n");
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
                        printf("�޸���ȡ��!");
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
            printf("�Ƿ�ȷ�����ϲ���(Y/N)\n");
            fflush(stdin);
            realy=getch();
            if(realy=='Y'||realy=='y')
            {
                if((fp=fopen("data.dat","wb"))==NULL)
                {
                    system("cls");
                    gotoxy(25,15);
                    printf(" �޷��򿪡�data.dat���ļ�!\n");
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
                    printf(" �޷��رա�data.dat���ļ�!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
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
            gotoxy(30,8);
            printf("δ�ҵ�ISBN��%s",isbnfb);
            gotoxy(23,7);
            printf("****************************");
            gotoxy(30,10);
            printf("1-������һ����");
            gotoxy(30,12);
            printf("���������˳�");
            gotoxy(23,13);
            printf("****************************\n");
            gotoxy(42,17);
            printf("         ---Ph\n");
            fflush(stdin);
            cc=getch();
            if(cc=='1')
                ph1=1;                             /*phϵ��=1����־����do-while���ѭ��*/
        }
    }while(ph1==1);
    while(head!=NULL)                        /*�ͷ������ڴ�*/
    {
        pc=head;
        head=head->next;
        free(pc);
    }
}
void delet()        /*ɾ��ͼ����Ϣ�������*/
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
        printf(" �޷��򿪡�data.dat���ļ�!\n");
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
        printf(" �޷��رա�data.dat���ļ�!\n");
        gotoxy(17,14);
        printf("***************************************************");
        gotoxy(7,16);
        printf("***************************************************\n");
        getch();
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
            gotoxy(80,12);printf("|\n");
            printf("�Ƿ�����ɾ�������鼮��Ϣ?(Y/N)\n");
            fflush(stdin);
            realy=getch();
            if(realy=='y'||realy=='Y')
            {
                if((fp=fopen("data.dat","wb"))==NULL)
                {
                    system("cls");
                    gotoxy(25,15);
                    printf(" �޷��򿪡�data.dat���ļ�!\n");
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
                    printf(" �޷��رա�data.dat���ļ�!\n");
                    gotoxy(17,14);
                    printf("***************************************************");
                    gotoxy(7,16);
                    printf("***************************************************\n");
                    getch();
                    exit(0);
                }
                system("CLS");
                gotoxy(30,10);
                printf("ɾ���ɹ�!");
                fflush(stdin);
                getch();
            }
            system("CLS");
            gotoxy(23,9);
            printf("____________________________");
            gotoxy(30,10);
            printf(" 1-��������");
            gotoxy(30,12);
            printf(" ���������˳�");
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
                    gotoxy(80,12);printf("|\n");
                    printf("�Ƿ�����ɾ�������鼮��Ϣ?(Y/N)\n");
                    fflush(stdin);
                    realy=getch();
                    if(realy=='y'||realy=='Y')
                    {   
                        if((fp=fopen("data.dat","wb"))==NULL)
                        {
                            system("cls");
                            gotoxy(25,15);
                            printf(" �޷��򿪡�data.dat���ļ�!\n");
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
                            printf(" �޷��رա�data.dat���ļ�!\n");
                            gotoxy(17,14);
                            printf("***************************************************");
                            gotoxy(7,16);
                            printf("***************************************************\n");
                            getch();
                            exit(0);
                        }
                        system("CLS");
                        gotoxy(30,10);
                        printf("ɾ���ɹ�!");
                        fflush(stdin);
                        getch();
                    }
                    system("CLS");
                    gotoxy(30,12);
                    printf("1-������һ����");
                    gotoxy(30,14);
                    printf("���������˳�");
                    fflush(stdin);
                    cc=getch();
                    if(cc=='1')
                        ph1=1;
                }
                p1=p1->next;                                  /*δ�ҵ�,p1��p2ָ����һ��ַ*/
                p2=p1->next;
            }
            if(ph2==0)
            {
                system("CLS");
                gotoxy(30,8);
                printf("δ�ҵ�ISBN��%s",isbnfb);
                gotoxy(23,7);
                printf("****************************");
                gotoxy(30,10);
                printf("1-��������");
                gotoxy(30,12);
                printf("���������˳�");
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
    while(head!=NULL)                        /*�ͷ������ڴ�*/
    {
        p1=head;
        head=head->next;
        free(p1);
    }
}
void seek(int inlet)
{
    FILE *fp;
    char isbnfb[20];      /*ISBN�븱��*/
    char bnamefb[30];     /*��������*/
    char anamefb[20];     /*����������*/
    char stylefb[3];      /*ns(��Ȼ��ѧ��ss(����ѧ)����*/
    char departmentfb[30];/*���浥λ����*/
    char timefb[11];      /*����ʱ�丱��*/
    double moneyfb;       /*�۸񸱱�*/
    long int numberfb;    /*������������*/
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
        printf(" �޷��򿪡�data.dat���ļ�!\n");
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
        printf(" �޷��رա�data.dat���ļ�!\n");
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
            printf("������Ҫ����ͼ������ͣ�ss-����ѧ��ns-��Ȼ��ѧ��\n");
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
                p1=save[s1];              /*����һҳ���鼮��Ϣ*/
                leftfb=0;                 /*�䵱Կ�����ã�Ϊ1���б��棬Ϊ0��������*/
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
                if(ii==0&&s1>=0&&jie==0)         /*jie�䵱Կ�׹��ܣ�Ϊ0ʱ����Ȩ����if*/
                                                 /*�Ӷ�����Ϣ�����save*/
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
                ii++;                  /*��¼һҳ���鼮��Ŀ�����ֵΪ6*/
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
            gotoxy(30,8);
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
            gotoxy(23,7);
            printf("****************************");
            gotoxy(30,10);
            printf("1-��������");
            gotoxy(30,12);
            printf("���������˳�");
            gotoxy(23,13);
            printf("****************************\n");
            gotoxy(42,17);
            printf("         ---Ph\n");
            fflush(stdin);
            cc=getch();
            if(cc=='1')
            ph1=1;                                                     /*phϵ��=1����־����do-while���ѭ��*/
        }
    }while(ph1==1);
    while(head!=NULL)                        /*�ͷ������ڴ�*/
    {
        p1=head;
        head=head->next;
        free(p1);
    }

}

