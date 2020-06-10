#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fopen1(FILE **file_out,char* name,int outs)
{
int i,len;
char ** names;
char c;
len = strlen(name);
names = (char **)calloc(outs,sizeof(char *));
for(i=0;i<outs;i++)
{
	names[i] = (char *)calloc(20,sizeof(char));
	strcpy(names[i],name);
	names[i][len] = '-';
	c = (char)i + '0';
	names[i][len+1] = c;
	file_out[i] = fopen(names[1],"w");
	free(names[i]);
}
free(names);
return 0;
}
