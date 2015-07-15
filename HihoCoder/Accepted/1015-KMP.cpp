#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

vector<int> calcNext(string s){
	int size = s.size();
	vector<int> next(size);
	for (int i = 1; i < size; i++){
		if (s[next[i - 1]] == s[i])
			next[i] = next[i - 1] + 1;
		else
			next[i] = s[0] == s[i];
	}
	return next;
}
int KMP(string origin, string match){
	int len_origin = origin.length();
	int len_match = match.length();
	int i = 0, j = 0;
	vector<int> next = calcNext(match);
	int count = 0;
	while (i < len_origin){
		while (i < len_origin && j < len_match){
			if (origin[i] == match[j]){
				i++;
				j++;
			}
			else if (j == 0){
				i++;
			}
			else{
				j = next[j - 1];
			}
		}
		if (j == len_match){
			count++;
			j = next[j - 1];
		}
	}
	return count;
}
int main(){
	freopen("in.txt", "r", stdin);
	int N;
	scanf("%d ", &N);
	string match, s;
	for (int i = 0; i < N; i++){
		cin >> match >> s;
		int ret = KMP(s, match);
		cout << ret << endl;
	}
	return 0;
}