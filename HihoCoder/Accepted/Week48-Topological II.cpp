#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

struct vertex_t{
	int virus;
	int indegree;
	vector<int> edge;
	vertex_t():virus(0),indegree(0){}
};

int main()
{
	freopen("input.txt","r",stdin);
	int N_vertex,M_edge,K_virus;
	while(cin>>N_vertex>>M_edge>>K_virus){
		int TOTAL = 0;
		vector<vertex_t> vList(N_vertex+1);
		int virusIndex;
		for(int i=0;i<K_virus;i++){
			scanf("%d",&virusIndex);
			vList[virusIndex].virus = 1;
		}
		int left,right;
		for(int i=0;i<M_edge;i++){
			scanf("%d %d",&left,&right);
			vList[left].edge.push_back(right);
			vList[right].indegree++;
		}
		vector<vertex_t*> zero;
		for(int i=1;i<N_vertex+1;i++){
			if(vList[i].indegree == 0)
				zero.push_back(&vList[i]);
		}
		while(!zero.empty()){
			vector<vertex_t*> nextLevel;
			for(vertex_t *x : zero){
				int addVirus = (x->virus)%142857;
				TOTAL = (TOTAL + addVirus)%142857;
				for(int index : x->edge){
					vList[index].indegree--;
					if(vList[index].indegree == 0)
						nextLevel.push_back(&vList[index]);
					vList[index].virus += addVirus;
				}
			}
			zero = nextLevel;
		}
		printf("%d\n",TOTAL);
	}
	return 0;
}