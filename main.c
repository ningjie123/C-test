#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libgenbank.h"
//#include "libgenbank.so"
//#include "libfasta.so"
/*struct REGION{
	char flag;
	int start[100];
	int end[100];
};*/
region region1,region2,region3;
int main(int argc,char **argv)
{
if(argc != 2)
{
	printf("error: Please enter like: trans file_in!\n");
	exit (1);
}
FILE* file_in;
file_in = fopen(argv[1],"r");
if(file_in == NULL)
{
	printf("error: Fail to open the files!\n");
	exit (2);
}
int i=0,outs=0;
char str_temp[600];
while(fgets(str_temp,600,file_in) != NULL)
{
	if(strstart2(str_temp,"CDS") == 1) outs++;
}
fclose(file_in);
printf("done1\n");
FILE** file_out;
file_out = (FILE **)calloc(outs,sizeof(FILE *));
fopen1(file_out,argv[1],outs);
printf("done2\n");
char firstline[1000];
memset(firstline,1000,'\0');
first_line(argv[1],firstline);
printf("%s",firstline);
printf("done3\n");
for(i=0;i<outs;i++) fputs(firstline,file_out[i]);
//read_region(arvg[1],&region1);
int count;
char sequence[10000];
count = get_join(argv[1],&region3);
printf("done4\n");
file_in = fopen(argv[1],"r");
getcds(file_in,sequence,&region3);
//fclose(file_in);
//get_cols(argv[1],&region1);
//file_in = fopen(argv[1],"r");
//getcds(file_in,sequence,&region1);


return 0;
}
