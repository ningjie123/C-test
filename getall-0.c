#include "libgenbank.h"

int isbase(char s)
{
  if (s=='a'||s=='t'||s=='c'||s=='g'||s=='A'||s=='T'||s=='C'||s=='G')
     return 1;
  else return 0;
}

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
 	char buf[200];
  	int num,i=0,j;
 	int left_gap,right_gap,len;
  	while(1){
    	if(region3->start[i]==0) break;
    	fgets(buf,200,fp);
   	if (strcmp(buf,"ORIGIN")==0){
        	fscanf(fp,"%d",num);
        	if ( region3->start[i]-num < 60 && region3->start[i]-num >= 0 ){
            		left_gap=region3->start[i]-num;
	    		while (1){
				char *tmp[200];
				fgets(tmp[j++],200,fp);
                		fscanf(fp,"%d",num);
                		if (num > region3->end[i]){
		  			right_gap=num-region3->end[i]-1;
		  			fgets(buf,MAX,fp);
		  			break;
				}
  				int m,n;
			 	char sequence_tmp[1000];
			  	for(m=0;m<j;m++){ 
			       		for(n=0;tmp[m][n]!='\n';n++){    
						if (isbase(tmp[m][n])){
							strcat(sequence_tmp,tmp[m][n]);
        					}
    					}
  				}			    
  				len=strlen(sequence_tmp)-left_gap-right_gap;
  				strncpy(sequence,sequence_tmp+left_gap,len);
				
	    		}             
		}
    		i++;
    		rewind(fp);
    	}
	printf("finish1\n");
  if(Region->flag=='c'){
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
printf("%s\n",sequence);		
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
