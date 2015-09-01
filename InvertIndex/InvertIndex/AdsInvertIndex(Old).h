#pragma once
#ifndef _ADSIRINDEX__
#define _ADSIRINDEX__

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <thread>

#include <Windows.h>
#include <direct.h>
#include <assert.h>

#include "AdsItem.h"
using namespace std;

class AdsInvertIndex{
public:
	/* save invert index */
	unordered_map<string, vector<AdsItem*>> adsMap;
	/* constructor */
	AdsInvertIndex(vector<AdsItem>* adsPtr) : Weight(100, 10, 1){
		addAdsSet(*adsPtr);
	}
	void addAdsSet(vector<AdsItem>& ads){
		using std::get;
		for (auto & adsItem : ads){
			//AdsItem adsItem(line);
			auto keyWordsTuple = adsItem.getKeyWordSet();
			vector<string>& bidKeywords = get<0>(keyWordsTuple);
			vector<string>& titleKeywords = get<1>(keyWordsTuple);
			vector<string>& textKeywords = get<2>(keyWordsTuple);

			createIndex_BidKeywords(bidKeywords, adsItem);
			createIndex_AdTitileKeywords(titleKeywords, adsItem);
			createIndex_AdTextKeywords(textKeywords, adsItem);
		}
	}
	/* forbid copy constructor and assignment */
	AdsInvertIndex(const AdsInvertIndex&) = delete;
	void operator = (const AdsInvertIndex&) = delete;
	/* search functions */
	vector<AdsItem*> search(string& key, int i){
		auto iter = this->adsMap.find(key);
		if (iter == this->adsMap.end())
			return{};
		else{
			auto ret = iter->second;
			//need to improve sort function
			std::sort(ret.begin(), ret.end(), [](AdsItem* & const lhs, AdsItem* & const rhs)->bool{return lhs->exactBid > rhs->exactBid; });
			if (ret.size() > i)
				ret.resize(i);
			return ret;
		}
	}

private:
	/* put differnt type of keywords into map */
	/*!!!wating for adding different rules*/
	void createIndex_BidKeywords(vector<string>& bidKws, AdsItem &item){
		for (auto & x : bidKws){
			item.score = rateAdsItem(item, Weight.fromBid);
			addToAdsMap(x, item);
		}
	}

	void createIndex_AdTitileKeywords(vector<string>& titleKws, AdsItem &item){
		for (auto & x : titleKws){
			item.score = rateAdsItem(item, this->Weight.fromTitle);
			addToAdsMap(x, item);
		}
	}

	void createIndex_AdTextKeywords(vector<string>& textKws, AdsItem &item){
		for (auto & x : textKws){
			item.score = rateAdsItem(item, this->Weight.fromText);
			addToAdsMap(x, item);
		}
	}
	void keyWordNormalizer(string& key){
		int len = key.length();
		int write = 0;
		for (int i = 0; i < key.size(); i++){
			if (key[i] == '?' || key[i] == '+'){
				len--;
			}
			else{
				key[write++] = key[i];
			}
		}
		key.resize(len);
	}
	void addToAdsMap(string& key, AdsItem& val){
		keyWordNormalizer(key);
		auto iter = this->adsMap.find(key);
		if (iter == this->adsMap.end())
			this->adsMap[key] = { &val };
		else
			this->adsMap[key].push_back(&val);
	}

	/* sort: top K */
	void SortAdsVector(string& key){
		auto & adsVec = this->adsMap[key];
	}

	/* different keywords weight for kws from different parts */
	struct KeywordsWeight{
		double fromBid;
		double fromTitle;
		double fromText;
		KeywordsWeight(double a, double b, double c) :fromBid(a), fromTitle(b), fromText(c){}
	}Weight;

	/*rating function*/
	double rateAdsItem(AdsItem& item, double weight){
		return 0;
	}

	/*sort's compare function implementation*/
	bool cmp(const AdsItem& lhs, const AdsItem& rhs){
		return true;
	}
public:
	void writeToFile(string& outputDir){
		if (outputDir[outputDir.size() - 1] != '/')
			outputDir += '/';
		DWORD attribute = GetFileAttributes(outputDir.c_str());
		if (attribute == INVALID_FILE_ATTRIBUTES){
			_mkdir(outputDir.c_str());
		}

		char s[100];
		string errfile = outputDir + "ErrorWords.csv";
		FILE *ferr= fopen(errfile.c_str(), "w");
		for (auto & pair : this->adsMap){
			string fname = outputDir + pair.first;
			FILE *fp = fopen(fname.c_str(), "w");
			if (fp == NULL){
				sprintf(s, "%s ,%d\n", pair.first.c_str(), pair.second.size());
				fwrite(s, sizeof(char), strlen(s), ferr);
			}
			else{
				assert(fp != NULL);
				for (auto ptr : pair.second){
					sprintf(s, "{\"%s\" : \"%d\"}\n", ptr->listingId.c_str(), ptr->score);
					fwrite(s, sizeof(char), strlen(s), fp);
				}
				fclose(fp);
			}
		}
		fclose(ferr);
	}
};
#endif