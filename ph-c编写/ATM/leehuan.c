#include<stdio.h> /*���ÿ⺯��*/
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#define ZHANGHUSHU 10
#define JIAOYISHU 20

int caidan();/*��¼ע��˵�*/
void zhuce();
void denglu();
void baocunshuju();

int menu();/*���˵�*/
void cunkuan();
void qukuan();
void zhuanzhang();
void chaxun();
void xiugaimima();

struct JiaoYi /*���彻�׽ṹ��*/
{
    char shijian[50];/*ʱ��*/
    char leixing[3];/*����*/
    float jine; /*���*/
    float yue;/*���*/
};
struct ZhangHu /*�����˻��ṹ��*/
{
char xingming[17];/*����*/
char zhanghao[12];/*�˺�*/
char shenfenzheng[19]; /*���֤*/
char mima[7]; /*����*/
float yue; /*���*/
struct JiaoYi jiaoyi[JIAOYISHU]; /*���˻��Ľṹ�����ڶ��彻�׵Ľṹ��*/
int jiaoyishu;
};
struct ZhangHu zhanghu[ZHANGHUSHU]; /*�����˻�����ȷ���˻���һ�ṹ�����ж��ٸ���*/
int j; /*��ǰ�˻�*/
int zhanghushu;
int k;/*�����ʺ�*/
int jiaoyishu;


void xianshizhanghu();



int caidan()/*�˵�����*/
{
    char c;
    do
    {
        system("cls"); /*ÿ��ѡ������ǰ����*/
        printf("\t\t =================��ӭʹ��ATMϵͳ===============\n\n"); /*�˵�ѡ��*/
        printf("\t\t * 1. ע��*                                     *\n");
        printf("\t\t * 2. ��¼                                      *\n");
        printf("\t\t * 3. ��������                                  *\n");
        printf("\t\t * 0. �˳�                                      *\n");
        printf("\t\t ===============================================\n");
        printf("\t\t\t������ѡ��(0-3):");
        c=getchar(); /*����ѡ��*/
    }
    while(c<'0'||c>'3');
    return(c-'0'); /*c��Ϊ�պ󷵻�����ѡ��*/
}/*�������˵��ķ���ֵ��ȷ����������ֵ*/

void zhuce()
{
    printf("\n\t\t����������:");
    scanf("%s",zhanghu[zhanghushu].xingming);
    printf("\n\t\t�������ʺ�:");
    scanf("%s",zhanghu[zhanghushu].zhanghao);
    do
     {
        printf("\n\t\t���������֤:");
        scanf("%s",zhanghu[zhanghushu].shenfenzheng);
        if(strlen(zhanghu[zhanghushu].shenfenzheng)==18)
        break;
        else
        printf("\n\t\t���֤������18,���������룡");
     }
     while(1);
     do
     { printf("\n\t\t����������:");
       scanf("%s",zhanghu[zhanghushu].mima);
       if(strlen(zhanghu[zhanghushu].mima)==6)
       break;
       else
        printf("\n\t\t���������6λ,���������룡");
     }
     while(1);
     zhanghu[zhanghushu].yue=0;
     zhanghu[zhanghushu].jiaoyishu=0;
     zhanghushu++;
     xianshizhanghu();
}


void xianshizhanghu() /*��ʾ�˻���������ʾ��������˻�*/
{
    int i;
    for(i=0;i<zhanghushu;i++)
    {
    printf("\n\n\t�ʺ�\t����\t���֤\t\t����\t���\n");
    printf("\t%s\t%s\t%s\t%s\t%.2f\n",zhanghu[i].zhanghao,zhanghu[i].xingming,zhanghu[i].shenfenzheng,zhanghu[i].mima,zhanghu[i].yue);
    system("pause");
    }
}

