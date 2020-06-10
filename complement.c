#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern region
/*struct Region
{
    int start[10];
    int end[10];
    char flag;
};*/

//读文件过程中调用，遇到CDS后执行
int is_complement(const char *s)
{
    int i=0,j,k;
    char a[10] = "complement";
    if (strlen(s) < 10) return 0; //compare length
    for ( i=0;((i+10) <= strlen(s));i++ )
        if (s[i] == a[0])  //overlap
            {
                j=i;
                k=0;
                while ((k < 10) && (s[j] == a[k])) {j++;k++;}
                if (k == 10) {return j;}
            }
    return 0;
}


//命令行参数file
void read_region(char f[],struct REGION region_c)
{
    int i=0;
    FILE *ifp_a;
    char c;
    int newline=1;
    int m=0,j=0;
    char a[100];
    int k,start=0,end=0;
    if ((ifp_a = fopen(f,"r")) == NULL) {printf("open file error!\n");exit(1);}
    int mark=0;
    while ((c=getc(ifp_a)) != EOF)
    {
        if ((c!='\n')&&(mark==-1)) continue;
        if (c=='\n') 
        {
            newline = 1;
            mark=0;
            continue;
        }
        if ((newline == 1) && (mark != 3))
        {
            if ((mark == 0 ) && (isspace(c))) continue;
            if (!isspace(c))
            {       
                
                if ((c == 'C')&&(mark==0)) {++mark;continue;} 
                else 
                if ((mark==1) && (c == 'D')){mark++;continue;} 
                else 
                if ((mark==2) && (c == 'S')){mark++;continue;} 
                else {mark=-1;newline=0;continue;}
            }          
        }
        if (mark==3)
        {
            newline=0;
            if (isspace(c)) continue;    
            if (c !=')')
                {
                    a[j]=c;
                    j++;
                }
            else 
                {
                    a[j]='\0';
                    /* for(j=0;a[j]!='\0';++j)
                        printf("%c",a[j]);
                    printf("\n"); */  //use for quiz
                    if ((j=is_complement(a))!=0) 
                    {
                        region_c.flag='c';
                        for (k=j;(a[k]!='.');k++)
                            if ((a[k]>='0')&&(a[k]<='9'))
                                start=10*start+(a[k]-'0');
                        for (;(a[k]!='\0');k++)
                            if ((a[k]>='0')&&(a[k]<='9'))
                                end=10*end+(a[k]-'0');
                        region_c.start[m]=start;
                        region_c.end[m]=end;

                        m++;
                        start=0;
                        end=0;
                    }  
                    i=0;
                    j=0;
                }
            
        }       
    }
    region_c.start[m]=0;
    region_c.end[m]=0;
    fclose(ifp_a);
}
