#include<iostream>
#include<stdio.h>
#include<vector>
#include <string>
#include <stack>
using namespace std;

stack<string> signals;
class MOD{
public:
	string start_signal;
	vector<string> output_signal;
	void input();
	void start();
	int start_times;
	MOD():start_times(0){};
};

void MOD::input()
{
	cin>>start_signal;
	int number;
	scanf("%d",&number);
	for(int i=0;i<number;i++){
		string temp;
		cin>>temp;
		output_signal.push_back(temp);
	}
}
void MOD::start()
{
	start_times++;
	for(int i = 0; i<output_signal.size();i++){
		signals.push(output_signal[i]);
	}
}


int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int circle;
	scanf("%d",&circle);
	for(int loop=0;loop<circle;loop++){
		int N,M; //N - signalsm M - modules
		scanf("%d",&N);
		scanf("%d",&M);
		vector<MOD*> modules;
		for(int i_=0;i_<M;i_++){
			string temp;
			cin>>temp;
			signals.push(temp);
		}
		for(int i_=0;i_<N;i_++){
			MOD *newmod = new MOD();
			modules.push_back(newmod);
			newmod->input();
		}
		while(!signals.empty()){
			string command = signals.top();
			signals.pop();
			for(int i=0;i<modules.size();i++){
				if(modules[i]->start_signal== command){
					modules[i]->start();
				}
			}
		}

		for(int i=0;i<N;i++){
			printf("%d ",(modules[i]->start_times)%142857);
		}

		cout<<endl;
	}
}