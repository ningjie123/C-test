#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fopen1(FILE **file_out,char* name,int outs)
{
int i,len;
char ** names;
char c;
len = strlen(name);
names = (char **)calloc(outs+1,sizeof(char *));
for(i=1;i<=outs;i++)
{
	names[i] = (char *)calloc(20,sizeof(char));
	strcpy(names[i],name);
	names[i][len-3] = '-';
	c = (char)i + '0';
	names[i][len-2] = c;
	names[i][len-1] = '.';
	names[i][len] = 'f';
	names[i][len+1] = 'a';
	names[i][len+2] = 's';
	names[i][len+3] = 't';
	names[i][len+4] = 'a';
	file_out[i] = fopen(names[i],"w");
	free(names[i]);
}
free(names);
return 0;
}

int fopen2(FILE **file_out,char* name,int outs)
{
int i,len;
char ** names;
char c;
len = strlen(name);
names = (char **)calloc(outs+1,sizeof(char *));
for(i=1;i<=outs;i++)
{
	names[i] = (char *)calloc(20,sizeof(char));
	strcpy(names[i],name);
	names[i][len-3] = '-';
	c = (char)i + '0';
	names[i][len-2] = c;
	names[i][len-1] = '.';
	names[i][len] = 'f';
	names[i][len+1] = 'a';
	names[i][len+2] = 's';
	names[i][len+3] = 't';
	names[i][len+4] = 'a';
	file_out[i] = fopen(names[i],"a");
	free(names[i]);
}
free(names);
return 0;
}
