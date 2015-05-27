#include<iostream>
using namespace std;
#include<cstdio>
#include<cstring>
const int MAX_WLEN = 11;
const int ALPHA_NUM = 26;
struct Node{
    int count;
	int md5;
    Node* nextHash[ALPHA_NUM];
    Node(): count(0),md5(-1){memset(nextHash,0x00,ALPHA_NUM*sizeof(Node*));}
};

Node* TrieTreeRoot = new Node;
int nowMD5 = 0;

void addWord(char* s){
	int len = strlen(s);
	Node *startNode = TrieTreeRoot;
	for(int i=0;i<len;i++){
		int hashIndex = s[i] - 'a';
		Node* & shouldNode = (startNode->nextHash)[hashIndex];
		if(shouldNode == NULL)
			shouldNode = new Node;
		
		if(shouldNode->md5 != nowMD5){///node already exsits.old node, reset it
			shouldNode->count = 0;
			shouldNode->md5 = nowMD5;
		}
		(shouldNode->count)++;
		startNode = shouldNode;
	}
}

void createTrieTree(int NUM){
	char s[MAX_WLEN];
	for(int i=0;i<NUM;i++){
		memset(s,0,sizeof(char)*MAX_WLEN);
		scanf("%s",s);
		addWord(s);
	}
}

int searchPreffixNum(char *pref){
	Node *startNode = TrieTreeRoot;
	int prefLen = strlen(pref);
	for(int i=0;i<prefLen;i++){
		int hashIndex = pref[i] - 'a';
		Node* shouldNode = (startNode->nextHash)[hashIndex];
		if(shouldNode == NULL || shouldNode->md5 != nowMD5)
			return 0;
		startNode = shouldNode;
	}
	return startNode->count;
}

void searchTrieTree(){
	int N;
	cin>>N;
	char preffix[MAX_WLEN];
	for(int i=0;i<N;i++){
		memset(preffix,0,sizeof(char)*MAX_WLEN);
		scanf("%s",preffix);
		int howMany = searchPreffixNum(preffix);
		printf("%d\n",howMany);
	}
}

int main(){
	freopen("input.txt","r",stdin);
	int inputNum;
	while(cin>>inputNum){
    	createTrieTree(inputNum);
		searchTrieTree();
		nowMD5++;
	}
	return 0;
}