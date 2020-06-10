#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct REGION {
	char flag;
	int start[100];
	int end[100];
};
extern struct REGION region1,region2,region3;

int strstart2(char *s,char *t);
int countchar(char *s,char c);
int exp_char(char c,int exp);
int get_join(char *filename);
int isbase(char s);
void getcds(FILE *fp,char *sequence,struct REGION Region);
