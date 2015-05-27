#ifndef GraphSTRUCT_H
#define GraphSTRUCT_H

#include "common.h"

/* only used to save some information. users can change it */
struct vertex_t{
	string word;
	vertex_t():word("Nil"){};
	vertex_t(vertex_t& x){if(this != &x) this->word = x.word;}
	vertex_t(string& x):word(x){}
	vertex_t(char* str):word(string(str)){}
};
typedef unsigned int uint;
struct edge_t{
	uint first;
	uint second;
	int length;//used in weighted graphs, default equals 1
	edge_t(uint a,uint b,int c=1): first(a),second(b),length(c){}
};

class edgeGraph{
public:
	vector<vertex_t> allNodes;
	vector<edge_t> allEdges;
	void printGraph();
	void getEdgeGraphFromFile(const char*);
};


#endif //GraphSTRUCT_H