#include "EdgeGraph.h"

void edgeGraph::printGraph(){
	for(int i=0;i<allNodes.size();i++){
		cout<<i<<": ["<<allNodes[i].word<<"]"<<endl;
	}
	for(int i=0;i<allEdges.size();i++){
		cout<<"("<<allEdges[i].first<<","<<allEdges[i].second<<")";
		cout<<"|"<<allEdges[i].length<<"  ";
	}
	cout<<endl<<endl;
}

void edgeGraph::getEdgeGraphFromFile(const char *filename){//I want to change this to stream style
	ifstream inFile(filename);
	int vertexNum;inFile>>vertexNum;
	string vertexInfo;
	for(int i=0;i<vertexNum;i++){
		inFile>>vertexInfo;
		allNodes.push_back(vertex_t(vertexInfo));
	}
	int edgesNum;inFile>>edgesNum;
	uint first,second;
	int length;
	for(int i=0;i<edgesNum;i++){
		inFile>>first>>second>>length;
		allEdges.push_back(edge_t(first,second,length));
	}
}