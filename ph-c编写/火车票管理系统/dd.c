#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define mm (data *)malloc(sizeof(data))          /*�����ڴ�*/
#define mm1 (people *)malloc(sizeof(people))
typedef struct data
{   long int date;       /*��������*/
    int fh;              /*����ʱ�䣬Сʱ*/
    int fm;              /*����*/
    int dh;              /*��վʱ�䣬Сʱ*/
    int dm;              /*����*/
    char num[7];         /*���κţ� ��T11*/
    char mdd[15];        /*Ŀ�ĵ�*/
    char qsd[15];        /*��ʼ��*/
    double money;        /*Ӳ���۸�Ӳ�Ժ����Կ��ɴ˳���2��3*/
    int rw;              /*������Ʊ*/
    int yw;              /*Ӳ����Ʊ*/
    int yz;              /*Ӳ����Ʊ*/
    struct data *next;   /*��һ�ڵ�*/
}data;                   /*�ṹ������*/
typedef struct people
{
    long int date;       /*��������*/
    char account[15];    /*�˺�*/
    char password[15];   /*����*/
    char name[15];       /*����*/
    char num[7];         /*����*/
    int zuowei;          /*��λ��1��ʾӲ����2��ʾӲ�ԣ�3��ʾ����*/
    struct people *next;
}people;
int creat();             /*������Ʊ*/
int look();              /*�鿴��Ʊ*/
int xs(data *head);      /*��ʾ����*/
int sign();              /*ע�ắ��*/
int deng();              /*��½*/
int ding();              /*��Ʊ*/
int tui();               /*��Ʊ*/
int main()
{
    char c;
    system("graftable 936");       /*��ʾ����*/
    system("cls");                 /*����(��ͬ)*/
    printf("\n\n\t\t   ��ӭʹ�û�Ʊ��Ʊϵͳ\n");    /*����*/
    printf("\t\t\t1-������Ʊ\n");
    printf("\t\t\t2-�鿴\n");
    printf("\t\t\t3-�û���½\n");
    printf("\t\t\t4-�û�ע��\n");
    printf("\t\t\t5-��Ʊ\n");
    printf("\t\t\t6-��Ʊ\n");
    printf("\t\t\t�������˳�\n");
    c=getch();
    switch(c)                     /*ѡ��*/
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
    printf("��������\n");
    fflush(stdin);
    gets(num);
    printf("������ʼ��\n");
    fflush(stdin);
    gets(qsd);
    printf("����Ŀ�ĵ�\n");
    fflush(stdin);            /*һ��дgetch������gets���������֮ǰ��Ҫдfflush����*/
    gets(mdd);
    printf("���������ڣ�20140501��\n");
    scanf("%ld",&head->date);
    printf("�����뷢��ʱ�䣨9 30��\n");
    scanf("%d%d",&head->fh,&head->fm);
    printf("�����뵽վʱ�䣨19 00��\n");
    scanf("%d%d",&head->dh,&head->dm);
    printf("����Ӳ���۸�\n");
    scanf("%lf",&money);
    strcpy(head->mdd,mdd);
    strcpy(head->qsd,qsd);
    head->money=money;
    strcpy(head->num,num);
    head->rw=30;                  /*ϵͳĬ��������Ʊ30*/
    head->yw=30;
    head->yz=40;
    if((fp=fopen("data.dat","ab+"))==NULL)      /*�򿪴�Ż�Ʊ��Ϣ���ļ�*/
    {
        printf("�޷��򿪣�������");
        getch();
    }
    fwrite(head,sizeof(data),1,fp);             /*���ṹ��д���ļ�*/
    fclose(fp);
    printf(" ����ɹ�");
    printf("�Ƿ��������?(y/n)\n");
    c=getch();
    if(c=='y')
        return creat();                        /*����creat������������ʵ��ѭ��*/
    else
        return main();
}
int look()
{
    FILE *fp;
    data *head=mm,*p1,*pls=NULL,*pm;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    p1=head;
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(data),1,fp);
        pm=mm;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls->next=NULL;              /*����β����Ϊ��*/
    p1=head;
    system("cls");
    while(p1->next!=NULL)
    {
        xs(p1);getch();system("cls");     /*��ʾ��Ʊ��Ϣ*/
        p1=p1->next;
    }
}
int xs(data *head)                        /*��ʾ��Ʊ��Ϣ*/
{
    printf("���Σ�%s   ·;��%s->%s    ���ڣ�%ld\n",head->num,head->qsd,head->mdd,head->date);
    printf("����ʱ�� %d:%d,��վʱ�� %d:%d\n",head->fh,head->fm,head->dh,head->dm);
    printf("Ӳ��:%.2lfԪ,Ӳ��:%.2lfԪ,����:%.2lfԪ\n",head->money,head->money*2,head->money*3);
    printf("Ӳ����Ʊ:%d,Ӳ����Ʊ:%d,������Ʊ:%d\n",head->yz,head->yw,head->rw);
    printf("\n");

}
int sign()
{
    char account[15];
    int judge=0;                        /*�����жϾ����ж�ʲô��������*/
    char num1[7]="0";
    FILE *fp,*fp1;
    people *head,*head1,*pm,*pls,*p1;    /*����ָ�����*/
    head=mm1;
    if((fp1=fopen("yonhu.dat","ab+"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head1=mm1;
    p1=head1;
    while(!feof(fp1))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(people),1,fp1);
        pm=mm1;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp1);
    pls->next=NULL;              /*����β����Ϊ��*/
    p1=head1;
    system("cls");
    printf("�����������˺�\n");
    fflush(stdin);
    gets(account);
    pm=p1;
    do                                  /*����ʵ���ж��˺��Ƿ����*/
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
            printf("%s�Ѿ����ڣ�����ģ���������\n",account);
            fflush(stdin);
            gets(account);
        }
    }while(judge==1);
    strcpy(head->account,account);
    printf("����������\n");
    fflush(stdin);
    gets(head->password);
    printf("����������\n");
    fflush(stdin);
    gets(head->name);
    strcpy(head->num,num1);
    head->date=0;
    head->zuowei=0;
    if((fp=fopen("yonhu.dat","ab+"))==NULL)
    {
        printf("�޷��򿪣�������");
        getch();
    }
    fwrite(head,sizeof(people),1,fp);
    fclose(fp);
    printf("ע��ɹ�");

}
int deng()
{
    FILE *fp;
    int judge=0;
    char account[15],password[15];
    people *head=mm1,*p1,*pls=NULL,*pm;
    if((fp=fopen("yonhu.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    p1=head;
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(people),1,fp);
        pm=mm1;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls->next=NULL;              /*����β����Ϊ��*/
    p1=head;
    system("cls");
    printf("�������˺�\n");
    fflush(stdin);
    gets(account);
    printf("����������\n");
    fflush(stdin);
    gets(password);
    while(p1->next!=NULL)           /*���������ҵ�������û�*/
    {
        if(strcmp(p1->password,password)==0&&(strcmp(p1->account,account)==0))
        {
            judge=1;              /*���ڸ�����˵���Ѿ��ҵ�*/
            break;
        }
        p1=p1->next;
    }
    system("cls");
    if(judge==1)                   /*�ҵ����û����ɽ������²���*/
    {
        printf("����:%s\n",p1->name);
        printf("�Ѷ���Ʊ:%s����,����:%ld��",p1->num,p1->date);
        if(p1->zuowei==1)
            printf("Ӳ��");
        if(p1->zuowei==2)
            printf("Ӳ��");
        if(p1->zuowei==3)
            printf("����");
    }
    else
    {
        printf("�˺Ż��������\n");
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
        printf("�޷���");
        getch();
    }
    dp1=dhead;
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(dp1,sizeof(data),1,fp);
        dpm=mm;
        dp1->next=dpm;
        dpls=dp1;
        dp1=dp1->next;
    }
    fclose(fp);
    dpls->next=NULL;              /*����β����Ϊ��*/
    dp1=dhead;
    system("cls");
    if((fp=fopen("yonhu.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    p1=head;
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(people),1,fp);
        pm=mm1;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls->next=NULL;              /*����β����Ϊ��*/
    p1=head;
    system("cls");
    printf("���ȵ�¼\n");
    printf("�������˺�\n");
    fflush(stdin);
    gets(account);
    printf("����������\n");
    fflush(stdin);
    gets(password);
    while(p1->next!=NULL)                /*���û�*/
    {
        if(strcmp(p1->password,password)==0&&(strcmp(p1->account,account)==0))
        {
            judge=1;                      /*judge=1��ʾ�ҵ�*/
            break;
        }
        p1=p1->next;
    }
    system("cls");
    if(judge==1)                          /*�ҵ����û�*/
    {
        printf("����:%s\n",p1->name);

    }
    else
    {
        printf("�˺Ż��������\n");
    }
    if(judge==1)
    {
        printf("1-�����κŶ�Ʊ\n");
        printf("2-����ʼ�أ�Ŀ�ĵض�Ʊ\n");
        fflush(stdin);
        c=getch();
        if(c=='1')
        {
            printf("�����복�κ�\n");
            gets(num);
            printf("����������\n");
            scanf("%ld",&date);
            dpm=dhead;
            while(dpm!=NULL)             /*�ҵ��û�Ʊ��Ϣ��ŵĽṹ��*/
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
            printf("��������ʼ��\n");
            fflush(stdin);
            gets(qsd);
            printf("����Ŀ�ĵ�\n");
            fflush(stdin);
            gets(mdd);
            printf("����������\n");
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
            printf("δ�ҵ����ϳ���\n");
        }
        if(judge1==1)
        {
            xs(dpm);
            printf("1-����Ӳ����2-����Ӳ�ԣ�3-��������\n");
            scanf("%d",&cc);
            if(cc==1)
            {
                dpm->yz--;            /*Ӳ����Ʊ����1*/
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
            p1->date=dpm->date;              /*�û��е����ڸ���Ϊ��Ʊ������*/
            strcpy(p1->num,dpm->num);

            if((fp=fopen("yonhu.dat","wb"))==NULL)       /*���²���λ������Ϣ���ļ�*/
            {
                printf("�޷���");
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
                printf("�޷���");
                getch();
            }
            while(dhead->next!=NULL)
            {
                fwrite(dhead,sizeof(data),1,fp);
                dhead=dhead->next;
            }
            fclose(fp);
            printf("��Ʊ�ɹ�");
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
        printf("�޷���");
        getch();
    }
    p1=head;
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(people),1,fp);
        pm=mm1;
        p1->next=pm;
        pls=p1;
        p1=p1->next;
    }
    fclose(fp);
    pls->next=NULL;              /*����β����Ϊ��*/
    p1=head;
    system("cls");
    printf("���ȵ�¼\n");
    printf("�������˺�\n");
    fflush(stdin);
    gets(account);
    printf("����������\n");
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
        printf("����:%s\n",p1->name);
        printf("�Ѷ���Ʊ:%s����,����:%ld��",p1->num,p1->date);
        if(p1->zuowei==1)
            printf("Ӳ��");
        if(p1->zuowei==2)
            printf("Ӳ��");
        if(p1->zuowei==3)
            printf("����");
        printf("�Ƿ���Ʊ(y/n)\n");
        c=getch();
        if(c=='y')
        {
            if((fp=fopen("data.dat","rb"))==NULL)
            {
                printf("�޷���");
                getch();
            }
            dp1=dhead;
            while(!feof(fp))                /*���ļ���Ϣ��������*/
            {
                fread(dp1,sizeof(data),1,fp);
                dpm=mm;
                dp1->next=dpm;
                dpls=dp1;
                dp1=dp1->next;
            }
            fclose(fp);
            dpls->next=NULL;              /*����β����Ϊ��*/
            dp1=dhead;   
            while(dp1!=NULL)
            {
                if(strcmp(dp1->num,p1->num)==0&&dp1->date==p1->date)
                    break;
                dp1=dp1->next;
            }
            if(p1->zuowei==1)
                dp1->yz++;                 /*Ӳ����Ʊ����1*/
            if(p1->zuowei==2)
                dp1->yw++;
            if(p1->zuowei==3)
                dp1->rw++;
            strcpy(head->num,num1);
            head->date=0;
            head->zuowei=0;
            if((fp=fopen("yonhu.dat","wb"))==NULL)
            {
                printf("�޷���");
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
                printf("�޷���");
                getch();
            }
            while(dhead->next!=NULL)
            {
                fwrite(dhead,sizeof(data),1,fp);
                dhead=dhead->next;
            }
            fclose(fp);
            printf("��Ʊ�ɹ�");
        }
        else
            printf("���˳�");
    }
    else
    {
        printf("�˺Ż��������\n");
    }
}

