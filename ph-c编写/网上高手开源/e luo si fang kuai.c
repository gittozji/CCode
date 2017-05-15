/*����˹����*/
#include "stdio.h"
#include "dos.h"
#include "graphics.h"
#include "stdlib.h"
#define TIMER 0x1c      /*ʱ���жϵ��жϺ�*/
/*����ͼ����ʾ��������Ͻ�����*/
#define SHANG 4
#define ZUO 10
/*������һ��������ʾ��������Ͻ�����*/
#define ZUO1 14
#define SHANG1 5
#define ESC 0x011b     /*�˳���*/
#define ENTER 0x1c0b
#define LEFT 0x4b00
#define RIGHT 0x4d00
#define UP 0x4800       /*���μ�*/
#define DOWN 0x5000     /*���ټ�*/
int TimerCounter=0;     /*��ʱ������ÿ������8*/
/*ָ��ԭ��ʱ���жϴ��������ڵ��жϴ�����*/
void interrupt(*oldhandler)();  
/*�µ�ʱ���жϴ�����*/
void interrupt newhandler()
{TimerCounter++;
 oldhandler();
}
/*�����µ�ʱ���жϴ������*/
void SetTimer(void interrupt(*IntProc)())
{oldhandler=getvect(TIMER);
 disable();  /*�����µ�ʱ���жϴ������ʱ����ֹ�����ж�*/
 setvect(TIMER,IntProc);
 enable();  /*�жϿ���*/
}
/*�ָ�ԭ�е�ʱ���жϴ������*/
void KillTimer()
{disable();
 setvect(TIMER,oldhandler);
 enable();
}
int speed,score,level;
struct shape
{int xy[8],next;  /*xy[0]~~xy[8]ָ4��С�����������꣬nextָ�˷�����κ�Ϊ�ĸ�����*/
};
struct shape shapes[19]={{0,1,1,1,1,2,2,2,1},
                         {1,1,0,2,1,2,0,3,0},
                         {1,1,2,1,0,2,1,2,3},
                         {0,1,0,2,1,2,1,3,2},
                         {1,1,1,2,1,3,2,3,5},
                         {2,1,0,2,1,2,2,2,6},
                         {0,1,1,1,1,2,1,3,7},
                         {0,1,1,1,2,1,0,2,4},
                         {1,1,1,2,1,3,0,3,9},
                         {0,1,1,1,2,1,2,2,10},
                         {1,1,2,1,1,2,1,3,11},
                         {0,1,0,2,1,2,2,2,8},
                         {0,1,1,1,2,1,1,2,13},
                         {0,1,0,2,1,2,0,3,14},
                         {1,1,0,2,1,2,2,2,15},
                         {2,1,1,2,2,2,2,3,12},
                         {1,1,1,2,1,3,1,4,17},
                         {0,1,1,1,2,1,3,1,16},
                         {1,1,2,1,1,2,2,2,18},
                         };
