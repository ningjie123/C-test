#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libgenbank.h"
#include "libfasta.h"
//#include "libgenbank.so"
//#include "libfasta.so"
/*struct REGION{
	char flag;
	int start[100];
	int end[100];
};*/
//region region1,region2,region3;
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
int i=0,outs=0,j=0,join_count=0;
char str_temp[600];
while(fgets(str_temp,600,file_in) != NULL)
{
	if(strstart2(str_temp,"CDS") == 1) outs++;
	if(strstart2(str_temp,"CDSjoin") == 1) join_count++;
}
fclose(file_in);
region *regions;
regions = (region *)calloc(outs+1,sizeof(region));
FILE** file_out;
file_out = (FILE **)calloc(outs+1,sizeof(FILE *));
fopen1(file_out,argv[1],outs);
char firstline[1000];
memset(firstline,1000,'\0');
first_line(argv[1],firstline);
printf("%s",firstline);
for(i=1;i<=outs;i++) fputs(firstline,file_out[i]);
for(i=1;i<=outs;i++) fclose(file_out[i]);
fopen2(file_out,argv[1],outs);
int count;
char **sequence;
sequence = (char **)calloc(outs+1,sizeof(char *));
for(i=1;i<=outs;i++)
{
 	sequence[i] = (char *)calloc(10000,sizeof(char));
	memset(sequence[i],10000,'\0');
}
for(i=1;i<=join_count;i++)
{
	count = get_join(argv[1],&regions[i],i,sequence[i]);
	writetofasta(sequence[i],file_out[i]);
//	printf("%s\n",sequence[i]);
}
//file_in = fopen(argv[1],"r");
//getcds(file_in,sequence,&region3);
//fclose(file_in);
//get_cols(argv[1],&region1);
//file_in = fopen(argv[1],"r");
//getcds(file_in,sequence,&region1);
for(i=1;i<=outs;i++) fclose(file_out[i]);
free(file_out);
free(regions);
for(i=1;i<=outs;i++) free(sequence[i]);
free(sequence);
return 0;
}
