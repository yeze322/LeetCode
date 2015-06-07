#include <stdio.h>
#include <string.h>
int island[10001];

int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    memset(island,0,sizeof(int)*(N+1));
    int i=0,b1,b2;
    for(;i<M;i++){
        scanf("%d %d",&b1,&b2);
        island[b1]++;
        island[b2]++;
    }
    int odd_count = 0;
    for(i=1;i<N+1;i++){
        if(island[i]==0) goto wrong;
        if(island[i]%2){
            odd_count++;
            if(odd_count>2) goto wrong;
        }
    }
    if(odd_count == 2 || odd_count ==0 )
        printf("Full\n");
    return 0;
wrong:
    printf("Part\n");
    return 0;
}