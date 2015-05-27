#include "AdjacantListGraph.h"

adjaListGraph::adjaListGraph(edgeGraph& inputGraph){
	__TIME = 0;
	/* transfer adgGraph to adjaListGraph */
	/* 1 - transfer nodes */
	vector<vertex_t>& inputNodes = inputGraph.allNodes;
	for(unsigned int i=0;i<inputNodes.size();i++){
		vList.push_back(adjaList_vertex_t(inputNodes[i]));
		vList[i].index = i;
	}
	/* 2 - transfer edges */
	vector<edge_t>& inputEdges = inputGraph.allEdges;
	for(unsigned int i=0;i<inputEdges.size();i++){
		edge_t& thisEdge = inputEdges[i];
		/* head insert linked list, unordered */
		adjaList_vertex_t* rootNode = &vList[thisEdge.first];
		adjaList_edge_t* insertEdge = new adjaList_edge_t(vList[thisEdge.second],thisEdge.length);
		adjaList_edge_t* recordEdge =  rootNode->next;
		rootNode->next = insertEdge;
		insertEdge->next = recordEdge;
	}
}

//bool __compareIndex(const adjaList_edge_t* a,const adjaList_edge_t* b){
//	return a->tartgetVertex->index < b->tartgetVertex->index;
//}

bool __adjaList_edge_compare(const adjaList_edge_t *left,const adjaList_edge_t *right){
	return left->tartgetVertex->index < right->tartgetVertex->index;
}

void adjaListGraph::sortEdge(){
	for(auto iter_v=vList.begin();iter_v!=vList.end();++iter_v){
		vector<adjaList_edge_t*> allLinkedEdges;
		adjaList_edge_t *ptr_edge = iter_v->next;
		while(ptr_edge!=NULL){
			allLinkedEdges.push_back(ptr_edge);
			ptr_edge = ptr_edge->next;
		}
		if(!allLinkedEdges.empty()){
			sort(allLinkedEdges.begin(),allLinkedEdges.end(),__adjaList_edge_compare);
			iter_v->next = allLinkedEdges[0];
			for(int i=0;i<allLinkedEdges.size()-1;i++)
				allLinkedEdges[i]->next = allLinkedEdges[i+1];
			allLinkedEdges[allLinkedEdges.size()-1]->next = NULL;
		}
	}

}

void adjaListGraph::refreshGraph(){
	__TIME = 0;
	for(auto iter=vList.begin();iter!=vList.end();++iter){
		iter->color = false;
		iter->finishTime = 0;
		iter->discoverTime = 0;
	}
}

void adjaListGraph::printGraph(){
	for(auto iterNodes=vList.begin();iterNodes!=vList.end();++iterNodes){
		cout<<"["<<iterNodes->word<<"] ";
		auto iterTempVisit = iterNodes->next;
		while(iterTempVisit!=NULL){
			cout<<"-"<<iterTempVisit->edgeLen<<"-> ["<<iterTempVisit->tartgetVertex->word<<"] ";
			iterTempVisit = iterTempVisit->next;
		}
		cout<<"/"<<endl;
	}
	cout<<endl;
}
/* Time functions */
void adjaListGraph::__TIME_ADD(){
	__TIME++;
}

void adjaListGraph::__TIME_Record_Discover(adjaList_vertex_t& v){
	v.discoverTime = __TIME;
}

void adjaListGraph::__TIME_Record_Finish(adjaList_vertex_t& v){
	v.finishTime = __TIME;
}
/* Tow basic function: Discover and finish */
void adjaListGraph::__Action_DiscoverVertex(adjaList_vertex_t& v){
	v.color = GREY;
	__TIME_ADD();
	__TIME_Record_Discover(v);
}

void adjaListGraph::__Action_FinishVertex(adjaList_vertex_t& v){
	v.color = BLACK;
	__TIME_ADD();
	__TIME_Record_Finish(v);
}

/* DDDDDDDDFS part start */
void adjaListGraph::DFS(){
	for(int i=0;i<vList.size();i++){
		if(vList[i].color == WHITE){
			__DFS_NewTreeAction();
			__DFS_RecursiveVisit(vList[i]);
			__DFS_EndTreeAction();
		}
	}
}

