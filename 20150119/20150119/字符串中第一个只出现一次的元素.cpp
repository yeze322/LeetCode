#include<stdio.h>
#include<string.h>

int main()
{
	char a[]="hhelpo asdadq!";
	int order[255]={0};
	int count[255]={0};
	for(int i=0;i<strlen(a);i++)
	{
		count[(int)a[i]]++;
		if(!order[(int)a[i]])
			order[(int)a[i]]=i+1;
	}
	int early=0x79999999;
	for(int i=0;i<255;i++)//用strlen,字符串转角标 还是直接遍历255好取决于字符串长度.用strlen方便而且不需要增加额外的数组；
		//但是考虑数据量很大的时候，想要寻找第一个非常不方便。因此。具体如何，还要看数据量吧
	{
		if(count[i]==1)
		{
			if(order[i]<early)
				early=order[i];
		}

	}
	return 0;
}
