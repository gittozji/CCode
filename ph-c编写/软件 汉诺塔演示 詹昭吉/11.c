#include<stdio.h>
#include<graphics.h>
#include<conio.h>
void main()
{

    /***ͼ������******/
    int driver = DETECT, mode = 0;
    registerbgidriver(EGAVGA_driver);
    initgraph(&driver, &mode, "");




    setbkcolor(7);            /*���ñ�����ɫ*/
    setwritemode(1);          /*�����ߵ�ģʽ*/
    setcolor(BLUE);
    setlinestyle(SOLID_LINE,1,3);
    rectangle(280,350,320,390);  /*������*/
    rectangle(270,340,330,350);
    rectangle(290,320,310,340);
    rectangle(270,390,330,400);
    setcolor(5);
    line(290,350,290,390);       /*����*/
    line(300,300,300,320);
    line(300,350,300,390);
    line(310,350,310,390);
    line(285,300,315,300);
    getch();
    closegraph();
}
