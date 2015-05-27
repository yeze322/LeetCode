#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int min(int a,int b,int c){
	int ret = a<b?a:b;
	return ret<c?ret:c;
}

void print(int **a,int len1,int len2,char *word1,char *word2){
	printf("   ");
	for(int i=0;i<len2;i++){
		printf("%3c",word2[i]);
	}
	putchar('\n');
	for(int i=0;i<len1;i++){
		printf("%3c",word1[i]);
		for(int j=0;j<len2;j++){
			printf("%3d",a[i][j]);
		}
		printf("\n");
	}
}

bool scanup(int i,int j,char *word1,char *word2)
{
	char flag= word2[j];
	for(int lp = 0;lp<i;lp++){
		if(word1[lp]==flag)
			return true;
	}
	return false;
}
bool scanleft(int i,int j,char *word1,char *word2)
{
	char flag= word1[i];
	for(int lp = 0;lp<j;lp++){
		if(word2[lp]==flag)
			return true;
	}
	return false;
}
int minDistance(char *word1, char *word2) {
	int len1 = strlen(word1);
	int len2 = strlen(word2);
	if(len1==0||len2==0)
		return len1+len2;
	if(len1==1&&len2==1)
		return word1[0]!=word2[0];
	if(len1==1)
		return (strstr(word2,word1)==NULL)+len2-1;
	if(len2==1)
		return (strstr(word1,word2)==NULL)+len1-1;
	/*matrix*/
	int **a = (int **)malloc(len1*sizeof(int*));
	for(int i=0;i<len1;i++){
		a[i] = (int *)malloc(len2*sizeof(int));
	}

	a[0][0] = (word1[0]!=word2[0]);
	bool existed = false;
	for(int i=1;i<len1;i++){
		int add = (word1[i]!=word2[0]);
		if(add==0){
			add = existed;
			existed = true;
		}
		a[i][0] = a[i-1][0]+add;
	}
	existed = !a[0][0];
	for(int j=1;j<len2;j++){
		int add = (word2[j]!=word1[0]);
		if(add==0){
			add = existed;
			existed = true;
		}
		a[0][j] = a[0][j-1]+add;
	}
	//frame finished
	/*fill*/
	for(int i=1;i<len1;i++){
		for(int j=1;j<len2;j++){
			bool if_add = (word1[i]!=word2[j]);
			int val1 = a[i-1][j-1] + if_add;
			int val_up = a[i-1][j] + 1;//(if_add||scanup(i,j,word1,word2));
			int val_left = a[i][j-1] + 1;//(if_add||scanleft(i,j,word1,word2));
			a[i][j] = min(val1,val_up,val_left);
		}
	}

	print(a,len1,len2,word1,word2);
	return a[len1-1][len2-1];
}

int main()
{
	char s1[] = "zooooooooooooooo";
	char s2[] = "zo";
	int ret = minDistance(s1,s2);
	return 0;
}

