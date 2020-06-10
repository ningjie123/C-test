//Get the sequence from genbank ORIGIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgenbank.h"

#define MAX 200

extern region;

int isbase(char s)
{
  if (s=='a'||s=='t'||s=='c'||s=='g'||s=='A'||s=='T'||s=='C'||s=='G')
     return 1;
  else return 0;
}  

void getcds(FILE fp,char *sequence,region Region)
{
  char buf[MAX];
  int num,i=0,j;
  int left_gap,right_gap,len;
  while(1){
    if(Region.start[i]==0) break;
    fgets(buf,MAX,fp);
    if (strcmp(buf,"ORIGIN")==0){
        fscanf(fp,"%d",num);
        if ( Region.start[i]-num < 60 && Region.start[i]-num >= 0 ){
            int left_gap=Region.start[i]-num+1;
	    while (1){
		char *tmp[MAX];
		fgets(tmp[j++],MAX,fp);
                fscanf(fp,"%d",num);
                if (num > region.end[i]){
		  int right_gap=num-Region.end[i]-1;
		  fgets(buf,MAX,fp);
		  break;
		}
	    }             
	}
    rewind(fp);
    i++;
    }
  }
  int m,n;
  char tmp[MAX][MAX];
  char sequence_tmp[1000];
  for(m=0;m<=i;m++){ 
    for(n=0;tmp[m][n]!='\n';n++){    
	if (isbase(tmp[m][n])){
	    strcat(sequence_tmp,tmp[m][n]);
        }
    }
  }    
  len=strlen(sequence_tmp)-left_gap-right_gap;
  strncpy(sequence,sequence_tmp,len);

  if(Region.flag=='c'){
     int s=0;
     for(s;sequence[s]!='\0';s++){
        if(sequence[s]=='a'||sequence[s]=='A'){
          sequence[s]+=19;
        }
 	if(sequence[s]=='t'||sequence[s]=='T'){
	  sequence[s]-=19;
	}
	if(sequence[s]=='c'||sequence[s]=='C'){
	  sequence[s]+=4;
	}
	if(sequence[s]=='g'||sequence[s]=='G'){
	  sequence[s]-=4;
	}
     } 
  }   
}

 
