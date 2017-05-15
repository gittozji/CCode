#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shoudsave=0 ;
int count1=0,count2=0,mark=0,mark1=0 ;
/*����洢����Ϣ�Ľṹ��*/
struct train 
{
    char num[10];/*�г���*/
    char city[10];/*Ŀ�ĳ���*/
    char takeoffTime[10];/*����ʱ��*/
    char receiveTime[10];/*����ʱ��*/
    int  price;/*Ʊ��*/
    int  bookNum ;/*Ʊ��*/
};
/*��Ʊ�˵���Ϣ*/
struct man 
{
    char num[10];/*ID*/
    char name[10];/*����*/
    int  bookNum ;/*�����Ʊ��*/
};
/*�������Ϣ����Ľ��ṹ*/
typedef struct node 
{
    struct train data ;
    struct node * next ;
}Node,*Link ;
/*���嶩Ʊ������Ľ��ṹ*/
typedef struct people 
{
    struct man data ;
    struct people*next ;
}bookMan,*bookManLink ;
/* ��ʼ����*/
void printInterface()
{
    puts("********************************************************");
    puts("*      ��ӭʹ��Ԥ����Ʊϵͳ                          *");
    puts("********************************************************");
    puts("*     ��ѡ�����²���:                                  *");
    puts("*       1:�������Ϣ                                 *");
    puts("*       2:��ѯ�г���Ϣ                                 *");
    puts("*       3:Ԥ����Ʊ                                   *");
    puts("*       4:���»�Ʊ��Ϣ                               *");
    puts("*       5:����                                         *");   
    puts("*       6:���������Ϣ                                 *");
    puts("*       7:�˳�ϵͳ                                     *");
    puts("********************************************************");
}
/*���һ������Ϣ*/
void InsertTraininfo(Link linkhead)
{
    struct node *p,*r,*s ;
    char num[10];
    r = linkhead ;
    s = linkhead->next ;
    while(r->next!=NULL)
    r=r->next ;
    while(1)
    {
        printf("������𳵳���(0-return)");
        scanf("%s",num);
        if(strcmp(num,"0")==0)
          break ;
        /*�ж��Ƿ��Ѿ�����*/
        while(s)
        {
            if(strcmp(s->data.num,num)==0)
            {
                printf("�� '%s'�Ѿ�����!\n",num);
                return ;
            }
            s = s->next ;
        }
        p = (struct node*)malloc(sizeof(struct node));
        strcpy(p->data.num,num);
        printf("������յ�:");
        scanf("%s",p->data.city);
        printf("����𳵷���ʱ��:");
        scanf("%s",p->data.takeoffTime);
        printf("����𳵵�վʱ��:");
        scanf("%s",&p->data.receiveTime);
        printf("�����Ʊ��:");
        scanf("%d",&p->data.price);
        printf("����ʣ��Ʊ��:");
        scanf("%d",&p->data.bookNum);
        p->next=NULL ;
        r->next=p ;
        r=p ;
        shoudsave = 1 ;
    }
}
/*��ӡ��Ʊ��Ϣ*/
void printTrainInfo(struct node*p)
{
    puts("\n������������Ҫ����Ϣ:");
    printf(">>�𳵳���: %s\n",p->data.num);
    printf(">>�𳵵���ص�: %s\n",p->data.city);
    printf(">>����ʱ��: %s\n>>�ִ�ʱ��:  %s\n",p->data.takeoffTime,p->data.receiveTime);
    printf(">>��Ʊ�۸�:  %d\n",p->data.price);
    printf(">>��Ʊʣ����Ŀ: %d\n",p->data.bookNum);
}

struct node * Locate1(Link l,char findmess[],char numorcity[])
{
    Node*r ;
    if(strcmp(numorcity,"num")==0)
    {
        r=l->next ;
        while(r)
        {
            if(strcmp(r->data.num,findmess)==0)
            return r ;
            r=r->next ;
        }
    }
    else if(strcmp(numorcity,"city")==0)
    {
        r=l->next ;
        while(r)
        {
            if(strcmp(r->data.city,findmess)==0)
            return r ;
            r=r->next ;
        }
    }
    return 0 ;
}

/*��ѯ����Ϣ*/
void QueryTrain(Link l)