void adjaListGraph::DFS(vector<int>& inputOrder){
	for(int indexGiven=0;indexGiven<inputOrder.size();indexGiven++){
		adjaList_vertex_t& givenVertex = vList[inputOrder[indexGiven]];
		if(givenVertex.color == WHITE){
			__DFS_NewTreeAction();
			__DFS_RecursiveVisit(givenVertex);
			__DFS_EndTreeAction();
		}
	}
	for(int i=0;i<vList.size();i++){
		if(vList[i].color == WHITE){
			__DFS_NewTreeAction();
			__DFS_RecursiveVisit(vList[i]);
			__DFS_EndTreeAction();
		}
	}
}

void adjaListGraph::__DFS_RecursiveVisit(adjaList_vertex_t &v){
	__Action_DiscoverVertex(v);
	__DFS_SingleAction_Discover(v);
	int vIndex = v.index;
	adjaList_edge_t *p_eNext= vList[vIndex].next;
	while(p_eNext != NULL){
		adjaList_vertex_t *p_targetVertex = p_eNext->tartgetVertex;
		switch(p_targetVertex->color){
		case WHITE:
			__DFS_RecursiveVisit(*p_targetVertex);break;
		case GREY:
			__DFS_GreyAction(*p_targetVertex);break;
		case BLACK:
			__DFS_BlackAction(*p_targetVertex);break;
		}
		p_eNext = p_eNext->next;
	}
	__Action_FinishVertex(v);
	__DFS_SingleAction_Finish(v);
}
void adjaListGraph::__DFS_GreyAction(adjaList_vertex_t &v){
	//cout<<"Backward Edge Discover\n";
}

void adjaListGraph::__DFS_BlackAction(adjaList_vertex_t &v){
	//cout<<"Foward Edge\n";
}

void adjaListGraph::__DFS_SingleAction_Discover(adjaList_vertex_t &v){
	cout<<"("<<v.word<<" ";
}

void adjaListGraph::__DFS_SingleAction_Finish(adjaList_vertex_t& v){
	cout<<v.word<<") ";
}

void adjaListGraph::__DFS_NewTreeAction(){
	cout<<endl;
}

void adjaListGraph::__DFS_EndTreeAction(){
}

/* DFS part end*/

/* BBBBBBBFS part start */
void adjaListGraph::BFS(){
	vector<adjaList_vertex_t*> thisLevel;
	vector<adjaList_vertex_t*> nextLevel;

	for(int i=0;i<vList.size();i++){
		if(vList[i].color == WHITE){
			__BFS_NewGroupAction();
			thisLevel.clear();
			thisLevel.push_back(&vList[i]);
			/* start BFS, thisLevel and nextLevel will change */
			while(!thisLevel.empty()){
				__BFS_NewLevelAction();
				/* mark all vertex saved in thisLevel */
				for(int i=0;i<thisLevel.size();i++){
					(*thisLevel[i]).color = GREY;
					__BFS_SingleAction(*thisLevel[i]);
					adjaList_edge_t *p_eNext = vList[thisLevel[i]->index].next;
					/* add vertex into nextLevel */
					while(p_eNext!=NULL){
						/* only when make sure uncolor, can be pushed */
						switch(p_eNext->tartgetVertex->color){
						case WHITE: nextLevel.push_back(p_eNext->tartgetVertex);break;
						case GREY: cout<<"FIND CIRCLE\n";break;
						}
						p_eNext = p_eNext->next;
					}
					(*thisLevel[i]).color = BLACK;
				}//for end
				thisLevel = nextLevel;
				nextLevel.clear();
			}//while end
		}
	}
}

void adjaListGraph::__BFS_SingleAction(adjaList_vertex_t &v){
	cout<<v.word<<" ";
}

void adjaListGraph::__BFS_NewLevelAction(){
	cout << endl;
}

void adjaListGraph::__BFS_NewGroupAction(){
	cout <<"new group";
}
/* BFS part end */