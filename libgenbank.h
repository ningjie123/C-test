#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct REGION {
	char flag;
	int start[100];
	int end[100];
};
extern struct REGION region1,region2,region3;
