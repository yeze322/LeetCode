#pragma once

#include "RuntimeMethods.h"

#include <iostream>
#include <ctime>

#include <algorithm>
#include <thread>
#include <vector>
#include <string>

#include "AdsItem.h"
#include "AdsInvertIndex.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
//function for create a irindex
vector<string>* loadFromFile(const string& fname, int maxItem){
	vector<string> *adsLines = new vector<string>;
	adsLines->reserve(9999);
	std::ifstream DATA(fname);
	string line;
	if (maxItem == 0){//unlimited
		while (std::getline(DATA, line)){
			adsLines->push_back(line);
		}
	}
	else{
		while (std::getline(DATA, line) && maxItem--){
			adsLines->push_back(line);
		}
	}
	return adsLines;
}

/*
vector<AdsItem> stringToAds(const string &fname, int maxItem = 0){
	vector<AdsItem> allAds;
	std::ifstream DATA(fname);
	string line;
	if (maxItem == 0){//unlimited
		while (std::getline(DATA, line)){
			allAds.push_back(line);
		}
	}
	else{
		while (std::getline(DATA, line) && maxItem--){
			allAds.push_back(line);
		}
	}
	return allAds;
}
*/

vector<AdsItem>* stringToAds(const vector<string> * lines){
	vector<AdsItem> *allAds = new vector<AdsItem>;
	allAds->reserve(lines->size());
	for (auto & x : *lines){
		allAds->push_back(x);
	}
	return allAds;
}

void textDestructor(vector<string>* ptr){
	cout << "Call destructor" << endl;
	clock_t start = clock();
	delete ptr;
	clock_t end = clock();
	cout << "Finished destructor: costs time --" << end - start << endl;
}

AdsInvertIndex* createInvertIndex(string & filename, int lines = 0){
	vector<string> *adsLines = loadFromFile(filename, lines);
	cout << "ads lines load finished, total number: "<<adsLines->size()<< endl;
	vector<AdsItem> *allAds = stringToAds(adsLines);
	cout << "ads structuring finished" << endl;
	AdsInvertIndex *IRIndex = new AdsInvertIndex(allAds);
	cout << "IRIndex finished" << endl;
	std::thread DELVEC(textDestructor, adsLines);
	DELVEC.detach();
	cout << "function return" << endl;
	return IRIndex;
}