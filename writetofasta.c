//write th sequence into fasta file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writetofasta(char *sequence,FILE *fp)
{
  	int i,j=0;
	while(1)
	{
    		i=0;
    		for(i;i<71;++i)
		{
      			if(sequence[j]>='a'&&sequence[j]<'z')
			{
         			sequence[j]=sequence[j]-'a'+'A';
         		}
      			fputc(sequence[j++],fp);
    		}
    		fputc('\n',fp);
    		if (sequence[j] == '\0') break;
  	}
return;
}
  

