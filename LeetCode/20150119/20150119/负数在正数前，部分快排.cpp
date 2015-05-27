#include<stdio.h>
int qsstep(int a[],int size)
{
	if(a==NULL||size<=1)
		return -1;
	int i=0,j=size-1;
	while(i<j)
	{
		while(i<j&&a[j]>=0)
			j--;
		while(i<j&&a[i]<=0)
			i++;
		int temp=a[i];a[i]=a[j];a[j]=temp;
	}
	return i;
}//不把0聚集到中间。

void gatherzero(int a[],int size,int cut)
{
	int write1=0;
	for(int i=0;i<=cut;i++)//cut对应位置的元素肯定是负的或者零，因为j先行。
	{
		while(a[i]==0&&i<cut)
			i++;
		a[write1++]=a[i];
	}
	int write2=size-1;
	for(int i=size-1;i>cut;i--)
	{
		while(a[i]==0&&i>cut)
			i--;
		a[write2--]=a[i];
	}
	for(int i=write1;i<=write2;i++)
		a[i]=0;
}

int main()
{
	int a[10]={1,0,2,0,3,-6,-98,0,4,-6};
	int cut=qsstep(a,10);
	gatherzero(a,10,cut);
	return 0;
}
