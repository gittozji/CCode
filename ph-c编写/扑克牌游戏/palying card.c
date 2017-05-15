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
typedef struct player
{
    int pai[5];
    int number;
    int judge;
    int scord;
}player;
void lonin(char namefb[],char passwordfb[],int *moneyfb,int *rankfb);
void sign();
void enter(user *apply);
void scatter(int card[],player *mine);
void supply(int card[],player *mine);
int sum(player *mine);
int chance(int a);
void main()
{
    char namefb[20],passwordfb[20];
    int *moneyfb=0,*rankfb=0;
    char choice;
    user *apply;
    apply=(user*)malloc(sizeof(user));
    randomize();
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
            lonin(namefb,passwordfb,moneyfb,rankfb);
            printf(" �Ƿ������Ϸ��(y/n)\n");
            fflush(stdin);
            choice=getch();
            if(choice=='y')
            {
                strcpy(apply->name,namefb);
                strcpy(apply->password,passwordfb);
                apply->money=*moneyfb;
                apply->rank=*rankfb;
                enter(apply);
            }
            break;
        case '2':
            system("cls");sign();break;
        default:break;
    }
    getch();
}
void lonin(char namefb[],char passwordfb[],int *moneyfb,int *rankfb)         /*��½����*/
{
    FILE *fp;
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
            system("cls");
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
void sign()                      /*ע���˺ź���*/
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
void enter(user *apply)      /*��Ϸ���ܺ���*/
{
    player *one,*two,*mine,*holt;
    int card[55]={0};
    int i,count=0;
    char chooice;
    one=(player*)malloc(sizeof(player));
    two=(player*)malloc(sizeof(player));
    mine=(player*)malloc(sizeof(player));
    holt=(player*)malloc(sizeof(player));
    for(i=0;i<5;i++)
    {
        holt->pai[i]=0;
        mine->pai[i]=0;
        one->pai[i]=0;
        two->pai[i]=0;
    }
    holt->number=0;
    mine->number=0;
    one->number=0;
    two->number=0;
    holt->judge=0;
    mine->judge=0;
    one->judge=0;
    two->judge=0;
    holt->scord=0;
    mine->scord=0;
    one->scord=0;
    two->scord=0;
    scatter(card,one);
    scatter(card,two);
    scatter(card,mine);
    scatter(card,holt);
    system("cls");
    gotoxy(35,6);printf("%c %c",11,11);
    gotoxy(30,7);printf("ׯ��______________________");
    gotoxy(12,11);printf("%c %c",11,11);
    gotoxy(8,12);printf("2��______________________");
    gotoxy(57,11);printf("%c %c",11,11);
    gotoxy(53,12);printf("1��______________________");
    gotoxy(35,16);printf("%d%c %d%c",mine->pai[0]/10,mine->pai[0]%10,mine->pai[1]/10,mine->pai[1]%10);
    gotoxy(30,17);printf("�Լ�______________________\n");
    do
    {
        chooice='n';
        if(one->judge==0&&one->number<5)
        {
            if(!random(chance(sum(one))))
            {
                supply(card,one);
                gotoxy(57+one->number+6,11);
                printf("%d%c",one->pai[one->number-1]/10,one->pai[one->number-1]%10);
            }
            else
            {
                one->judge=1;
            }
        }
        if(two->judge==0&&two->number<5)
        {
            if(!random(chance(sum(two))))
            {
                supply(card,two);
                gotoxy(12+(two->number-2)*6,11);
                printf("%d%c",two->pai[two->number-1]/10,two->pai[two->number-1]%10);
            }
            else
            {
                two->judge=1;
            }
        }
        if(mine->judge==0&&mine->number<5)
        {
            gotoxy(1,1);
            printf(" �Ƿ���?(y/n)");
            fflush(stdin);
            chooice=getch();
            if(chooice=='y')
            {
                supply(card,mine);
                gotoxy(35+(two->number-2)*6,16);
                printf("%d%c",holt->pai[holt->number-1]/10,holt->pai[holt->number-1]%10);
            }
            else
            {
                mine->judge=1;
            }
        }
        if(holt->judge==0&&holt->number<5)
        {
            if(!random(chance(sum(holt))))
            {
                supply(card,holt);
                gotoxy(35+two->number+6,6);
                printf("%d%c",two->pai[two->number-1]/10,two->pai[two->number-1]%10);
            }
            else
            {
                
                holt->judge=1;
            }
        }
        count++;              printf("\n\n\n\n");
    }while((mine->judge==0||holt->judge==0||one->judge==0||two->judge==0)&&count<3);
    getch();
    gotoxy(35,6);printf("%d%c %d%c",holt->pai[0]/10,holt->pai[0]%10,holt->pai[1]/10,holt->pai[1]%10);
    gotoxy(1,18);
    if((mine->scord<=21&&mine->scord>holt->scord)||(mine->scord<=21&&holt->scord>21))
        printf("HHH��ϲ�㣬Ӯ������Ϸ��");
    else
        printf("HHH��ϲ�㣬�������Ϸ��");
}
void scatter(int card[],player *mine)      /*���ƺ���*/
{
    int ph[55]={00,14,15,13,16,24,25,23,26,34,35,33,36,44,45,43,46,54,55,53,56,64,65,63,66,74,75,73,76,84,85,83,86,94,95,93,96,104,105,103,106,114,115,113,116,124,125,123,126,134,135,133,136,141,142};
    int i,k;
    mine->number=0;
    while(mine->number<2)
    {
        i=random(56);
        k=i;
        i=ph[i];
        if(i>0&&card[k]!=1)
        {
            mine->pai[mine->number]=i;
            card[k]=1;
            mine->number++;
        }
    }
}
void supply(int card[],player* mine)           /*���ƺ���*/
{
    int ph[55]={00,14,15,13,16,24,25,23,26,34,35,33,36,44,45,43,46,54,55,53,56,64,65,63,66,74,75,73,76,84,85,83,86,94,95,93,96,104,105,103,106,114,115,113,116,124,125,123,126,134,135,133,136,141,142};
    int i,j=0,k;

    do
    {
        i=random(56);
        k=i;
        i=ph[i];
        if(card[k]==0)
        {
            mine->pai[mine->number]=i;
            mine->number++;
            card[k]=1;
            j=1;
        }

    }while(j==0);
}
int sum(player *mine)
{
    int i,j,k,l,count=0,sum=0,sum1=0,sum2=0,max=0,sum21,sum22,sum23,sum24;
    for(i=0;i<mine->number;i++)                         /*��A����С������ͳ�Ƶ���*/
    {
        if(mine->pai[i]/10==1||mine->pai[i]/10==14)
        {
            count++;
        }
        else
        {
            if(mine->pai[i]/10>10)
            {
                sum1=sum1+10;
            }
            else
            {
                sum1=sum1+mine->pai[i]/10;
            }
        }
    }
    if(count==1)                                       /*A����С������ͳ�Ƶ���*/
    {

        for(i=0;i<2;i++)
        {
            sum2=0;
            if(i==0)
            {
                sum2=sum2+1;
            }
            if(i==1)
            {
                sum2=sum2+11;
            }
            sum=sum1+sum2;
            if(sum>max&&sum<=21)
            {
                max=sum;
            }
        }
        if(max==0)
            max=sum;
    }
    if(count==2)
    {
        for(i=0;i<2;i++)
        {
            sum2=0;
            if(i==0)
                sum2=sum2+1;
            if(i==1)
                sum2=sum2+11;
            sum21=sum2;
            for(j=0;j<2;j++)
            {
                sum2=sum21;
                if(j==0)
                    sum2=sum2+1;
                if(j==1)
                    sum2=sum2+11;
                sum=sum1+sum2;
                if(sum>max&&sum<=21)
                {
                    max=sum;
                }
            }
        }
        if(max==0)
            max=sum;
    }
    if(count==3)
    {
        for(i=0;i<2;i++)
        {
            sum2=0;
            if(i==0)
                sum2=sum2+1;
            if(i==1)
                sum2=sum2+11;
            sum21=sum2;
            for(j=0;j<2;j++)
            {
                sum2=sum21;
                if(j==0)
                    sum2=sum2+1;
                if(j==1)
                    sum2=sum2+11;
                sum22=sum2;
                for(k=0;k<2;k++)
                {
                    sum2=sum22;
                    if(k==0)
                        sum2=sum2+1;
                    if(k==1)
                        sum2=sum2+11;
                    sum=sum1+sum2;
                    if(sum>max&&sum<=21)
                    {
                        max=sum;
                    }
                }
            }
        }
        if(max==0)
            max=sum;
    }
    if(count==4)
    {
        for(i=0;i<2;i++)
        {
            sum2=0;
            if(i==0)
                sum2=sum2+1;
            if(i==1)
                sum2=sum2+11;
            sum21=sum2;
            for(j=0;j<2;j++)
            {
                sum2=sum21;
                if(j==0)
                    sum2=sum2+1;
                if(j==1)
                    sum2=sum2+11;
                sum22=sum2;
                for(k=0;k<2;k++)
                {
                    sum2=sum22;
                    if(k==0)
                        sum2=sum2+1;
                    if(k==1)
                        sum2=sum2+11;
                    sum23=sum2;
                    for(l=0;l<2;l++)
                    {
                        sum2=sum23;
                        if(l==0)
                            sum2=sum2+1;
                        if(l==1)
                            sum2=sum2+11;
                        sum=sum1+sum2;
                        if(sum>max&&sum<=21)
                        {
                            max=sum;
                        }    
                    }
                }
            }
        }
        if(max==0)
            max=sum;
    }
    if(mine->number==4)
    {
        sum=0;
        for(i=0;i<4;i++)
        {
            if(mine->pai[i]/10==1||mine->pai[i]/10==14)
                sum=sum+1;
            else
            {
                if(mine->pai[i]/10>10)
                    sum=sum+10;
                else
                    sum=sum+mine->pai[i]/10;
            }
        }
        if(sum<14)
        {
             mine->scord=sum;
            return sum;
        }
    }
    if(count!=0)
    {
        mine->scord=max;
        return max;
    }
    else
    {
         mine->scord=sum1;
        return sum1;
    }
}
int chance(int a)
{
    if(a<16)
        return 1;
    if(a==16)
        return 2;
    if(a==17)
        return 4;
    if(a==18)
        return 6;
    if(a==19)
        return 20;
    if(a==20)
        return 50;
    if(a>=21)
        return 100;
}