void initgraphics();
/*�˺�������x��y���괦��ʾ����Ϊnow�ķ��飬wayΪ1����ʾ��Ϊ0�����*/
void draw_block(int x,int y,int now,int way);
void draw_little_block(int x,int y);
int change(int *x,int *y,int key);
int check(int x,int y,int now);
void kill_line(int y);                                              
int x0=3,board[10][20],now,now1,flag;/*now Ϊ��ǰ��������࣬now1Ϊ������ʾ�ķ��������*/
main()
{int i,j,key,speed=0,k;
 randomize();
 initgraphics();
 SetTimer(newhandler);
 now=random(19);
 while(!flag)
  {i=x0;
   now1=random(19);
   draw_block(ZUO1,SHANG1,now1,1);
   for(j=0;j<=19;j++)
   {if(check(i,j,now))
 draw_block(i,j,now,1);
    else if(j==0)
  flag=1;
  else break;
    while(1)
 {if(speed==0)
  {if(TimerCounter>18)
   {TimerCounter=0;
    break;
   }
  }
  else {if(TimerCounter>18/9)
   {TimerCounter=0;
    break;
   }
  }
  if(bioskey(1))
  {key=bioskey(0);
   if(change(&i,&j,key))
   flag=1;
  }
 }
   if(flag==1)
  break;
   draw_block(i,j,now,0);
   }
  draw_block(ZUO1,SHANG1,now1,0);
  draw_block(i,j-1,now,1);
  for(k=0;k<=6;k+=2)
 board[i+shapes[now].xy[k]][j-2+shapes[now].xy[k+1]]=1;
  now=now1;
  kill_line(j);/*��ȥ�к���*/
  }
closegraph();
KillTimer();
}
void initgraphics()
{int gdriver=VGA,i,j;
 int gmode=VGAHI;
 initgraph(&gdriver,&gmode,"");
 setcolor(BLUE);
 setlinestyle(0,0,3);
 rectangle(158+16,78,306,386);
 rectangle(23*16-2,10*16-2,28*16+2,14*16+2);
 setlinestyle(0,0,1);
 for(i=0;i<10;i++)
 for(j=0;j<20;j++)
  {if(i==0||i==9||j==19)
   board[i][j]=1;
   else board[i][j]=0;
  }
}
void draw_block(int x,int y,int now,int way)
{int x1=x+ZUO,y1=y+SHANG;
 int i;
 if(way==1)
 setfillstyle(1,RED);
 else
 setfillstyle(1,BLACK);
 for(i=0;i<=6;i+=2)
 {draw_little_block(x1+shapes[now].xy[i],y1+shapes[now].xy[i+1]);
 }
}
int check(int x,int y,int now)
{int x1=x+ZUO,y1=y+SHANG;
 int x2,y2,i;
 for(i=0;i<8;i+=2)
 {x2=x1+shapes[now].xy[i];
  y2=y1+shapes[now].xy[i+1];
  if(x2<=19&&x2>=10&&y2<=23&&y2>=5&&(board[x2-10][y2-5]==0))
  continue;
  else break;
 }
 if(i==8)
 return 1;
 else  return 0;
}
void draw_little_block(int x,int y)
{bar(x*16+1,y*16+1,x*16+15,y*16+15);
}
int change(int *x,int *y,int key)
{if(key==LEFT&&(check(*x-1,*y,now)))
 {draw_block(*x,*y,now,0);
  (*x)--;
  draw_block(*x,*y,now,1);
 }
 else if(key==RIGHT&&check(*x+1,*y,now))
  {draw_block(*x,*y,now,0);
   (*x)++;
   draw_block(*x,*y,now,1);
  }
 else if(key==DOWN&&check(*x,*y+1,now))
   {draw_block(*x,*y,now,0);
    (*y)++;
    draw_block(*x,*y,now,1);
    speed=1;
   }
  else if(key==UP&&check(*x,*y,shapes[now].next))
    {draw_block(*x,*y,now,0);
     now=shapes[now].next;
     draw_block(*x,*y,now,1);
    }
   else if(key==ESC)
     {return 1;
     }
 return 0;
}
void kill_line(int y)
{int k,b=0,i;
 for(y-=1;y<=18;y++)
 {for(k=1;k<=8;k++)
  {if(!board[k][y])
   break;
   if(k==8)
   {for(k=1;k<=8;k++)
    {setfillstyle(1,BLACK);
     draw_little_block(ZUO+k,y+SHANG+1);
    }
    b++;
    i=y;
   }
  }
 }
 if(b>0)
 {for(;i>=1;i--)
  {for(k=1;k<=8;k++)
   {if((i-b)>0)
    {board[k][i]=board[k][i-b];
     if(board[k][i]==1)
    {setfillstyle(1,RED);
     draw_little_block(k+ZUO,i+SHANG+1);
     setfillstyle(1,BLACK);
     draw_little_block(k+ZUO,i+SHANG-b+1);
    }
    }
   }
  }
 }
}

