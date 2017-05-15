#include<stdio.h>
#include <stdlib.h>
int main()
{
    char key;
    int i=0;
    while(1)
    {

        if(bioskey(1))
        {
        key = bioskey(0);
        if(key=='p')
        {
            printf("gg__");
        }
        }
        printf("ph__");
        sleep(1);
    }

}