void denglu() /*��¼����*/
{

    char zhanghao[12],mima[7];
    int i=0;
    int mimacishu=1;
    printf("\n\t\t�������ʺ�:");
    scanf("%s",zhanghao);
    while(strcmp(zhanghao,zhanghu[i].zhanghao)!=0&&i<zhanghushu)
    i++; /**/
    if(i==zhanghushu)
    return;

        do
    {
        printf("\n\t\t����������:");
    scanf("%s",mima);

        
        if(strcmp(mima,zhanghu[i].mima)!=0)
        {
            
            if(mimacishu==3)
            {
                printf("��������������Σ��㲻������.");
                system("pause");
                return;
            }
            else
            {
                printf("�����������������:");
            
            mimacishu++;
            }
        }
        else
        break;
    }
    while(1);
    for(;;)
    {
        switch(menu()) /*ѡ���ж�*/
        {
        case 1:
        cunkuan();
        break;
        case 2:
        qukuan();
        break;
        case 3:
        zhuanzhang();
        break;
        case 4:
        chaxun();
        break;
        case 5:
        xiugaimima();
        break;
       case 0:
       return;
        }
    }

}
void baocunshuju()/*��������*/
{
  int i,j;
  FILE *fp;
  char filename[20];
  printf("\t\t\t�����ݱ��浽һ���ı��ļ���\n");/*�����ļ���*/
  printf("\t\t\t�������ļ���");
  fflush(stdin);
  scanf("%s",filename);
  if((fp=fopen(filename,"w"))==NULL)/*���ļ�*/
  {
    printf("�޷��������ļ�\n");
    system("pause");
    return;
  }
  fprintf(fp,"%d\n",zhanghushu);/*ѭ��д������*/
   printf("\t�ʺ�\t\t����\t\t���֤\t\t����\t���\t������");
  for(i=0;i<zhanghushu;i++)
  {

    fprintf(fp,"\t%15s%10s%20s%10s\t%10.2f\t%5d\n",zhanghu[i].zhanghao,zhanghu[i].xingming,zhanghu[i].shenfenzheng,zhanghu[i].mima,zhanghu[i].yue,zhanghu[i].jiaoyishu);
    for(j=0;j<zhanghu[i].jiaoyishu;j++)
      fprintf(fp,"%30s%10s%10.2f%10.2f\n",zhanghu[i].jiaoyi[j].shijian,zhanghu[i].jiaoyi[j].leixing,zhanghu[i].jiaoyi[j].jine,zhanghu[i].jiaoyi[j].yue);
   }
   fclose(fp);
}

void duqushuju()
{
  int i,j;
  FILE *fp;
  char filename[20];
  printf("\n\n\n\t���������������ݵ��ļ���:\n");
  fflush(stdin);
  gets(filename);
    if(strlen(filename)==0)
      return;
    else
      if((fp=fopen(filename,"r"))==NULL)/*���ļ�*/
      {
        printf("�޷��򿪴��ļ�\n");
        system("pause");
        return;
      }
      else
      {
       printf("\t\t�ɹ����ļ�.\n");
       getch();
       }
  fscanf(fp,"%d\n",zhanghushu);
  for(i=0;i<zhanghushu;i++)
  {
    fscanf(fp,"%15s%10s%20s%10f\t%10f%5d\n",
    zhanghu[i].zhanghao,
    zhanghu[i].xingming,
    zhanghu[i].shenfenzheng,
    zhanghu[i].mima,
    &zhanghu[i].yue,
    &zhanghu[i].jiaoyishu);
    for(j=0;j<zhanghu[i].jiaoyishu;j++)
    {
      fgets(zhanghu[i].jiaoyi[j].shijian,30,fp);
    fscanf(fp,"%5s%10f\t%10f\n",zhanghu[i].jiaoyi[j].leixing,
    &(zhanghu[i].jiaoyi[j].jine),
    &(zhanghu[i].jiaoyi[j].yue));
    }
  }
  fclose(fp);
}

int menu()
{
    
     char c;
    do
    {

    system("cls");
      printf("\n\n\t=================  ��ӭʹ�� XXX����ATM ==================\n\n");
      printf("\t=====================��ѡ�����=====================\n");
      printf("\t*                                                  *\n");
      printf("\t*    1  ʵʱ���                   2   ȡ�����    *\n");
      printf("\t*                                                  *\n");
      printf("\t*    3  ת�˷���                   4   ��ѯ        *\n");
      printf("\t*                                                  *\n");
      printf("\t*    5  �޸�����                   6   �˳�        *\n");
      printf("\t*                                                  *\n");
      printf("\t====================================================\n");
      printf("\t\t\t������ѡ��(1-7):");
      c=getchar(); /*����ѡ��*/
      system("pause");
    }
    while(c<'1'||c>'7');
    return(c-'0'); /*c��Ϊ�պ󷵻�����ѡ��*/
}

