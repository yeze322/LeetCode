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
	for(int i=0;i<255;i++)//��strlen,�ַ���ת�Ǳ� ����ֱ�ӱ���255��ȡ�����ַ�������.��strlen������Ҳ���Ҫ���Ӷ�������飻
		//���ǿ����������ܴ��ʱ����ҪѰ�ҵ�һ���ǳ������㡣��ˡ�������Σ���Ҫ����������
	{
		if(count[i]==1)
		{
			if(order[i]<early)
				early=order[i];
		}

	}
	return 0;
}
