#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define mm (goods *)malloc(sizeof(goods))
typedef struct goods
{
    int num;         /*��Ʒ��*/
    char name[20];   /*��Ʒ��*/
    char gyname[20]; /*��Ӧ����*/
    double inmoney;  /*������*/
    double outmoney; /*���ۼ�*/
    int style;       /*1ΪTV��2ΪDVD*/
    int number;      /*��������*/
    double sum;      /*�����ܶ�*/
    struct goods *next;
}goods;
int look();         /*�����߲鿴����Щ��Ʒ*/
int inlet();        /*��Ʒ���*/
int buy1();         /*������Ʒ*/
int tui1();         /*�˻���*/
int tui2();         /*�˻���һ����DVD��TV*/
int tong();         /*ͳ�ƣ���������������*/
int buy2();         /*������Ʒ��һ������DVD��TV*/
int xs(goods *head,int a);  /*��ʾ������look����ʱa=0��tong����ʱa=1*/
int main()
{
    char c;
    char a;
    int numfb;                  /*fb���ڽ����û��������Ϣ���Ը����ṹ���Ӧ�ĳ�Ա(��ͬ��*/
    char namefb[20];
    char gynamefb[20];
    int stylefb;
    double inmoneyfb;
    double outmoneyfb;
    int numberfb;
    system( "graftabl 936");          /*��ʾ����*/
    system("cls");
    printf(" 1-������Ʒ\n");
    printf(" 2-���\n");
    printf(" 3-����\n");
    printf(" 4-�˻�\n");
    printf(" 5-ͳ��\n");
    fflush(stdin);
    c=getch();
    system("cls");
    switch(c)
    {
        case '1':look();break;
        case '2':inlet();break;
        case '3':
            printf(" 1-��һ��Ʒ����\n 2-˫����Ʒ�Ź�\n");
            fflush(stdin);
            a=getch();
            if(a=='1')
                buy1();
            if(a=='2');
                buy2();
            break;
        case '4':
            printf(" 1-��һ��Ʒ�˻�\n 2-˫����Ʒ����\n");
            fflush(stdin);
            a=getch();
            if(a=='1')
                tui1();
            if(a=='2');
                tui2();
            break;
        case '5':tong();break;
        default:break;
    }
}
int look()
{
    FILE *fp;
    int hang=0;
    goods *head,*p1,*pm,*pls=NULL,*pls1;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))                /*���ļ���Ϣ��������*/
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮�٣���ʦ������Ҳֻ������*/
        pls=p1;
        p1=p1->next;
    }                              /*�ر��ļ�*/
    fclose(fp);
    pls1->next=NULL;               /*����β����Ϊ��*/
    p1=head;                      /*�����ʾ����������*/
    while(p1!=NULL)
    {
        xs(p1,0);
        p1=p1->next;
        hang++;
        if(hang>5)
        {
            fflush(stdin);
            hang=0;
            getch();
            system("cls");
        }
    }
    fflush(stdin);                      /*���������*/
    getch();
    return main();
}
int inlet()
{
    FILE *fp;
    char c;
    int cl=0;
    int numfb;
    char namefb[20];
    char gynamefb[20];
    double inmoneyfb;
    double outmoneyfb;
    int numberfb;
    double sumfb;
    int stylefb;
    goods *head,*ptr;
    head=mm;
    printf(" ��������Ʒ��:");
    ptr=mm;
    do
    {   cl=0;                        /*do-while��������ж��µĺ����Ƿ��Ѵ���*/
        fp=fopen("data.dat","ab+");
        scanf("%d",&numfb);

        while(!feof(fp))
        {

            fread(ptr,sizeof(goods),1,fp);
            if(ptr->num==numfb)
            {
                cl=1;
                printf(" �˺����Ѵ��ڣ�����������\n");
                break;
            }
        }

    }while(cl==1);
    fclose(fp);
    printf(" ��������Ʒ���(1-TV��2-DVD):");
    scanf("%d",&stylefb);
    printf(" ��������Ʒ��:");
    fflush(stdin);
    gets(namefb);
    printf(" �����빩Ӧ����:");
    fflush(stdin);
    gets(gynamefb);
    printf(" �����������:");
    scanf("%lf",&inmoneyfb);
    printf(" ���������ۼ�:");
    scanf("%lf",&outmoneyfb);
    numberfb=0;
    sumfb=0;
    head->num=numfb;
    head->sum=sumfb;
    head->number=numberfb;
    head->style=stylefb;
    head->inmoney=inmoneyfb;
    head->outmoney=outmoneyfb;
    strcpy(head->name,namefb);
    strcpy(head->gyname,gynamefb);
    if((fp=fopen("data.dat","ab+"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    fwrite(head,sizeof(goods),1,fp);      /*���µĽṹ��д������*/
    fclose(fp);
    printf("����ɹ�!");
    printf("�Ƿ������⣿��y/n��\n");
    fflush(stdin);
    c=getch();
    if(c=='y')
        inlet();
    fflush(stdin);
    getch();
    return main();
}
int buy1()
{
    FILE *fp;
    int numfb;
    int numberfb;
    goods *head,*p1,*pm,*pls=NULL,*pls1;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮�٣���ʦ������Ҳֻ������*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    printf(" ������Ҫ�������Ʒ�ţ�������\n");
    scanf("%d%d",&numfb,&numberfb);
    p1=head;
    while(p1!=NULL)
    {
        if(p1->num==numfb)
        {
            printf("����ɹ���");
            break;
        }
        p1=p1->next;
    }
    p1->number=p1->number+numberfb;
    p1->sum=p1->sum+p1->outmoney*numberfb;
    if((fp=fopen("data.dat","wb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    while(head!=NULL)
    {
        fwrite(head,sizeof(goods),1,fp);
        p1=head;
        head=head->next;
        free(p1);
    }
    fflush(stdin);
    getch();
    fclose(fp);
    return main();
}
int buy2()
{
    FILE *fp;
    int numfb;
    int judge=0;
    int numberfb;
    goods *head,*p1,*pm,*pls=NULL,*pls1,*ptr1=NULL,*ptr2=NULL;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮�٣���ʦ������Ҳֻ������*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    printf(" ������Ҫ�������Ʒ�ţ�������\n");
    scanf("%d%d",&numfb,&numberfb);
    p1=head;
    while(p1!=NULL)
    {
        if(p1->num==numfb)
        {
            ptr1=p1;
            break;
        }
        p1=p1->next;
    }
    if(ptr1==NULL)
        printf("û�д���Ʒ\n");
    else
        judge=1;
    if(judge==1)
    {
        printf(" ��������һ��Ҫ�������Ʒ�ţ�\n");
        scanf("%d",&numfb);
        p1=head;
        while(p1!=NULL)
        {
            if(p1->num==numfb)
            {
                ptr2=p1;
                break;
            }
            p1=p1->next;
        }
        if(ptr2==NULL)
            printf("û�д���Ʒ\n");
        else
            judge=2;
    }
    if(judge==2&&ptr1->style!=ptr2->style)
    {
        ptr1->number=ptr1->number+numberfb;
        ptr1->sum=ptr1->sum+ptr1->outmoney*0.8*numberfb;
        ptr2->number=ptr2->number+numberfb;
        ptr2->sum=ptr2->sum+ptr2->outmoney*0.8*numberfb;
        if((fp=fopen("data.dat","wb"))==NULL)
        {
            printf("�޷���");
            getch();
        }
        while(head!=NULL)
        {
            fwrite(head,sizeof(goods),1,fp);
            p1=head;
            head=head->next;
            free(p1);
        }
        printf("����ɹ�");
    }
    else
    {
        printf("����ʧ��");
    }
    fflush(stdin);
    getch();
    fclose(fp);
    return main();
}
int tui1()
{
    FILE *fp;
    int numfb;
    int numberfb;
    goods *head,*p1,*pm,*pls=NULL,*pls1;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮�٣���ʦ������Ҳֻ������*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    printf(" ������Ҫ�˻�����Ʒ�ţ�������\n");
    scanf("%d%d",&numfb,&numberfb);
    p1=head;
    while(p1!=NULL)
    {
        if(p1->num==numfb)
        {
            printf("�˻��ɹ���");
            break;
        }
        p1=p1->next;
    }
    p1->number=p1->number-numberfb;
    p1->sum=p1->sum-p1->outmoney*numberfb;
    if((fp=fopen("data.dat","wb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    while(head!=NULL)
    {
        fwrite(head,sizeof(goods),1,fp);
        p1=head;
        head=head->next;
        free(p1);
    }
    fflush(stdin);
    getch();
    fclose(fp);
    return main();
}
int tui2()
{
    FILE *fp;
    int numfb,judge=0;
    int numberfb;
    goods *head,*p1,*pm,*pls=NULL,*pls1,*ptr1,*ptr2;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮�٣���ʦ������Ҳֻ������*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    printf(" ������Ҫ�˻�����Ʒ�ţ�������\n");
    scanf("%d%d",&numfb,&numberfb);
    p1=head;
    while(p1!=NULL)
    {
        if(p1->num==numfb)
        {
            ptr1=p1;
            break;
        }
        p1=p1->next;
    }
    if(ptr1==NULL)
        printf("û�д���Ʒ\n");
    else
        judge=1;
    if(judge==1)
    {
        printf(" ��������һ��Ҫ�˻�����Ʒ�ţ�\n");
        scanf("%d",&numfb);
        p1=head;
        while(p1!=NULL)
        {
            if(p1->num==numfb)
            {
                ptr2=p1;
                break;
            }
            p1=p1->next;
        }
        if(ptr2==NULL)
            printf("û�д���Ʒ\n");
        else
            judge=2;
    }
    if(judge==2&&ptr1->style!=ptr2->style)
    {
        ptr1->number=ptr1->number-numberfb;
        ptr1->sum=ptr1->sum-ptr1->outmoney*0.8*numberfb;
        ptr2->number=ptr2->number-numberfb;
        ptr2->sum=ptr2->sum-ptr2->outmoney*0.8*numberfb;
        if((fp=fopen("data.dat","wb"))==NULL)
        {
            printf("�޷���");
            getch();
        }
        while(head!=NULL)
        {
            fwrite(head,sizeof(goods),1,fp);
            p1=head;
            head=head->next;
            free(p1);
        }
        printf("�˻��ɹ�");
    }
    else
    {
        printf("�˻�ʧ��");
    }
    fflush(stdin);
    getch();
    fclose(fp);
    return main();
}
int tong()
{
    FILE *fp;
    int hang=0;
    goods *head,*h=NULL,*p1,*ptr,*ptr1,*ptr2,*pm,*pls=NULL,*pls1;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*�������룬������������֮�٣���ʦ������Ҳֻ������*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    p1=head;
    while(p1!=NULL)
    {
        ptr=p1;
        p1=p1->next;
        ptr2=h;
        if(h==NULL)
        {
            h=ptr;
            h->next=NULL;
        }
        else
        {
            while((ptr->number<ptr2->number)&&(ptr2->next!=NULL))
            {
                ptr1=ptr2;
                ptr2=ptr2->next;
            }
            if(ptr->number>=ptr2->number)
            {
                if(h==ptr2)
                    h=ptr;
                else
                    ptr1->next=ptr;
                ptr->next=ptr2;
            }
            else
            {
                ptr2->next=ptr;
                ptr->next=NULL;
            }
        }

    }
    while(h!=NULL)
    {
        xs(h,1);
        h=h->next;
        hang++;
        if(hang>5)
        {
            fflush(stdin);
            hang=0;
            getch();
            system("cls");
        }
    }
    fflush(stdin);
    getch();
    fclose(fp);
    return main();

}
int xs(goods *head,int a)
{
    printf(" ��Ʒ�ţ�%d          ��Ʒ��: %s       ���ۼۣ�%.2lf\n",head->num,head->name,head->outmoney);
    printf(" ��Ʒ��: %d  (1-TV,2-DVD)            ��Ӧ��: %s\n",head->style,head->gyname);
    if(a==1)
    {
        printf(" ������: %d         ������: %.2lf          �����ܶ�: %.2lf\n",head->number,head->inmoney,head->sum);
    }
    printf("______________________________________________________________________________\n");
}