void cunkuan() /*����*/
{
    float cunkuanjine;/*����Ĵ����*/
    int k;

    int i;
    char t[30];
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    strcpy(t,asctime(timeinfo));
    for(i=0;t[i]!='\0';i++)
    if(t[i]=='\n')
    {   
        t[i]='\0';
        break;
    }
    printf("����������(�����������0,������10000,������100Ԫ�����\n");
    scanf("%f",&cunkuanjine); 
    if(cunkuanjine<=0||cunkuanjine>1000||(int)cunkuanjine%100!=0)
    {
        printf("������Ҫ��,������ѡ��");
        return;
    }
    else
    {
       k=zhanghu[j].jiaoyishu;
        strcpy(zhanghu[j].jiaoyi[k].shijian,t);
        strcpy(zhanghu[j].jiaoyi[k].leixing,"��");
        zhanghu[j].jiaoyi[k].jine=cunkuanjine;
        zhanghu[j].yue+=cunkuanjine;
        zhanghu[j].jiaoyi[k].yue=zhanghu[j].yue;
        zhanghu[j].jiaoyishu++;
        printf("\n\\t\t\t�����δ���%.2fԪ\n",cunkuanjine);
        printf("\n\\t\t\t�������Ϊ%.2fԪ\n",zhanghu[j].yue);
        printf("\nʱ��Ϊ:%s\n",zhanghu[j].jiaoyi[k].shijian);
        printf("\n����Ϊ:%s\n",zhanghu[j].jiaoyi[k].leixing);
        system("pause");
    }

}

void qukuan()   /*ȡ���*/
{
    int k;/*�����±�*/
    float qukuanjine;
    int i;
    char t[30];
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    strcpy(t,asctime(timeinfo));
    for(i=0;t[i]!='\0';i++)
    if(t[i]=='\n')
    {   
        t[i]='\0';
        break;
    }    
    printf("     ȡ�����   \n");
      printf("\t=====================��ѡ�����=====================\n");
      printf("\t*                                                  *\n");
      printf("\t*    1  100                         2   200        *\n");
      printf("\t*                                                  *\n");
      printf("\t*    3  500                         4   1000       *\n");
      printf("\t*                                                  *\n");
      printf("\t*    5  �������                    6   �������˵� *\n");
      printf("\t*                                                  *\n");
      printf("\t====================================================\n");
    scanf("%f",&qukuanjine);
    if(qukuanjine<=0||qukuanjine>10000||(int)qukuanjine%100!=0)
    {
        printf("������Ҫ��,������ѡ��");
        return;
    }
       
         else
        if(zhanghu[j].yue<qukuanjine)
        {
            printf("����˻�����,����������������");
        return;
        }
   
       {
        k=zhanghu[j].jiaoyishu;
        strcpy(zhanghu[j].jiaoyi[k].shijian,t);
        strcpy(zhanghu[j].jiaoyi[k].leixing,"ȡ");
        zhanghu[j].jiaoyi[k].jine=qukuanjine;
        zhanghu[j].yue-=qukuanjine;
        zhanghu[j].jiaoyi[k].yue=zhanghu[j].yue;
        zhanghu[j].jiaoyishu++;
        printf("\n\\t\t\t������ȡ��%.2fԪ\n",qukuanjine);
        printf("\n\\t\t\t�������Ϊ%.2fԪ\n",zhanghu[j].yue);
        printf("\nʱ��Ϊ:%s\n",zhanghu[j].jiaoyi[k].shijian);
        printf("\n����Ϊ:%s\n",zhanghu[j].jiaoyi[k].leixing);
        system("pause");
    }
}


