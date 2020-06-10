//Get the sequence from genbank ORIGIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isbase(char s)
{
  if (s=='a'||s=='t'||s=='c'||s=='g'||s=='A'||s=='T'||s=='C'||s=='G')
     return 1;
  else return 0;
}  

void getcds(char *file_gb,char *sequence,struct region)
{
  char buf[MAX];
  FILE *fp=NULL;
  int num,i=0,j;
  fp=fopen("*.gb","r");
  while(1){
    if(region.start[i]==0) break;
    fgets(buf,MAX,fp);
    if (strcmp(buf,"ORIGIN")==0){
        fscanf(fp,"%d",num);
        if ( region.start[i]-num < 60 && region.start[i]-num >= 0 ){
            int left_gap=region.start[i]-num+1;
	    while (1){
		char *tmp[MAX];
		fgets(tmp[j++],MAX,fp);
                fscanf(fp,"%d",num);
                if (num > region.end[i]){
		  int right_gap=num-region.end[i]-1;
		  fgets(buf,MAX,fp);
		  break;
		}
	    }             
	}
    rewind(fp);
    i++
    }
  }
  int m,n;
  char *sequence_tmp;
  for(m=0;m<=i;m++){ 
    for(n=0;tmp[m][n]!='\n';n++){    
	if (isbase(tmp[m][n])){
	    strcat(sequence_tmp,tmp[m][n]);
        }
    }
  }    
  len=strlen(sequence_tmp)-left_gap-right_gap;
  strncpy(sequence,sequence_tmp,len);

  if(flag=='c'){
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

 
