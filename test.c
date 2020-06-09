#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Region
{
    int start[10];
    int end[10];
    char flag;
};

int main()
{
    char file_name[]=".\\sequence.gb";
    struct Region p;
    read_region(file_name,&p);
    
    int i;
    for (i=0;(p.end[i]!= 0);i++)
        printf("%d---start:%d; end:%d\n",i,p.start[i],p.end[i]);
    
    return 0;
}