void zhuanzhang()
{
    float zhuanzhangjine;
    int i;
    int l=0;
    char t[30],zhuanzhangzhanghao[12];
    char sign='n';
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    strcpy(t,asctime(timeinfo));
    for(i=0;t[i]!='\0';i++)
        if(t[i]=='\n')
        {
            t[i]='\0';
            
        }
     printf("��������Ҫת����ʺ�:");
     scanf("%s",zhuanzhangzhanghao);
     while(strcmp(zhanghu[l].zhanghao,zhuanzhangzhanghao)!=0&&l<zhanghushu)
        l++;
     if(l==zhanghushu)
     {
     printf("��������û������ڣ�\n");
     system("pause");
        return;
        }
     printf("\n���˻���������Ϊ%s\n,�Ƿ�ȷ��ת��Y/N��",zhanghu[j].xingming);
     scanf("\t\t%c",&sign); /*�����ж�*/
     if(sign!='y'&&sign!='Y') /*�ж�*/
        return;
    else
        {
     do
     {
        printf("\n������ת�˽��(����100������5000):");
        scanf("%f",&zhuanzhangjine);
        if(zhuanzhangjine<100||zhuanzhangjine>5000)
        {
            printf("�������,����������!");
            system("pause");
            return;
        }
        if(zhanghu[j].yue<=0||zhanghu[j].yue<zhuanzhangjine)
          {
                printf("�˻�����\n");
                system("pause");
                return;
            }
          else
            {
                k=zhanghu[j].jiaoyishu;
                strcpy(zhanghu[j].jiaoyi[k].shijian,t);
                strcpy(zhanghu[j].jiaoyi[k].leixing,"ת��");
                zhanghu[j].jiaoyi[k].jine=zhuanzhangjine;
                zhanghu[j].yue-=zhuanzhangjine;
                zhanghu[j].jiaoyi[k].yue=zhanghu[j].yue;
                zhanghu[j].jiaoyishu++;

                printf("\n\t\t�㱾��ת��%0.2fԪ\n",zhuanzhangjine);
                printf("\n\t\t������Ϊ%0.2fԪ\n",zhanghu[j].yue);
                printf("\n\t\tʱ��Ϊ:%s\n",zhanghu[j].jiaoyi[k].shijian);
                printf("\n\t\t����Ϊ:%s\n",zhanghu[j].jiaoyi[k].leixing);
                system("pause");
            }
     }while(0);
     }
        
    printf("\n\n\t\tת�˳ɹ�\n\n");
    system("pause");
} 

void xiugaimima() /*�޸����뺯��*/
{
 char mima1[7],mima2[7];
  do
    {
     do
        { 
            printf("\n\n\n\t\t����������:");
            scanf("%s",mima1);
            if(strlen(mima1)==6)
            break;
            else
            printf("\n\n\t\t���������6λ,���������룡");
        }while(1);
         do
        {
            printf("\n\n\n\t\t��ȷ������:");
            scanf("%s",mima2);
            if(strlen(mima2)==6)
            break;
            else
            printf("�������������6λ����������:");
        } while(1);
    if(strcmp(mima1,mima2)==0 ) /*�жϵڶ�������������Ƿ����һ�ε�һ��*/
         break;
     else
         printf("\n\n\t\t*|�������벻�������������:\n\n");
    } while(1);
    strcpy(zhanghu[j].mima,mima1);
    printf("\n\n\t\t�޸�����ɹ�\n\n");
    getch();
    system("pause");
}

int chaxuncaidan();/*��ѯ�˵�*/
void chaxunyue();
void chaxuncunkun();
void chaxunqukun();
void chaxunzhuangzhan();
void chaxunjiaoyi();
void duqushuju();

void chaxun() /*��ѯ����*/
{
 for(;;)
    {
        switch(chaxuncaidan()) /*ѡ���ж�*/
        {
        case 1:
       chaxunyue();
        break;
       case 2:
       chaxuncunkun();
        break;
       case 3:
      chaxunqukun();
        break;    
       case 4:
       chaxunzhuangzhan();
           break;
       case 5:
       chaxunjiaoyi();
           break;
       case 0:
       return;
        }
    }
}

