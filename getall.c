#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libgenbank.h"
int strstart2(char *s,char *t)
{
	int lent,i=0,j=0,k=0;
	lent = strlen(t);
	char c;
	while(s[i] == ' ') i++;
	while(k < lent)
	{
		if(s[i] == ' ')
		{
			i++;
			continue;
		}
		else	if(s[i] == t[j])
			{
				i++;
				j++;
				k++;
				if(j == lent) return 1;
			}
			else
			{
				i = i - j + 1;
				j = 0;
				k++;
			}
	}
	return 0;
}

int countchar(char *s,char c)
{
	int lens,i,count=0;
	lens = strlen(s);
	for(i=0;i<lens;i++)
	{
		if(s[i] == c) count++;
	}
	return count;
}

int exp_char(char c,int exp)
{
	int i,cc,a;
	a = (int)'0';
	cc = (int)c - a;
	for(i=0;i<exp;i++)
	{
	       	cc = cc * 10;
	}
	return cc;
}

int isbase(char c)
{
	if(c == 'a' || c == 't' || c == 'g' || c == 'c') return 1;
	else return 0;
}

int get_join(char *filename,region* region3,int num,char *sequence)
{

	FILE* file_in;
	char str[400];
	char** s;
	int i=0,j=0,k=0,n=1,line_count=0,lab[3],count=0,flag=0;
	for(i=0;i<3;i++) lab[i] = 0;
	file_in = fopen(filename,"r");
	while(fgets(str,400,file_in) != NULL) line_count++;
	fseek(file_in,0,SEEK_SET);
	s = (char **)calloc(line_count+1,sizeof(char *));
	for(i=1;i<=line_count;i++) s[i] = (char *)calloc(400,sizeof(char));
	for(i=1;i<=line_count;i++)
	{
		fgets(s[i],400,file_in);
		if(strstart2(s[i],"CDSjoin") == 1) 
		{
			flag++;
			if(flag == num) lab[2] = lab[0] = i;
		}
		if(strstart2(s[i],"/") == 1 && lab[2] != 0 && flag == num)
		{
			lab[1] = i;
			break;
		}
	}
	for(i=lab[0];i<lab[1];i++)
	{
		count += countchar(s[i],'.') / 2;
	}
	int *region1,*region2,temp[2];
//	region1 = (int *)calloc(count+1,sizeof(int));
//	region2 = (int *)calloc(count+1,sizeof(int));
	for(i=lab[0];i<lab[1];i++)
	{
		j=0;
		while(s[i][j] != '\n')
		{	
			if(s[i][j] <= '9' && s[i][j] >= '0')
			{
				while(s[i][j] != '.')
				{
					region3->start[n] += exp_char(s[i][j],6 - k);
					k++;
					j++;
				}
				region3->start[n] = region3->start[n] / exp_char('1',7 - k);
				k=0;
				j += 2;
				while(s[i][j] != ',' && s[i][j] != ')')
				{
					region3->end[n] += exp_char(s[i][j],6 - k);
					k++;
					j++;
				}
				region3->end[n] = region3->end[n] / exp_char('1',7 - k);
				k=0;
				n++;
				j--;
			}	
			j++;
		}
	}
	fseek(file_in,0,SEEK_SET);
	for(i=1;i<=line_count;i++)
	{
		fgets(s[i],400,file_in);
		if(strstart2(s[i],"ORIGIN") == 1) lab[0] = i;
		if(strstart2(s[i],"//") == 1) lab[1] = i;
	}	
	fseek(file_in,0,SEEK_SET);
	n=0;
	int start_l,start_c,end_l,end_c,len,tmp=0;
	for(i=1;i<=count;i++)
	{
		fseek(file_in,0,SEEK_SET);
		start_l  = (region3->start[i] / 60) + lab[0] + 1;
		start_c = region3->start[i] % 60;
		end_l = (region3->end[i] / 60) + lab[0] + 1;
		end_c = region3->end[i] % 60;
		for(j=1;j<start_l;j++) fgets(s[j],400,file_in);
		for(j=start_l;j<=end_l;j++)
		{
			tmp = k = 0;
			fgets(s[j],400,file_in);
			if(j == start_l)
			{
				while(s[j][k] != '\n')
				{
					if(isbase(s[j][k]) == 1)
					{
						tmp++;
						if(tmp >= start_c) sequence[n++] = s[j][k];
						k++;
					}
					else k++;
				}
			}
			else	if(j == end_l)
				{
					while(s[j][k] != '\n')
					{
						if(isbase(s[j][k]) == 1)
						{
							tmp++;
							if(tmp <= end_c) sequence[n++] = s[j][k];
							k++;	
						}
						else k++;
					}
				}
				else	while(s[j][k] != '\n')
					{
						if(isbase(s[j][k]) == 1) sequence[n++] = s[j][k++];
						else k++;
					}
		}
	}
	for(i=1;i<=line_count;i++) free(s[i]);
	free(s);
	fclose(file_in);
	return count;
}

/*int main()
{
	int count,i;
	count = get_join("test.gb");
	for(i=1;i<=count;i++) printf("%d\t%d\n",region3.start[i],region3.end[i]);	
	return 0;
}*/
