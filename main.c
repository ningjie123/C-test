#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libgenbank.h"
//#include "libfasta.so"

int main(int argc,char **argv)
{
if(argc != 2)
{
	printf("error: Please enter like: trans file_in!\n");
	exit (1);
}
FILE* file_in;
file_in = fopen(argv[1],"r");
int i=0,outs;
char str_temp[600];
while(fgets(str_temp,600,file_in) != NULL)
{
	if(strstart2(str_temp,"CDS") == 1) outs++;
}
fclose(file_in);
FILE** file_out;
file_out = (FILE **)calloc(outs,sizeof(FILE *));
fopen1(file_out,argv[1],outs);
if(file_in == NULL)
{
	printf("error: Fail to open the files!\n");
	exit (2);
}
char firstline[1000];
first_line(file_in,firstline);
for(i=0;i<outs;i++)	fputs(firstline,file_out[i]);
//read_region(arvg[1],&region1);




return 0;
}
