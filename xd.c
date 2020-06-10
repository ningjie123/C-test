#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define buffer_size 1000//Maximum of  length
int start[2],end[2];//"start..end"

void get_cols(char *file_path)
{  char col[buffer_size];
  FILE *file=fopen(file_path,"r");
  char temp_data[buffer_size];
  fget(temp_data,buffer_size,file);//the content of each line
  if (strlen(temp_data) <= 2) continue; //Skip blank lines
  char *p;
  p=strtok(temp_data,"\t"); //Use spaces as separators
  if(!strcmp(p,"CDS"))
    {  p = strtok(NULL, "\t");
      strcpy(col[buffer_size], p);
      if(strlen(p)<12) //Only one interval
	sscanf(delete(col), "%d..%d", &start[1], &end[1]);
    }

  fclose(file);
}

char* delete(char string[])
{
  int i,j;
  for(i=j=0;*(string+i)!='\0';i++)
    {
      if(string[i]!='<'&&string[i]!='>')
        string[j++]=string[i];
    }
  return string;
}