int chaxuncaidan()/*�˵�����*/
{
    char c;
    do
    {
        system("cls"); /*ÿ��ѡ������ǰ����*/
        printf("\t\t *********************��ѯ�˵�*******************\n\n"); /*�˵�ѡ��*/
        printf("\t\t *| 1. ��ѯ���|\n");
        printf("\t\t *| 2. ��ѯ����¼|\n");
        printf("\t\t *| 3. ��ѯȡ���¼|\n");
        printf("\t\t *| 4. ��ѯת�˼�¼|\n");
        printf("\t\t *| 5. ��ѯ�������|\n");
        printf("\t\t *| 0. �˳� |\n");
        printf("\t\t ************************************************\n");
        printf("\t\t\t������ѡ��(0-5):");
        c=getchar(); /*����ѡ��*/
    }
    while(c<'0'||c>'5');
    return(c-'0'); /*c��Ϊ�պ󷵻�����ѡ��*/
}   
void chaxunyue()/*��ѯ����*/
{
     printf("\n\t�������Ϊ%.2fԪ\n",zhanghu[j].yue);
    system("pause");
}
void chaxuncunkun() /*��ѯ����*/
{
 int i;
    printf("\t\t *************����ѯ��¼****************\n\n");
    printf("\t�ʺ�\t����\t��������\t����ʱ��\t\t���\t���\n");
    for(i=0;i<zhanghu[j].jiaoyishu;i++)
        {
            if(strcmp(zhanghu[j].jiaoyi[i].leixing,"��")==0)
            printf("\t%s\t%s\t%s\t%s\t%.2f\t%.2f\n\n",zhanghu[j].zhanghao,
            zhanghu[j].xingming,zhanghu[j].jiaoyi[i].leixing,
            zhanghu[j].jiaoyi[i].shijian,zhanghu[j].jiaoyi[i].jine,
            zhanghu[j].jiaoyi[i].yue);
            else;
        }
        system("pause");
}
void chaxunqukun() /*��ѯȡ���*/
{
 int i;
    printf("\t\t *************ȡ���ѯ��¼****************\n\n");
    printf("\t�ʺ�\t����\t��������\t����ʱ��\t\t���\t���\n");
    for(i=0;i<zhanghu[j].jiaoyishu;i++)
        {
            if(strcmp(zhanghu[j].jiaoyi[i].leixing,"ȡ")==0)
            printf("\t%s\t%s\t%s\t%s\t%.2f\t%.2f\n\n",zhanghu[j].zhanghao,
            zhanghu[j].xingming,zhanghu[j].jiaoyi[i].leixing,
            zhanghu[j].jiaoyi[i].shijian,zhanghu[j].jiaoyi[i].jine,
            zhanghu[j].jiaoyi[i].yue);
            else;
        }
        system("pause");
}
void chaxunzhuangzhan()/*��ѯת�˺���*/
{
 int i;
    printf("\t\t *************ȡ���ѯ��¼****************\n\n");
    printf("\t�ʺ�\t����\t��������\t����ʱ��\t\t���\t���\n");
    for(i=0;i<zhanghu[j].jiaoyishu;i++)
        {
            if(strcmp(zhanghu[j].jiaoyi[i].leixing,"ת")==0)
            printf("\t%s\t%s\t%s\t%s\t%.2f\t%.2f\n\n",zhanghu[j].zhanghao,
            zhanghu[j].xingming,zhanghu[j].jiaoyi[i].leixing,
            zhanghu[j].jiaoyi[i].shijian,zhanghu[j].jiaoyi[i].jine,
            zhanghu[j].jiaoyi[i].yue);
            else;
        }
        system("pause");
}
void chaxunjiaoyi()  /*��ѯ���׺���*/
{
   int i;
    printf("\t\t *************ȡ���ѯ��¼****************\n\n");
    printf("\t�ʺ�\t����\t��������\t����ʱ��\t\t���\t���\n");
    for(i=0;i<zhanghu[j].jiaoyishu;i++)
        {

            printf("\t%s\t%s\t%s\t%s\t%.2f\t%.2f\n\n",zhanghu[j].zhanghao,
            zhanghu[j].xingming,zhanghu[j].jiaoyi[i].leixing,
            zhanghu[j].jiaoyi[i].shijian,zhanghu[j].jiaoyi[i].jine,
            zhanghu[j].jiaoyi[i].yue);

        }
        system("pause");
}


 void main() /*������*/
{    system("graftabl 936");
    duqushuju();
    for(;;)
    {
        switch(caidan()) /*�������˵��������˵��ķ���ֵ����ѡ��*/
        {
        case 1:
        zhuce();
        break;
        case 2:
        denglu();
        break;
        case 3:
        baocunshuju();
        break;
        case 0:
        printf("\t\t\t��ӭʹ��ATM!\n"); /*��������*/
        printf("\t\t\t");
        system("pause"); /*ʹ������ͣ*/
        exit(0);
        }
  }
}
