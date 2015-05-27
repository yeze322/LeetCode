#include "common.h"
#include "EdgeGraph.h"
#include "AdjacantListGraph.h"

int main()
{
	bool ifTestList = true;
	bool ifTestMatrix = false;
	bool ifTestDFS = true;
	bool ifTestBFS = false;
	/* initialize basic input: adgeGraph */
	freopen("inputGraph.txt","r",stdin);
	edgeGraph fourBridge;
	fourBridge.getEdgeGraphFromFile("inputGraph.txt");
	fourBridge.printGraph();
	/* Lists Graph */
	
	if(ifTestList){
		adjaListGraph adjaList_fourBridge(fourBridge);
		adjaList_fourBridge.printGraph();
		// test DFS 
		adjaList_fourBridge.refreshGraph();
		adjaList_fourBridge.sortEdge();
		adjaList_fourBridge.printGraph();
		if(ifTestDFS){
			cout<<"\n==DFS==\n";
			int visitOrder[] = {2,3,};
			adjaList_fourBridge.DFS(vector<int>(visitOrder,visitOrder+sizeof(visitOrder)/sizeof(int)));
			cout<<"\n==END_DFS==\n"<<endl;
		}
		if(ifTestBFS){
			cout<<"\n==BFS==\n";
			adjaList_fourBridge.refreshGraph();
			adjaList_fourBridge.BFS();
			cout<<"\n==END_BFS==\n"<<endl;
		}
	}

	///* Matrix Graph */
	//if(ifTestMatrix){
	//	adjaMatrixGraph adjaMatrix_fourBridge(fourBridge);
	//	adjaMatrix_fourBridge.printGraph();
	//}
	cout<<"TEST END"<<endl;
	return 0;
}