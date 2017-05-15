#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define mm (goods *)malloc(sizeof(goods))
typedef struct goods
{
    int num;         /*商品号*/
    char name[20];   /*商品名*/
    char gyname[20]; /*供应商名*/
    double inmoney;  /*进货价*/
    double outmoney; /*销售价*/
    int style;       /*1为TV，2为DVD*/
    int number;      /*销售数量*/
    double sum;      /*销售总额*/
    struct goods *next;
}goods;
int look();         /*消费者查看有哪些商品*/
int inlet();        /*商品入库*/
int buy1();         /*购买商品*/
int tui1();         /*退货。*/
int tui2();         /*退货。一次退DVD和TV*/
int tong();         /*统计，按销售数量排序*/
int buy2();         /*购买商品，一次性买DVD和TV*/
int xs(goods *head,int a);  /*显示函数，look调用时a=0，tong调用时a=1*/
int main()
{
    char c;
    char a;
    int numfb;                  /*fb用于接收用户输入的信息，以赋给结构体对应的成员(下同）*/
    char namefb[20];
    char gynamefb[20];
    int stylefb;
    double inmoneyfb;
    double outmoneyfb;
    int numberfb;
    system( "graftabl 936");          /*显示中文*/
    system("cls");
    printf(" 1-阅览商品\n");
    printf(" 2-入库\n");
    printf(" 3-买入\n");
    printf(" 4-退货\n");
    printf(" 5-统计\n");
    fflush(stdin);
    c=getch();
    system("cls");
    switch(c)
    {
        case '1':look();break;
        case '2':inlet();break;
        case '3':
            printf(" 1-单一商品买入\n 2-双样商品团购\n");
            fflush(stdin);
            a=getch();
            if(a=='1')
                buy1();
            if(a=='2');
                buy2();
            break;
        case '4':
            printf(" 1-单一商品退货\n 2-双样商品团退\n");
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
        printf("无法打开");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))                /*将文件信息读进链表*/
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举，老师不允许也只好认了*/
        pls=p1;
        p1=p1->next;
    }                              /*关闭文件*/
    fclose(fp);
    pls1->next=NULL;               /*链表尾部赋为空*/
    p1=head;                      /*逐个显示链表中内容*/
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
    fflush(stdin);                      /*清除缓冲流*/
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
    printf(" 请输入商品号:");
    ptr=mm;
    do
    {   cl=0;                        /*do-while语句用于判断新的号码是否已存在*/
        fp=fopen("data.dat","ab+");
        scanf("%d",&numfb);

        while(!feof(fp))
        {

            fread(ptr,sizeof(goods),1,fp);
            if(ptr->num==numfb)
            {
                cl=1;
                printf(" 此号码已存在，请重新输入\n");
                break;
            }
        }

    }while(cl==1);
    fclose(fp);
    printf(" 请输入商品类别(1-TV，2-DVD):");
    scanf("%d",&stylefb);
    printf(" 请输入商品名:");
    fflush(stdin);
    gets(namefb);
    printf(" 请输入供应商名:");
    fflush(stdin);
    gets(gynamefb);
    printf(" 请输入进货价:");
    scanf("%lf",&inmoneyfb);
    printf(" 请输入销售价:");
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
        printf("无法打开");
        getch();
    }
    fwrite(head,sizeof(goods),1,fp);      /*将新的结构体写进链表*/
    fclose(fp);
    printf("保存成功!");
    printf("是否继续入库？（y/n）\n");
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
        printf("无法打开");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举，老师不允许也只好认了*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    printf(" 请输入要买入的商品号，数量：\n");
    scanf("%d%d",&numfb,&numberfb);
    p1=head;
    while(p1!=NULL)
    {
        if(p1->num==numfb)
        {
            printf("购买成功！");
            break;
        }
        p1=p1->next;
    }
    p1->number=p1->number+numberfb;
    p1->sum=p1->sum+p1->outmoney*numberfb;
    if((fp=fopen("data.dat","wb"))==NULL)
    {
        printf("无法打开");
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
        printf("无法打开");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举，老师不允许也只好认了*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    printf(" 请输入要买入的商品号，数量：\n");
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
        printf("没有此商品\n");
    else
        judge=1;
    if(judge==1)
    {
        printf(" 请输入另一样要买入的商品号：\n");
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
            printf("没有此商品\n");
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
            printf("无法打开");
            getch();
        }
        while(head!=NULL)
        {
            fwrite(head,sizeof(goods),1,fp);
            p1=head;
            head=head->next;
            free(p1);
        }
        printf("购买成功");
    }
    else
    {
        printf("购买失败");
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
        printf("无法打开");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举，老师不允许也只好认了*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    printf(" 请输入要退货的商品号，数量：\n");
    scanf("%d%d",&numfb,&numberfb);
    p1=head;
    while(p1!=NULL)
    {
        if(p1->num==numfb)
        {
            printf("退货成功！");
            break;
        }
        p1=p1->next;
    }
    p1->number=p1->number-numberfb;
    p1->sum=p1->sum-p1->outmoney*numberfb;
    if((fp=fopen("data.dat","wb"))==NULL)
    {
        printf("无法打开");
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
        printf("无法打开");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举，老师不允许也只好认了*/
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    printf(" 请输入要退还的商品号，数量：\n");
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
        printf("没有此商品\n");
    else
        judge=1;
    if(judge==1)
    {
        printf(" 请输入另一样要退还的商品号：\n");
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
            printf("没有此商品\n");
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
            printf("无法打开");
            getch();
        }
        while(head!=NULL)
        {
            fwrite(head,sizeof(goods),1,fp);
            p1=head;
            head=head->next;
            free(p1);
        }
        printf("退还成功");
    }
    else
    {
        printf("退还失败");
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
        printf("无法打开");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(goods),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;           /*避免乱码，最最最最无奈之举，老师不允许也只好认了*/
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
    printf(" 商品号：%d          商品名: %s       销售价：%.2lf\n",head->num,head->name,head->outmoney);
    printf(" 商品类: %d  (1-TV,2-DVD)            供应商: %s\n",head->style,head->gyname);
    if(a==1)
    {
        printf(" 销售量: %d         进货价: %.2lf          销售总额: %.2lf\n",head->number,head->inmoney,head->sum);
    }
    printf("______________________________________________________________________________\n");
}


