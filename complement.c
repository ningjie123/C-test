#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100;

//读文件过程中调用，遇到CDS后执行
bool iscomplement(const char *s)
{
    int i=0,j,k;
    char a[10] = "complement";
    if (strlen(s) < 10) return false; //compare length
    for ( i=0;((i+10<=strlen(s));i++ )
        if (s[i] == a[0])  //overlap
            {
                j=i;
                k=0;
                while ((k < 10) && (s[j] == a[k])) {j++;k++;}
                if (k == 10) {return true;}
            }
    return false;
}


//命令行参数file
int **read(char *file[])
{
    int **b =(int **)malloc(MAX*sizeof(int *));
    for (int i=0;i<MAX;i++)
        b[i]=(int *)malloc(2*sizeof(int));
    FILE *ifp_a;
    char c;
    int newline=0;
    int i=0,m=0,j=0;
    char a[100];
    if ((ifp_a = fopen(*file,"r")) == NULL) {printf("open file error!\n");exit(1);}

    while ((c=getc(ifp_a)) != EOF)
    {
        if (c=='\n') {newline=1;continue;}
        if (newline == 1) 
            if (c != ' ')
            {        
                if ((i==0) && (c == 'C')){i++;continue;} 
                else {newline=0;i=0;}
                if ((i==1) && (c == 'D')){i++;continue;} 
                else {newline=0;i=0;}
                if ((i==2) && (c == 'S')){i++;continue;} 
                else {newline=0;i=0;}
            }
        if (i==3)
        {
            newline=0;
            while (c != ' ')
            {
                if ((c !=')'))
                {
                    a[j]=c;
                    j++;
                }
                else 
                {a[j]='\0';
                if (iscomplement(a)) 
                    {
                        int k,start=0,end=0;
                        for (k=0;(a[k]!='.');k++)
                            if ((a[k]>='0')&&(a[k]<='9'))
                                start=10*start+(a[k]-'0');
                        for (;(a[k]!=')');k++)
                            if ((a[k]>='0')&&(a[k]<='9'))
                                end=10*end+(a[k]-'0');
                        b[m][0]=start;
                        b[m][0]=end;
                        start=0;
                        end=0;
                    }  
                i=0;
                break;}
            }
        }       
    }
    return b;
}