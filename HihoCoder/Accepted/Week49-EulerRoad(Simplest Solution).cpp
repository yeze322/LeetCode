#include <stdio.h>
#include <string.h>
int island[10001];
int unionset[10001];

int findEnd(int start){
	int end = unionset[start];
	while(unionset[end]!=end)
		end = unionset[end];
	return end;
}


int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    memset(island,0,sizeof(int)*(N+1));
    memset(unionset,0,sizeof(int)*(N+1));

    int i=0,b1,b2;
    for(;i<M;i++){
        scanf("%d %d",&b1,&b2);
        island[b1]++;
        island[b2]++;
		if(unionset[b1]==0&&unionset[b2]==0){
			unionset[b1] = b1;
			unionset[b2] = b1;
		}else if(unionset[b1]!=0&&unionset[b2]!=0){
			int end1 = findEnd(b1);
			int end2 = findEnd(b2);
			unionset[end2] = end1;
		}else{
			if(unionset[b1]==0)
				unionset[b1] = b2;
			else
				unionset[b2] = b1;
		}
    }

    int odd_count = (island[1]%2 != 0);
	int ROOT = findEnd(1);
    for(i=2;i<N+1;i++){
		/* exam odd and even */
        if(island[i]%2){
            odd_count++;
			if(odd_count > 2)
				break;
        }
		/* exam connected */
		int thisRoot = findEnd(i);
		if(thisRoot != ROOT){
			odd_count = -1;
			break;
		}
    }

    if(odd_count==2 || odd_count==0) printf("Full\n");
	else printf("Part\n");
    return 0;
}