#ifndef MATRIX_GRAPH
#define MATRIX_GRAPH

#include "common.h"
#include "EdgeGraph.h"

class adjaMatrixGraph{
public:
	vector<vertex_t> vList;
	vector<vector<int>> edgeMatrix;
	adjaMatrixGraph(edgeGraph&);
	void printGraph();
};

adjaMatrixGraph::adjaMatrixGraph(edgeGraph& inputGraph){
	vList = inputGraph.allNodes;
	int nodeNumber = vList.size();
	/*initialize capacity*/
	for(int i=0;i<nodeNumber;i++){
		edgeMatrix.push_back(vector<int>(nodeNumber));
	}
	/* assign edge to matrix */
	vector<edge_t>& inputEdges = inputGraph.allEdges;
	for(auto iterEdge = inputEdges.begin();iterEdge!=inputEdges.end();++iterEdge){
		edgeMatrix[iterEdge->first][iterEdge->second] = iterEdge->length;
	}
}

void adjaMatrixGraph::printGraph(){
	int NUM = vList.size();
	for(int i=0;i<NUM;i++){
		cout<<"["<<vList[i].word<<"] ";
		for(int j=0;j<NUM;j++)
			cout<<edgeMatrix[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}

#endif //MATRIX_GRAPH