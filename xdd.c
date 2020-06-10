#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgenbank.h>
char* del(char string[]);
#define buffer_size 1000//Maximum of  length                                    
//"start..end"                                                    

void get_cols(char *file_path)
{  char col[buffer_size];
  char *str;
  FILE *file=fopen(file_path,"r");
  char temp_data[buffer_size];
  while (feof(file) == 0)
    {    fgets(temp_data,buffer_size,file);//the content of each line           
      if (strlen(temp_data) <= 2) continue; //Skip blank lines                  
      char *p;
      p=strtok(temp_data,"\t"); //Use spaces as separators                      
      if(!strcmp(p,"CDS"))
        {  p = strtok(NULL, "\t");
	  if(!strcmp(p,"CDS"))
	    {  p = strtok(NULL, "\t");

	      if(strlen(p)<12) //Only one interval                                  
		str=del(p);
	      sscanf(str, "%d..%d", &region1->start[0], &region1->end[0]);
	    }


	}
      region1.flag='n';
      fclose(file);
    }
  char* del(char *string)
  {
    int i,j;
    for(i=j=0;*(string+i)!='\0';i++)
      {
	if(string[i]!='<'&&string[i]!='>')
	  string[j++]=string[i];
      }
    return string;
  }

