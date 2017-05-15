#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define mm1 (information *)malloc(sizeof(information))
#define mm2 (people *)malloc(sizeof(people))
typedef struct information
{
    char account[15];/*�˺ţ������жϴ˽ṹ������ĸ��û�*/
    int year;
    int month;
    int day;
    int in_out;     /*0Ϊ���룬1Ϊ֧��*/
    double money;   /*��¼������Ϣ�Ľ�Ǯ*/
    char aim[30];   /*��ע*/
    struct information *next;
}information;
typedef struct people
{
    char account[15];
    char password[15];
}people;
int deng();                /*��½*/
int sign();                /*ע�����û�*/
int creat(people *pq);     /*��������֧����Ϣ*/
int look(people *pq);      /*�鿴*/
int xs(information *p1);   /*��ʾ����*/
int tong(people *pq);      /*ͳ�����*/
int sc(people *pq);        /*ɾ���޸ĺ���*/
int ftime(information *p,int year1,int month1,int day1,int year2,int month2,int day2);/*�Ƚ�ʱ���Ⱥ�*/
int main()
{
    FILE *fp;
    char c;
    system("graftable 936");       /*��ʾ����*/
    system("cls");                 /*����(��ͬ)*/
    printf(" 1-�˺ŵ�½\n");
    printf(" 2-ע���˺�\n");
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
    return main();              /*����������������ѭ��*/
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
    ptr=mm2;                   /*�����ڴ棬��ͬ*/
    system("cls");
    printf(" �������˺�\n");
    fflush(stdin);
    gets(accountfb);
    printf("����������\n");
    fflush(stdin);
    gets(passwordfb);
    if((fp=fopen("a_p.dat","rb"))==NULL)     /*�򿪴���˺������ļ�*/
    {
        printf("�޷���\n");
        getch();
    }
    while(!feof(fp))                          /*���ļ����ݺ˶ԣ�ƥ�䣬��judge=1���е�¼*/
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
            printf(" ��½�ɹ�\n");
            printf("1-�����Ϣ\n2-ɾ���޸�\n3-�鿴��Ϣ\n4-ͳ����Ϣ\n");
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
            printf(" ��½ʧ�ܣ�������\n");
            fflush(stdin);
            getch();
        }
        printf(" 1-����,2-����\n");
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
        printf("�޷���\n");
        getch();
    }
    printf(" �����˺�\n");
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
                printf(" �˺����Ѵ��ڣ�����������\n");
                break;
            }
        }
    }while(judge==1);
    fclose(fp);
    printf(" ��������\n");
    fflush(stdin);
    gets(passwordfb);
    strcpy(ptr1->account,accountfb);
    strcpy(ptr1->password,passwordfb);
    if((fp=fopen("a_p.dat","ab+"))==NULL)
    {
        printf("�޷��򿪣�������");
        getch();
        return sign();
    }
    fwrite(ptr1,sizeof(people),1,fp);         /*д���ļ�*/
    fclose(fp);
    printf(" ����ɹ�");
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
    printf(" 0-���룬1-֧��\n");
    scanf("%d",&in_outfb);
    printf(" ��������\n");
    scanf("%lf",&moneyfb);
    printf(" �����뱸ע\n");
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
        printf("�޷��򿪣�������");
        getch();
        return deng();
    }
    fwrite(ptr,sizeof(information),1,fp);
    fclose(fp);
    printf(" ����ɹ�");
    printf(" �Ƿ��������y/n\n");
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
        printf("�޷���");
        getch();
    }
    head=mm1;
    p1=head;
    printf(" ��������ʼʱ��\n");
    scanf("%d%d%d",&year1,&month1,&day1);
    printf(" ��������ֹʱ��\n");
    scanf("%d%d%d",&year2,&month2,&day2);
    printf("____________________________________________________________________________\n");
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(information),1,fp);
        pm=mm1;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮��*/
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls1->next=NULL;               /*����β����Ϊ��*/
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
    fflush(stdin);                      /*�������������ͬ*/
    getch();   
}
int xs(information *p1)
{
    printf(" ʱ�䣺%d��%d��%d��\n",p1->year,p1->month,p1->day);
    if(p1->in_out==0)
        printf(" ���룺%.2lf\n",p1->money);
    if(p1->in_out==1)
        printf(" ֧����%.2lf\n",p1->money);
    printf(" ��ע�� %s\n",p1->aim);
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
        printf("�޷���");
        getch();
    }
    head=mm1;
    p1=head;
    printf(" ��������ʼʱ��\n");
    scanf("%d%d%d",&year1,&month1,&day1);
    printf(" ��������ֹʱ��\n");
    scanf("%d%d%d",&year2,&month2,&day2);
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(information),1,fp);
        pm=mm1;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮��*/
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls1->next=NULL;               /*����β����Ϊ��*/
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
    printf(" �����룺%.2lf\n",sum1);
    printf(" ��֧����%.2lf\n",sum2);
    printf(" ���Ϊ��%.2lf\n",sum1-sum2);
    fflush(stdin);                      /*���������*/
    getch();
}
int sc(people *pq)
{
    FILE *fp;
    int i=0;
    char accountfb[15];
    int year1,year2,month1,month2,day1,day2;
    int in_outfb;     /*0Ϊ���룬1Ϊ֧��*/
    double moneyfb;
    char aimfb[30];
    information *head,*p1,*p2,*pm,*pls1,*pls=NULL;
    char c;
    long int date1,date2;
    system("cls");
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head=mm1;
    p1=head;
    printf(" ��������ʼʱ��\n");
    scanf("%d%d%d",&year1,&month1,&day1);
    printf(" ��������ֹʱ��\n");
    scanf("%d%d%d",&year2,&month2,&day2);
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(information),1,fp);
        pm=mm1;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮��*/
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls1->next=NULL;               /*����β����Ϊ��*/
    p1=head;
    while(p1!=NULL)
    {

        i++;
        if(!(strcmp(p1->account,pq->account))&&ftime(p1,year1,month1,day1,year2,month2,day2))
        {
            xs(p1);
            printf(" 1-ɾ����2-�޸�\n\n");
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
                printf(" 0-���룬1-֧��\n");
                scanf("%d",&in_outfb);
                printf(" ��������\n");
                scanf("%lf",&moneyfb);
                printf(" �����뱸ע\n");
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
        printf("�޷���");
        getch();
    }
    while(head!=NULL)
    {
        fwrite(head,sizeof(information),1,fp);
        head=head->next;
    }
    fclose(fp);
    fflush(stdin);                      /*���������*/
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
