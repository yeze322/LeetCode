#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int a[101][101]={0};
int main()
{
	freopen("output.txt","w",stdout);
	a[1][0]=1;
	a[1][1]=1;
	for(int i=1;i<101;i++){
		for(int j=1;j<101;j++){
			a[i][j]=a[i][j-1]+a[i-1][j];
		}
	}

	for(int i=0;i<101;i++){
		printf("{");
		for(int j=0;j<i+1;j++){
			if(a[i][j]<0)
				break;
			printf("%d,",a[i][j]);
		}
		printf("},\n");
	}
}