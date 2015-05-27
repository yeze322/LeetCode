#ifndef LIST_GRAPH
#define LIST_GRAPH

#include "common.h"
#include "EdgeGraph.h"

/* inheritant from vertex_t, adjusted depends on save type 
adjaList means : adjacant Lists (a kind of data structure save Graph)
*/
enum COLOR{WHITE,GREY,BLACK};
struct adjaList_edge_t;
struct adjaList_vertex_t : public vertex_t{
	unsigned int index;
	int color;
	int discoverTime;
	int finishTime;
	adjaList_edge_t *next;
	//adjaList_vertex_t():color(false),next(NULL){}
	adjaList_vertex_t(vertex_t& x):vertex_t(x),color(false),next(NULL),discoverTime(0),finishTime(0){};
};

struct adjaList_edge_t{
	int edgeLen;
	adjaList_vertex_t *tartgetVertex;
	adjaList_edge_t *next;
	adjaList_edge_t(adjaList_vertex_t& x,int len=1):edgeLen(len),tartgetVertex(&x),next(NULL){}
};

/* Graph, only a lists of nodes, color by linked list */
class adjaListGraph{
public:
	/* Hash index, all nodes are saved here */
	vector<adjaList_vertex_t> vList;
	/* constructor from edgeGraph */
	adjaListGraph(edgeGraph&);
	/* common functions */
	void sortEdge();
	void refreshGraph();
	void printGraph();
	/* visit functionts */
	void DFS();
	void DFS(vector<int>&);
	void BFS();
private:
	/* Time functions, record Discover time && finish time */
	int __TIME;
	void __TIME_ADD();
	void __TIME_Record_Discover(adjaList_vertex_t&);
	void __TIME_Record_Finish(adjaList_vertex_t&);
	/* actions: Discover node && finish node */
	void __Action_DiscoverVertex(adjaList_vertex_t&);
	void __Action_FinishVertex(adjaList_vertex_t&);
	/* functions used in DFS */
	void __DFS_RecursiveVisit(adjaList_vertex_t&);
	void __DFS_GreyAction(adjaList_vertex_t&);
	void __DFS_BlackAction(adjaList_vertex_t&);
	void __DFS_SingleAction_Discover(adjaList_vertex_t&);
	void __DFS_SingleAction_Finish(adjaList_vertex_t&);
	void __DFS_NewTreeAction();
	void __DFS_EndTreeAction();
	/* functions used in BFS */
	void __BFS_SingleAction(adjaList_vertex_t&);
	void __BFS_NewLevelAction();
	void __BFS_NewGroupAction();
};

#endif //LIST_GRAPH