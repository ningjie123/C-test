#include <stdio.h>
#include <string.h>

int strstart(char *s,char *t)
{
	int lent,i=0,j=0;
	lent = strlen(t);
	while(i < lent)
	{
		if(s[i] == t[j])
		{
			i++;
			j++;
			if(j == lent) return 1;
		}
		else return 0;
	}
	return 0;
}

int strtotal(char *total,char *str1,char *str2)
{
	int lenall,len1,len2,i=0;
	len1 = strlen(str1);
	len2 = strlen(str2);
	for(i=0;i<len1;i++)
	{
		total[i] = str1[i];
	}
	for(i=0;i<len2;i++)
	{
		total[i+len1] = str2[i];
	}
	total[len1+len2] = '\n';
	return 0;
}

int first_line(char *filename,char *firstline)
{
	FILE *file_in;
	file_in = fopen(filename,"r");
	int i=0,j=0,temp=0,lab[2];
	char str[10][200],definition[600],accession[200];
	for(i=0;i<10;i++)
	{
		fgets(str[i],200,file_in);
		if(strstart(str[i],"DEFINITION") == 1)lab[0] = i;
		else	if(strstart(str[i],"ACCESSION") == 1)lab[1] = i;
	}
	i=0;
	while(str[lab[0]][i+10] != '\n')
	{
		definition[i] = str[lab[0]][i + 10];
		i++;
	}
	temp = i;
	for(j=lab[0]+1;j<lab[1];j++)
	{
		i=0;
		while(str[j][i] != '\n')
		{
			definition[temp + i] = str[j][i];
			i++;
		}
		temp += i;
	}
	i = j = 0;
	while(str[lab[1]][i + 9] != '\n')
	{	
		accession[i] = str[lab[1]][i + 9];
		i++;
	}
	strtotal(firstline,accession,definition);
	return 0;
}



int main()
{
	char firstline[1000];
	memset(firstline,1000,'\0');
	first_line("test.gb",firstline);
	printf("%s",firstline);
	return 0;
}
