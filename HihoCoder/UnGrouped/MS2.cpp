#include<iostream>
#include<stdio.h>
#include<vector>
#include <string>
#include <stack>
using namespace std;

stack<string> signals;
vector<int>* INFLUENCE;


class MOD{
public:
	int NO;
	string start_signal;
	vector<string> output_signal;
	void input();
	void start();
	int start_times;
	void calcu();
	MOD():start_times(0),NO(0){};
	vector<int>* influence;
};
vector<MOD*> modules;

void MOD::calcu(){
	signals.push(start_signal);
	while(!signals.empty()){
		string command = signals.top();
		signals.pop();
		for(int i=0;i<modules.size();i++){
			if(modules[i]->start_signal== command){
				modules[i]->start();
			}
		}
	}
	influence = new vector<int>(*INFLUENCE);
}


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
	(*INFLUENCE)[NO]++;
	for(int i = 0; i<output_signal.size();i++){
		signals.push(output_signal[i]);
	}
}


int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int circle;
	scanf("%d",&circle);
	for(int loop=0;loop<circle;loop++){
		int N,M; //N - signalsm M - modules
		scanf("%d",&N);
		scanf("%d",&M);
		INFLUENCE = new vector<int>(M,0);
		vector<int> start_times(0,M);
		vector<string> sis;
		for(int i_=0;i_<M;i_++){
			string temp;
			cin>>temp;
			sis.push_back(temp);
		}
		for(int i_=0;i_<N;i_++){
			MOD *newmod = new MOD();
			modules.push_back(newmod);
			newmod->NO = i_;
			newmod->input();
		}
		for(int i_=0;i_<N;i_++){
			modules[i_]->calcu();
		}
		for(int i=0;i<M;i++){
			signals.push(sis[i]);
		}
		while(!signals.empty()){
			string command = signals.top();
			signals.pop();
			for(int i=0;i<modules.size();i++){
				if(modules[i]->start_signal== command){
					for(int j=0;j<M;j++){
						start_times[j]+=(*modules[i]->influence)[j];
					}
				}
			}
		}

		for(int i=0;i<N;i++){
			printf("%d ",(start_times[i])%142857);
		}

		cout<<endl;
	}
}