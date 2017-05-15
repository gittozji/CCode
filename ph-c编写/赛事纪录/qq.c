#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>
#define mm (team *)malloc(sizeof(team)) 
typedef struct team
{
    int fnumber;            /*��������*/
    char name[20];          /*����*/
    int win;                /*Ӯ��*/
    int flat;               /*ƽ��*/
    int lose;               /*����*/
    int goal;               /*����*/
    int fumble;             /*ʧ��*/
    int score;              /*����*/
    struct team *next;
}team;
int creat();                 /*�½����*/
int inlet();                 /*��������*/
int pai();                   /*����*/
int xs(team*p1,int i);             /*��ʾ�������*/
int main()
{
        int n=0;
        system("graftabl 936");
        do
        {
        system("cls");
        printf("   ***************************�����Ϣ����ϵͳ**************************\n");
        printf("   *                          1.�½������Ϣ                           *\n");        
        printf("   *                          2.������������                           *\n");
        printf("   *                          3.�����������                           *\n");
        printf("   *                          0.�˳�ϵͳ                               *\n");            
        printf("   *********************************************************************\n");
        printf("   *********************************************************************\n");
        printf("   �����빦�����: ");
        scanf("%d",&n);    
        switch(n)
        {
            case 1: creat();break;
            case 2: inlet();break;
            case 3: pai();break;
            default:break;
        }
        }while(n);
}
int creat()
{
    FILE *fp;
    int fnumber;        
    char name[20];            
    int win;
    int flat;
    int lose;
    int goal;
    int fumble;
    int score; 
    int n;
    int i=0;
    team *head,*p,*pm,*p1;
    head=mm;
    p=head;

    fp=fopen("data.dat","wb");
    printf("���������\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        p1=p;
        printf("�����%d���Ӷ���\n",i+1);
        fflush(stdin); 
        gets(p->name);
        p->fnumber=0;
        p->win=0;
        p->flat=0;
        p->lose=0;
        p->fumble=0;
        p->score=0;
        p->goal=0;
        pm=mm;
        p->next=pm;
        p=p->next;
    }
    p1->next=NULL;                     /*������βΪ��*/
    while(head!=NULL)                  /*д���ļ�*/
    {
        fwrite(head,sizeof(team),1,fp);
        p1=head;
        head=head->next;
        free(p1);                     /*�ͷ��ڴ�*/
    }
    printf(" ����ɹ�\n");
    fclose(fp);
    fflush(stdin);
    getch();
}
int inlet()
{
    FILE *fp;
    int i=0,j;
    int w;
    int l;
    team *head,*p1,*pcl1,*pcl=NULL,*pm;
    if((fp=fopen("data.dat","rb"))==NULL)      /*�ԡ�rb����ʽ���ļ�*/
    {
        printf("�޷���");
        getchar();
    }
    head=mm;                                  /*�����ڴ�*/
    p1=head;
    while(!feof(fp))                         /*���ļ�*/
    {
        i++;
        fread(p1,sizeof(team),1,fp);
        pm=mm;
        pcl1=pcl;           
        pcl=p1;
        p1->next=pm;
        p1=p1->next;
    }
    fclose(fp);
    pcl1->next=NULL;
    p1=head;
    for(j=0;j<i-1;j++)
    {
        printf("�����롰%s���Ľ�������ʧ������\n",p1->name);
        scanf("%d%d",&w,&l);
        if(w>l)
        {
            p1->win++;
            p1->score+=3;
        }
        if(l==w)
        {
            p1->flat++;
            p1->score+=1;
        }
        if(l>w)
        {
            p1->lose++;
        }
        p1->fnumber++;
        p1->goal+=w;
        p1->fumble+=l;
        p1=p1->next;
    }
    if((fp=fopen("data.dat","wb"))==NULL)
    {
        printf("�޷���");
        getchar();
    }
    while(head!=NULL)
    {
        fwrite(head,sizeof(team),1,fp);
        p1=head;
        head=head->next;
        free(p1);
    }
    printf("����ɹ�");
    fflush(stdin);
    getch();
    fclose(fp);   
}
int pai()
{
    FILE *fp;
    int hang=0;
    int i=1;
    team *head,*h=NULL,*p1,*ptr,*ptr1,*ptr2,*pm,*pls=NULL,*pls1;
    if((fp=fopen("data.dat","rb"))==NULL)
    {
        printf("�޷���");
        getch();
    }
    head=mm;
    p1=head;
    while(!feof(fp))
    {
        fread(p1,sizeof(team),1,fp);
        pm=mm;
        p1->next=pm;
        pls1=pls;
        pls=p1;
        p1=p1->next;
    }
    pls1->next=NULL;
    fclose(fp);
    p1=head;
    while(p1!=NULL)                  /*��������㷨*/
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
            while((ptr->score<ptr2->score)&&(ptr2->next!=NULL))
            {
                ptr1=ptr2;
                ptr2=ptr2->next;
            }
            if(ptr->score>=ptr2->score)
            {
                if(ptr->score>ptr2->score)
                {
                    if(h==ptr2)
                        h=ptr;
                    else
                        ptr1->next=ptr;
                    ptr->next=ptr2;
                }
                if(ptr->score==ptr2->score)
                {
                    while((ptr->goal-ptr->fumble)<(ptr2->goal-ptr2->fumble)&&(ptr2->next!=NULL))
                    {
                        ptr1=ptr2;
                        ptr2=ptr2->next;
                    }
                    if((ptr->goal-ptr->fumble)>=(ptr2->goal-ptr2->fumble))
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
            else
            {
                ptr2->next=ptr;
                ptr->next=NULL;
            }
        }

    }
    system("cls");
    printf("______________________________________________________________\n");
    printf(" ���� ��  ����  ��������Ӯ����������ƽ��������ʧ�򩧻��֩�\n");
    printf("______________________________________________________________\n");

    while(h!=NULL)
    {
        xs(h,i++);
        h=h->next;
        hang++;
        if(hang>8)
        {
            fflush(stdin);
            hang=0;
            getch();
            system("cls");
            printf("______________________________________________________________\n");
            printf(" ���� ��  ����  ��������Ӯ����������ƽ��������ʧ�򩧻��֩�\n");
            printf("______________________________________________________________\n");
        }
    }
    fflush(stdin);
    getch();
    fclose(fp);
}
int xs(team *p1,int i)
{

    printf("��%-2d����%-8s��%-4d��%-4d��%-4d��%-4d��%-4d��%-4d��%-4d��\n",i,p1->name,p1->fnumber,p1->win,p1->lose,p1->flat,p1->goal,p1->fumble,p1->score);
    printf("______________________________________________________________\n");
}


