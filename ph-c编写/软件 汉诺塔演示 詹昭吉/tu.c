#include<stdio.h>
#include<graphics.h>
#include<conio.h>
void main()
{
    int driver=DETECT, mode=0;
    registerbgidriver(EGAVGA_driver);
    initgraph(&driver,&mode,"");

    setbkcolor(7);
    setwritemode(1);
    setcolor(5);
    setlinestyle(SOLID_LINE,1,3);
    line(150,100,150,400);
    line(100,400,200,400);
    line(300,100,300,400);
    line(450,100,450,400);
    line(250,400,350,400);
    line(400,400,500,400);
    getch();
}
