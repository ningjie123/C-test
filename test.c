#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test.h"
/*typedef struct REGION
{
    int start[100];
    int end[100];
    char flag;
}region;*/
region p;
int main()
{
    char file_name[]="./sequence.gb";
   // struct REGION p;
    read_region(file_name,&p);
    
    int i;
    for (i=0;(p.end[i]!= 0);i++)
        printf("%d---start:%d; end:%d\n",i,p.start[i],p.end[i]);
    
    return 0;
}
