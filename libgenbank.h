#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct REGION {
	char flag;
	int start[100];
	int end[100];
}region;
extern region region1,region2,region3;

int strstart2(char *s,char *t);
int countchar(char *s,char c);
int exp_char(char c,int exp);
int get_join(char *filename,region *region3,int num,char *sequence);	//get_join.c
int isbase(char c);
void getcds(FILE *fp,char *sequence,region *Region);//getcds.c
void get_cols(char *file_path,region *region1);
 char* del(char *string);	//xdd.c
int fopen1(FILE **file_out,char *name,int outs);
