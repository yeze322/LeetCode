#define _CRT_SECURE_NO_DEPRECATE
#define PC

#include <cstdio>
#include <vector>
using namespace std;

class nextList{
public:
	vector<int> next;
	int  size;
	nextList() :size(0){}
	inline bool remove(int);
	inline void insert(int);
	inline int pop();
	inline bool empty(){ return size == 0; }
};

bool nextList::remove(int val){
	for (auto iter = next.begin(); iter != next.end(); ++iter){
		if (*iter == val){
			*iter = -1;
			size--;
			return true;
		}
	}
	return false;
}

int nextList::pop(){
	int ret = 0;
	for (auto iter = next.begin(); iter != next.end(); ++iter){
		if (*iter != -1){
			ret = *iter;
			*iter = -1;
			size--;
			break;
		}
	}
	return ret;
}

void nextList::insert(int val){
	size++;
	next.push_back(val);
}

class Euler{
public:
	void input(){
		int n_edge;
		scanf("%d %d", &__N_node, &n_edge);
		__adjaList.resize(__N_node + 1);
		__visited.resize(__N_node + 1);
		int l, r;
		for (int i = 0; i < n_edge; i++){
			scanf("%d %d", &l, &r);
			__adjaList[l].insert(r);
			__adjaList[r].insert(l);
		}
	}

	void dfsStart(){
		for (int i = 1; i < __N_node + 1; i++){
			if (__adjaList[i].size % 2){
				DFS(i);
				return;
			}
		}
	}

	void DFS(int index_start){
		__visited[index_start] = true;
		while (!__adjaList[index_start].empty()){
			int next_index = __adjaList[index_start].pop();
			__adjaList[next_index].remove(index_start);
			DFS(next_index);
		}
		__outputArr.push_back(index_start);
	}
	void output(){
		for (auto iter = __outputArr.begin(); iter != __outputArr.end(); ++iter){
			printf("%d ",*iter);
		}
		printf("\n");
	}

private:
	vector<bool> __visited;
	vector<nextList> __adjaList;
	vector<int> __outputArr;
	int __N_node;
};

#ifndef PC
int main(){
	Euler map;
	map.input();
	map.DFS(1);
	map.output();
	return 0;
}
#endif

#ifdef PC
int main(){
	freopen("in.txt", "r", stdin);
	Euler test1;
	test1.input();
	test1.dfsStart();
	test1.output();
	return 0;
}
#endif