{
    Node *p ;
    int sel ;
    char str1[5],str2[10];
    if(!l->next)
    {
        printf("û���κ���Ϣ !");
        return ;
    }
    printf("Choose the way:\n>>1:���ݻ𳵳��Ų���;\n>>2:�����յ�վ����:\n");
    scanf("%d",&sel);
    if(sel==1)
    {
        printf("������𳵺�:");
        scanf("%s",str1);
        p=Locate1(l,str1,"num");
        if(p)
        {
            printTrainInfo(p);
        }
        else 
        {
            mark1=1 ;
            printf("\nû���ҵ�!");
        }
    }
    else if(sel==2)
    {
        printf("�������:");
        scanf("%s",str2);
        p=Locate1(l,str2,"city");
        if(p)
        {
            printTrainInfo(p);
        }
        else 
        {
            mark1=1 ;
            printf("\nû���ҵ�!");
        }
    }
}

/*��Ʊ��ģ��*/
void BookTicket(Link l,bookManLink k)
{
    Node*r[10],*p ;
    char ch,dem ;
    bookMan*v,*h ;
    int i=0,t=0 ;
    char str[10],str1[10],str2[10];
    v=k ;
    while(v->next!=NULL)
    v=v->next ;
    printf("�����յ�վ: ");
    scanf("%s",&str);
    p=l->next ;
    while(p!=NULL)
    {
        if(strcmp(p->data.city,str)==0)
        {
            r[i]=p ;
            i++;
        }
        p=p->next ;
    }
printf("\n\nthe number of record have %d\n",i);   
for(t=0;t<i;t++)
    printTrainInfo(r[t]);
    if(i==0)
    printf("\n\t\t\t�Բ���!û���ҵ��û���Ϣ\n");
    else 
    {
        printf("\n�Ƿ�Ԥ��?<1/0>\n");
        scanf("%d",&ch);
        if(ch == 1)
        {
            h=(bookMan*)malloc(sizeof(bookMan));
            printf("��������: ");
            scanf("%s",&str1);
            strcpy(h->data.name,str1);
            printf("�������֤��: ");
            scanf("%s",&str2);
            strcpy(h->data.num,str2);
            printf("����Ԥ����Ŀ: ");
            scanf("%d",&dem);
            h->data.bookNum=dem ;
            h->next=NULL ;
            v->next=h ;
            v=h ;
            printf("\n��ϲ�����Ѿ�Ԥ���ɹ�!");
            getch();
            shoudsave=1 ;
        }
    }
}
bookMan*Locate2(bookManLink k,char findmess[])
{
    bookMan*r ;
    r=k->next ;
    while(r)
    {
        if(strcmp(r->data.num,findmess)==0)
         {
         mark=1 ;
         return r ;
         }
         r=r->next ;
    }
    return 0 ;
}
/*�޸Ļ���Ϣ*/
void UpdateInfo(Link l)
{
    Node*p ;
    char findmess[20],ch ;
    if(!l->next)
    {
        printf("\nthere isn't record for you to modify!\n");
        return ;
    }
    else 
    {
        QueryTrain(l);
        if(mark1==0)
        {
            printf("\nȷ���޸�?\n");
            getchar();
            scanf("%c",&ch);
            if(ch=='y');
            {
                printf("\n����𳵳���:");
                scanf("%s",findmess);
                p=Locate1(l,findmess,"num");
                if(p)
                {
                    printf("�����µĻ𳵳���:");
                    scanf("%s",&p->data.num);
                    printf("�����µ��յ�վ:");
                    scanf("%s",&p->data.city);
                    printf("�����µķ���ʱ��");
                    scanf("%s",&p->data.takeoffTime);
                    printf("�����µĵִ�ʱ��:");
                    scanf("%s",&p->data.receiveTime);
                    printf("�����µ�Ʊ��::");
                    scanf("%d",&p->data.price);
                    printf("�����µ�Ʊ��:");
                    scanf("%d",&p->data.bookNum);
                    printf("\n�滻�ɹ�!\n");
                    shoudsave=1 ;
                }
                else 
                printf("\t\t\tû���ҵ�!");
            }
        }
        else 
         mark1=0 ;
    }
}
/*ϵͳ���û�����ʾ��Ϣ*/
void AdvicedTrains(Link l)
{
    Node*r ;
    char str[10];
    int mar=0 ;
    r=l->next ;
    printf("�����յ�վ: ");
    scanf("%s",str);
    while(r)
    {
        if(strcmp(r->data.city,str)==0&&r->data.bookNum<200)
        {
            mar=1 ;
            printf("\n�����ѡ�����»�!\n");
            printf("\n\n��ѡ��4Ԥ���ó�Ʊ!\n");
            printTrainInfo(r);
        }
        r=r->next ;
    }
    if(mar==0)
    printf("\n\t\t\t�Բ��������޷�Ԥ��!\n");
    
}
/*�������Ϣ*/
void SaveTrainInfo(Link l)
{
    FILE*fp ;
    Node*p ;
    int count=0,flag=1 ;
    fp=fopen("c:\\train.txt","wb");
    if(fp==NULL)
    {
        printf("�ļ��޷���!");
        return ;
    }
    p=l->next ;
    while(p)
    {
        if(fwrite(p,sizeof(Node),1,fp)==1)
        {
            p=p->next ;
            count++;
        }
        else 
        {
            flag=0 ;
            break ;
        }
    }
    if(flag)
    {
        printf("the number of the record which have been saved is %d\n",count);   //1111
        shoudsave=0 ;
    }
    fclose(fp);
}
/*���涩Ʊ�˵���Ϣ*/
void SaveBookmanInfo(bookManLink k)
{
    FILE*fp ;
    bookMan*p ;
    int count=0,flag=1 ;
    fp=fopen("c:\\man.txt","wb");
    if(fp==NULL)
    {
        printf("�ļ��޷���!");
        return ;
    }
    p=k->next ;
    while(p)
    {
        if(fwrite(p,sizeof(bookMan),1,fp)==1)
        {
            p=p->next ;
            count++;
        }
        else 
        {
            flag=0 ;
            break ;
        }
    }
    if(flag)
    {
        printf("the number of the record which have been saved is %d\n",count);   //111111
        shoudsave=0 ;
    }
    fclose(fp);
}

