#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Node{
	string name;
	Node *root;
	Node(const string& x):name(x),root(this){}
	Node(const string& x,Node *y):name(x),root(y){}
};

class UnionSet{
public:
	UnionSet(int x):N(x){}
	void run();
	void printResult();
private:
	/* the number of inputs */
	int N;
	/* A map save elements' pair, so we can visit struct Node via string*/
	unordered_map<string,Node*> __Elmts;
	/* An array save the search result, need to be printed after input done*/
	vector<bool> __findResultArray;

	Node* findRoot(const string&);
	bool UnionFind(const string&,const string&);
	void UnionAdd(const string&,const string&);
	bool mapFind(const string& word){
		auto found = __Elmts.find(word);
		if(__Elmts.end()!=found) return true;
		else return false;
	}
};

void UnionSet::run(){
	bool mode;
	string word1;
	string word2;
	for(int i=0;i<N;i++){
		cin>>mode>>word1>>word2;
		if(mode==0){
			//add elmt pair
			UnionAdd(word1,word2);
		}else{//search element pair
			bool samePi = UnionFind(word1,word2);
			(this->__findResultArray).push_back(samePi);
		}
	}
	return;
}

Node* UnionSet::findRoot(const string& word){
	Node *thisNode = __Elmts[word];
	Node *rootNode = thisNode;
	vector<Node*> vistedNode;
	while(rootNode->root->name!=rootNode->name){
		vistedNode.push_back(rootNode);
		rootNode = rootNode->root;
	};
	//point all via node to root;
	int viaNodeNum = vistedNode.size();
	if(viaNodeNum > 1){
		//the last elmt already pointed to rootNode, so skip tail
		for(int i=0;i<viaNodeNum-1;i++)
			vistedNode[i]->root = rootNode;
	}
	return rootNode;
}

bool UnionSet::UnionFind(const string& word1,const string& word2){
	//elmt do not exits
	bool foundWord1 = mapFind(word1);
	if(false == foundWord1) return false;
	bool foundWord2 = mapFind(word2);
	if(false == foundWord2) return false;
	//two word exists
	Node *root1 = findRoot(word1);
	Node *root2 = findRoot(word2);
	return root1 == root2;
}
void UnionSet::UnionAdd(const string& word1,const string& word2){
	bool foundWord1 = mapFind(word1);
	bool foundWord2 = mapFind(word2);
	if(true == foundWord1 && true == foundWord2){
		Node *root1 = findRoot(word1);
		Node *root2 = findRoot(word2);
		root1->root = root2;
	}else if(false == foundWord1 && false == foundWord2){
		//both of them not found, create new Union-find set
		Node *addNode1 = new Node(word1);
		Node *addNode2 = new Node(word2,addNode1);
		__Elmts.emplace(word1,addNode1);
		__Elmts.emplace(word2,addNode2);
	}else{
		//only one existed
		const string * p_existedWord;
		const string *p_addWord;
		//adjust the order
		if(true == foundWord1){
			p_existedWord = &word1;
			p_addWord = &word2;
		}else if(true == foundWord2){
			p_existedWord = &word2;
			p_addWord = &word1;
		}
		//add to set;
		Node *addNode = new Node(*p_addWord,__Elmts[*p_existedWord]->root);
		__Elmts.emplace(*p_addWord,addNode);
	}
}

void UnionSet::printResult(){
	for(auto iter = __findResultArray.begin();iter!=__findResultArray.end();++iter){
		if(true == *iter) cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
}

int main()
{
	int N = 0;
	while(cin>>N){
		UnionSet unit(N);
		unit.run();
		unit.printResult();
	}
	return 0;
}