#include <stdlib.h>
#include <string.h>
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
int maxProfit(int prices[], int n){
    int *right = (int*)calloc(n,sizeof(int));
    int max_right = prices[n-1];
    for(int i=n-2;i>-1;i--){
        max_right = max(max_right,prices[i]);
        right[i] = max(max_right-prices[i],right[i+1]);
    }
    int min_left = prices[0];
	prices[0]=0;
    int profit_max = 0;
    for(int i=1;i<n;i++){
        min_left = min(min_left,prices[i]);
        prices[i] = max(prices[i]-min_left,prices[i-1]);
        profit_max = max(profit_max,prices[i]+right[i]);
    }
    return profit_max;
}

int main()
{
	int prices[] = {1,2,3};
	int ret = maxProfit(prices,sizeof(prices)/sizeof(int));
	return 0;
}