int main()
{
    FILE*fp1,*fp2 ;
    Node*p,*r ;
    char ch1,ch2 ;
    Link l ;
    bookManLink k ;
    bookMan*t,*h ;
    int sel ;
    l=(Node*)malloc(sizeof(Node));
    l->next=NULL ;
    r=l ;
    k=(bookMan*)malloc(sizeof(bookMan));
    k->next=NULL ;
    h=k ;
    fp1=fopen("c:\\train.txt","ab+");
    if((fp1==NULL))
    {
        printf("�޷����ļ�!");
        return 0 ;
    }
    while(!feof(fp1))
    {
        p=(Node*)malloc(sizeof(Node));
        if(fread(p,sizeof(Node),1,fp1)==1)
        {
            p->next=NULL ;
            r->next=p ;
            r=p ;
            count1++;
        }
    }
    fclose(fp1);
    fp2=fopen("c:\\man.txt","ab+");
    if((fp2==NULL))
    {
        printf("�޷����ļ�!");
        return 0 ;
    }
    
    while(!feof(fp2))
    {
        t=(bookMan*)malloc(sizeof(bookMan));
        if(fread(t,sizeof(bookMan),1,fp2)==1)
        {
            t->next=NULL ;
            h->next=t ;
            h=t ;
            count2++;
        }
    }
    fclose(fp2);
    while(1)
    {
        system("cls");
        printInterface();
        printf("��ѡ�����:  ");
        scanf("%d",&sel);
        system("cls");
        if(sel==8)
        {
            if(shoudsave==1)
            {
                getchar();
                printf("\n�ļ��Ѿ��ı䣬�Ƿ񱣴棿(y/n)?\n");
                scanf("%c",&ch1);
                if(ch1=='y'||ch1=='Y')
                {
                    SaveBookmanInfo(k);
                    SaveTrainInfo(l);
                }
            }
            printf("\nлл\n");
            break ;
            
        }
        switch(sel)
        {
            case 1 :
              InsertTraininfo(l);break ;
            case 2 :
              QueryTrain(l);break ;
            case 3 :
              BookTicket(l,k);break ;
            case 4 :
              UpdateInfo(l);break ;
            case 5 :
              AdvicedTrains(l);break ;
            case 6 :
              SaveTrainInfo(l);SaveBookmanInfo(k);break ;
            case 7 :
            return 0;
        }
        printf("\nplease press any key to continue.......");
        getch();
    }
 return 0;
}


