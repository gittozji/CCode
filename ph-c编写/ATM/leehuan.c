#include<stdio.h> /*引用库函数*/
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#define ZHANGHUSHU 10
#define JIAOYISHU 20

int caidan();/*登录注册菜单*/
void zhuce();
void denglu();
void baocunshuju();

int menu();/*主菜单*/
void cunkuan();
void qukuan();
void zhuanzhang();
void chaxun();
void xiugaimima();

struct JiaoYi /*定义交易结构体*/
{
    char shijian[50];/*时间*/
    char leixing[3];/*类型*/
    float jine; /*金额*/
    float yue;/*余额*/
};
struct ZhangHu /*定义账户结构体*/
{
char xingming[17];/*姓名*/
char zhanghao[12];/*账号*/
char shenfenzheng[19]; /*身份证*/
char mima[7]; /*密码*/
float yue; /*余额*/
struct JiaoYi jiaoyi[JIAOYISHU]; /*在账户的结构体中在定义交易的结构体*/
int jiaoyishu;
};
struct ZhangHu zhanghu[ZHANGHUSHU]; /*定义账户数来确定账户这一结构体中有多少个体*/
int j; /*当前账户*/
int zhanghushu;
int k;/*交易帐号*/
int jiaoyishu;


void xianshizhanghu();



int caidan()/*菜单函数*/
{
    char c;
    do
    {
        system("cls"); /*每次选择运行前清屏*/
        printf("\t\t =================欢迎使用ATM系统===============\n\n"); /*菜单选择*/
        printf("\t\t * 1. 注册*                                     *\n");
        printf("\t\t * 2. 登录                                      *\n");
        printf("\t\t * 3. 保存数据                                  *\n");
        printf("\t\t * 0. 退出                                      *\n");
        printf("\t\t ===============================================\n");
        printf("\t\t\t请作出选择(0-3):");
        c=getchar(); /*读入选择*/
    }
    while(c<'0'||c>'3');
    return(c-'0'); /*c变为空后返回重新选择*/
}/*根据主菜单的返回值来确定主函数的值*/

void zhuce()
{
    printf("\n\t\t请输入姓名:");
    scanf("%s",zhanghu[zhanghushu].xingming);
    printf("\n\t\t请输入帐号:");
    scanf("%s",zhanghu[zhanghushu].zhanghao);
    do
     {
        printf("\n\t\t请输入身份证:");
        scanf("%s",zhanghu[zhanghushu].shenfenzheng);
        if(strlen(zhanghu[zhanghushu].shenfenzheng)==18)
        break;
        else
        printf("\n\t\t身份证必须是18,请重新输入！");
     }
     while(1);
     do
     { printf("\n\t\t请输入密码:");
       scanf("%s",zhanghu[zhanghushu].mima);
       if(strlen(zhanghu[zhanghushu].mima)==6)
       break;
       else
        printf("\n\t\t密码必须是6位,请重新输入！");
     }
     while(1);
     zhanghu[zhanghushu].yue=0;
     zhanghu[zhanghushu].jiaoyishu=0;
     zhanghushu++;
     xianshizhanghu();
}


void xianshizhanghu() /*显示账户函数来显示所输入的账户*/
{
    int i;
    for(i=0;i<zhanghushu;i++)
    {
    printf("\n\n\t帐号\t姓名\t身份证\t\t密码\t余额\n");
    printf("\t%s\t%s\t%s\t%s\t%.2f\n",zhanghu[i].zhanghao,zhanghu[i].xingming,zhanghu[i].shenfenzheng,zhanghu[i].mima,zhanghu[i].yue);
    system("pause");
    }
}

void denglu() /*登录函数*/
{

    char zhanghao[12],mima[7];
    int i=0;
    int mimacishu=1;
    printf("\n\t\t请输入帐号:");
    scanf("%s",zhanghao);
    while(strcmp(zhanghao,zhanghu[i].zhanghao)!=0&&i<zhanghushu)
    i++; /**/
    if(i==zhanghushu)
    return;

        do
    {
        printf("\n\t\t请输入密码:");
    scanf("%s",mima);

        
        if(strcmp(mima,zhanghu[i].mima)!=0)
        {
            
            if(mimacishu==3)
            {
                printf("你已输入错误三次，你不能在输.");
                system("pause");
                return;
            }
            else
            {
                printf("密码错误请重新输入:");
            
            mimacishu++;
            }
        }
        else
        break;
    }
    while(1);
    for(;;)
    {
        switch(menu()) /*选择判断*/
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
void baocunshuju()/*保存数据*/
{
  int i,j;
  FILE *fp;
  char filename[20];
  printf("\t\t\t将数据保存到一个文本文件中\n");/*输入文件名*/
  printf("\t\t\t请输入文件名");
  fflush(stdin);
  scanf("%s",filename);
  if((fp=fopen(filename,"w"))==NULL)/*打开文件*/
  {
    printf("无法创建此文件\n");
    system("pause");
    return;
  }
  fprintf(fp,"%d\n",zhanghushu);/*循环写入数据*/
   printf("\t帐号\t\t姓名\t\t身份证\t\t密码\t余额\t交易数");
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
  printf("\n\n\n\t请输入欲读入数据的文件名:\n");
  fflush(stdin);
  gets(filename);
    if(strlen(filename)==0)
      return;
    else
      if((fp=fopen(filename,"r"))==NULL)/*打开文件*/
      {
        printf("无法打开此文件\n");
        system("pause");
        return;
      }
      else
      {
       printf("\t\t成功打开文件.\n");
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
      printf("\n\n\t=================  欢迎使用 XXX银行ATM ==================\n\n");
      printf("\t=====================请选择服务=====================\n");
      printf("\t*                                                  *\n");
      printf("\t*    1  实时存款                   2   取款服务    *\n");
      printf("\t*                                                  *\n");
      printf("\t*    3  转账服务                   4   查询        *\n");
      printf("\t*                                                  *\n");
      printf("\t*    5  修改密码                   6   退出        *\n");
      printf("\t*                                                  *\n");
      printf("\t====================================================\n");
      printf("\t\t\t请作出选择(1-7):");
      c=getchar(); /*读入选择*/
      system("pause");
    }
    while(c<'1'||c>'7');
    return(c-'0'); /*c变为空后返回重新选择*/
}

void cunkuan() /*存款函数*/
{
    float cunkuanjine;/*输入的存款金额*/
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
    printf("请输入存款金额(存款金额必须大于0,不超过10000,必须是100元的面额\n");
    scanf("%f",&cunkuanjine); 
    if(cunkuanjine<=0||cunkuanjine>1000||(int)cunkuanjine%100!=0)
    {
        printf("金额不符合要求,请重新选择");
        return;
    }
    else
    {
       k=zhanghu[j].jiaoyishu;
        strcpy(zhanghu[j].jiaoyi[k].shijian,t);
        strcpy(zhanghu[j].jiaoyi[k].leixing,"存");
        zhanghu[j].jiaoyi[k].jine=cunkuanjine;
        zhanghu[j].yue+=cunkuanjine;
        zhanghu[j].jiaoyi[k].yue=zhanghu[j].yue;
        zhanghu[j].jiaoyishu++;
        printf("\n\\t\t\t您本次存了%.2f元\n",cunkuanjine);
        printf("\n\\t\t\t您的余额为%.2f元\n",zhanghu[j].yue);
        printf("\n时间为:%s\n",zhanghu[j].jiaoyi[k].shijian);
        printf("\n类型为:%s\n",zhanghu[j].jiaoyi[k].leixing);
        system("pause");
    }

}

void qukuan()   /*取款函数*/
{
    int k;/*交易下标*/
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
    printf("     取款服务   \n");
      printf("\t=====================请选择服务=====================\n");
      printf("\t*                                                  *\n");
      printf("\t*    1  100                         2   200        *\n");
      printf("\t*                                                  *\n");
      printf("\t*    3  500                         4   1000       *\n");
      printf("\t*                                                  *\n");
      printf("\t*    5  其他金额                    6   返回主菜单 *\n");
      printf("\t*                                                  *\n");
      printf("\t====================================================\n");
    scanf("%f",&qukuanjine);
    if(qukuanjine<=0||qukuanjine>10000||(int)qukuanjine%100!=0)
    {
        printf("金额不符合要求,请重新选择");
        return;
    }
       
         else
        if(zhanghu[j].yue<qukuanjine)
        {
            printf("你的账户余额不足,不能完成这项操作。");
        return;
        }
   
       {
        k=zhanghu[j].jiaoyishu;
        strcpy(zhanghu[j].jiaoyi[k].shijian,t);
        strcpy(zhanghu[j].jiaoyi[k].leixing,"取");
        zhanghu[j].jiaoyi[k].jine=qukuanjine;
        zhanghu[j].yue-=qukuanjine;
        zhanghu[j].jiaoyi[k].yue=zhanghu[j].yue;
        zhanghu[j].jiaoyishu++;
        printf("\n\\t\t\t您本次取款%.2f元\n",qukuanjine);
        printf("\n\\t\t\t您的余额为%.2f元\n",zhanghu[j].yue);
        printf("\n时间为:%s\n",zhanghu[j].jiaoyi[k].shijian);
        printf("\n类型为:%s\n",zhanghu[j].jiaoyi[k].leixing);
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
     printf("请输入你要转入的帐号:");
     scanf("%s",zhuanzhangzhanghao);
     while(strcmp(zhanghu[l].zhanghao,zhuanzhangzhanghao)!=0&&l<zhanghushu)
        l++;
     if(l==zhanghushu)
     {
     printf("你输入的用户不存在！\n");
     system("pause");
        return;
        }
     printf("\n该账户户主姓名为%s\n,是否确认转账Y/N？",zhanghu[j].xingming);
     scanf("\t\t%c",&sign); /*输入判断*/
     if(sign!='y'&&sign!='Y') /*判断*/
        return;
    else
        {
     do
     {
        printf("\n请输入转账金额(大于100不超过5000):");
        scanf("%f",&zhuanzhangjine);
        if(zhuanzhangjine<100||zhuanzhangjine>5000)
        {
            printf("输入金额不对,请重新输入!");
            system("pause");
            return;
        }
        if(zhanghu[j].yue<=0||zhanghu[j].yue<zhuanzhangjine)
          {
                printf("账户余额不足\n");
                system("pause");
                return;
            }
          else
            {
                k=zhanghu[j].jiaoyishu;
                strcpy(zhanghu[j].jiaoyi[k].shijian,t);
                strcpy(zhanghu[j].jiaoyi[k].leixing,"转账");
                zhanghu[j].jiaoyi[k].jine=zhuanzhangjine;
                zhanghu[j].yue-=zhuanzhangjine;
                zhanghu[j].jiaoyi[k].yue=zhanghu[j].yue;
                zhanghu[j].jiaoyishu++;

                printf("\n\t\t你本次转了%0.2f元\n",zhuanzhangjine);
                printf("\n\t\t你的余额为%0.2f元\n",zhanghu[j].yue);
                printf("\n\t\t时间为:%s\n",zhanghu[j].jiaoyi[k].shijian);
                printf("\n\t\t类型为:%s\n",zhanghu[j].jiaoyi[k].leixing);
                system("pause");
            }
     }while(0);
     }
        
    printf("\n\n\t\t转账成功\n\n");
    system("pause");
} 

void xiugaimima() /*修改密码函数*/
{
 char mima1[7],mima2[7];
  do
    {
     do
        { 
            printf("\n\n\n\t\t请输入密码:");
            scanf("%s",mima1);
            if(strlen(mima1)==6)
            break;
            else
            printf("\n\n\t\t密码必须是6位,请重新输入！");
        }while(1);
         do
        {
            printf("\n\n\n\t\t请确认密码:");
            scanf("%s",mima2);
            if(strlen(mima2)==6)
            break;
            else
            printf("输入密码必须是6位请输入密码:");
        } while(1);
    if(strcmp(mima1,mima2)==0 ) /*判断第二次输入的密码是否与第一次的一致*/
         break;
     else
         printf("\n\n\t\t*|两次密码不相等请重新输入:\n\n");
    } while(1);
    strcpy(zhanghu[j].mima,mima1);
    printf("\n\n\t\t修改密码成功\n\n");
    getch();
    system("pause");
}

int chaxuncaidan();/*查询菜单*/
void chaxunyue();
void chaxuncunkun();
void chaxunqukun();
void chaxunzhuangzhan();
void chaxunjiaoyi();
void duqushuju();

void chaxun() /*查询函数*/
{
 for(;;)
    {
        switch(chaxuncaidan()) /*选择判断*/
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

int chaxuncaidan()/*菜单函数*/
{
    char c;
    do
    {
        system("cls"); /*每次选择运行前清屏*/
        printf("\t\t *********************查询菜单*******************\n\n"); /*菜单选择*/
        printf("\t\t *| 1. 查询余额|\n");
        printf("\t\t *| 2. 查询存款记录|\n");
        printf("\t\t *| 3. 查询取款记录|\n");
        printf("\t\t *| 4. 查询转账记录|\n");
        printf("\t\t *| 5. 查询交易情况|\n");
        printf("\t\t *| 0. 退出 |\n");
        printf("\t\t ************************************************\n");
        printf("\t\t\t请作出选择(0-5):");
        c=getchar(); /*读入选择*/
    }
    while(c<'0'||c>'5');
    return(c-'0'); /*c变为空后返回重新选择*/
}   
void chaxunyue()/*查询余额函数*/
{
     printf("\n\t您的余额为%.2f元\n",zhanghu[j].yue);
    system("pause");
}
void chaxuncunkun() /*查询存款函数*/
{
 int i;
    printf("\t\t *************存款查询记录****************\n\n");
    printf("\t帐号\t姓名\t交易类型\t交易时间\t\t金额\t余额\n");
    for(i=0;i<zhanghu[j].jiaoyishu;i++)
        {
            if(strcmp(zhanghu[j].jiaoyi[i].leixing,"存")==0)
            printf("\t%s\t%s\t%s\t%s\t%.2f\t%.2f\n\n",zhanghu[j].zhanghao,
            zhanghu[j].xingming,zhanghu[j].jiaoyi[i].leixing,
            zhanghu[j].jiaoyi[i].shijian,zhanghu[j].jiaoyi[i].jine,
            zhanghu[j].jiaoyi[i].yue);
            else;
        }
        system("pause");
}
void chaxunqukun() /*查询取款函数*/
{
 int i;
    printf("\t\t *************取款查询记录****************\n\n");
    printf("\t帐号\t姓名\t交易类型\t交易时间\t\t金额\t余额\n");
    for(i=0;i<zhanghu[j].jiaoyishu;i++)
        {
            if(strcmp(zhanghu[j].jiaoyi[i].leixing,"取")==0)
            printf("\t%s\t%s\t%s\t%s\t%.2f\t%.2f\n\n",zhanghu[j].zhanghao,
            zhanghu[j].xingming,zhanghu[j].jiaoyi[i].leixing,
            zhanghu[j].jiaoyi[i].shijian,zhanghu[j].jiaoyi[i].jine,
            zhanghu[j].jiaoyi[i].yue);
            else;
        }
        system("pause");
}
void chaxunzhuangzhan()/*查询转账函数*/
{
 int i;
    printf("\t\t *************取款查询记录****************\n\n");
    printf("\t帐号\t姓名\t交易类型\t交易时间\t\t金额\t余额\n");
    for(i=0;i<zhanghu[j].jiaoyishu;i++)
        {
            if(strcmp(zhanghu[j].jiaoyi[i].leixing,"转")==0)
            printf("\t%s\t%s\t%s\t%s\t%.2f\t%.2f\n\n",zhanghu[j].zhanghao,
            zhanghu[j].xingming,zhanghu[j].jiaoyi[i].leixing,
            zhanghu[j].jiaoyi[i].shijian,zhanghu[j].jiaoyi[i].jine,
            zhanghu[j].jiaoyi[i].yue);
            else;
        }
        system("pause");
}
void chaxunjiaoyi()  /*查询交易函数*/
{
   int i;
    printf("\t\t *************取款查询记录****************\n\n");
    printf("\t帐号\t姓名\t交易类型\t交易时间\t\t金额\t余额\n");
    for(i=0;i<zhanghu[j].jiaoyishu;i++)
        {

            printf("\t%s\t%s\t%s\t%s\t%.2f\t%.2f\n\n",zhanghu[j].zhanghao,
            zhanghu[j].xingming,zhanghu[j].jiaoyi[i].leixing,
            zhanghu[j].jiaoyi[i].shijian,zhanghu[j].jiaoyi[i].jine,
            zhanghu[j].jiaoyi[i].yue);

        }
        system("pause");
}


 void main() /*主函数*/
{    system("graftabl 936");
    duqushuju();
    for(;;)
    {
        switch(caidan()) /*调用主菜单根据主菜单的返回值来做选择*/
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
        printf("\t\t\t欢迎使用ATM!\n"); /*结束程序*/
        printf("\t\t\t");
        system("pause"); /*使程序暂停*/
        exit(0);
        }
  }
}
