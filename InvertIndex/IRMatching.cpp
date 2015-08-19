#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <ctime>
#include <algorithm>

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;
using std::tuple;

const enum AdsItemIndex{
	CampaignId,
	ListingId,
	AdId,
	BidKeyword,
	Matchtypes,
	ExactBid,
	PhraseBid,
	BroadBid,
	ActualAdTitle,
	ActualAdDesc,
	ActualDisplayURL,
	ActualDestinationURL,
	MatchTypeId,
};

vector<string> split(const string  &s, char delim) {
	vector<string> result;
	std::stringstream ss(s);
	string item;
	//to much copy here... not solved
	while (std::getline(ss, item, delim))
		result.push_back(item);
	return result;
}

class AdsItem{
public:
	/*Id Part*/						/*Example*/
	string campaignId;				/*120167260*/
	string listingId;				/*7933771993*/
	string adId;					/*8557524873*/

	/*Bid Info Part*/
	vector<string> bidKeyWords;				/*mercedes benz s65 lease*/
	string matchTypes;				/*B P E*/
	int exactBid;					/*164*/
	int phraseBid;					/*164*/
	int broadBid;					/*164*/

	/*Ads Text Info*/
	string actualAdTitle;			/*Mercedes - Benz S - Class*/
	string actualAdDesc;			/*Lease a S - Class for $1249 / mo.Mercedes - Benz of Ontario!*/
	string actualDisplayURL;		/*www.MbOntario.com*/
	string actualDestinationURL;	/*http://....*/
	int matchTypeId;				/*3*/

	/*ads' score, used to sort*/
	double score;

	/* generate keywords and rating them automatically */
	tuple<vector<string>, vector<string>, vector<string>> getKeyWordSet(){
		return std::make_tuple(
			this->getBidKeywords(),
			this->getAdsTitleKeyWords(),
			this->getAdsTextKeyWords()
			);
	}

	void print(){
		using namespace std;
		cout << adId << " " << actualAdTitle << endl;
	}

private:
	/*Const members*/
	static const char adSeparator = '\t';
	static const char keywordSeparator = ' ';
	static const int adItemNumber = 13;

	/*Method Functions*/
	int ToInt(string &x){ return std::atoi(x.c_str()); }

	vector<string> getBidKeywords(){
		return this->bidKeyWords;
	}

	vector<string> getAdsTitleKeyWords(){
		return vector<string>{};
	}

	vector<string> getAdsTextKeyWords(){
		return vector<string>{};
	}

	void keyWordFilter(){

	}


public:
	/*Constructor*/
	AdsItem(const string& textLine) : score(0){
		vector<int> head(adItemNumber);
		vector<int> len(adItemNumber);
		int index = 0;
		for (int i = 0; i < textLine.length() - 1; i++){//last char must be '\n'
			if (textLine[i] == this->adSeparator){
				head[++index] = i + 1;
			}
			else len[index]++;
		}
		index = index | index;
		if (index + 1 != this->adItemNumber){
			throw std::invalid_argument("Receive negative adsText in AdsItem's constructor!");
		}
		else{
			auto GetItem = [&textLine, &head, &len](int index)->string {
				return textLine.substr(head[index], len[index]);
			};
			this->campaignId = GetItem(CampaignId);
			this->listingId = GetItem(ListingId);
			this->adId = GetItem(AdId);
			this->bidKeyWords = split(GetItem(BidKeyword), keywordSeparator);
			this->matchTypes = GetItem(Matchtypes);
			this->exactBid = this->ToInt(GetItem(ExactBid));
			this->phraseBid = this->ToInt(GetItem(PhraseBid));
			this->broadBid = this->ToInt(GetItem(BroadBid));
			this->actualAdTitle = GetItem(ActualAdTitle);
			this->actualAdDesc = GetItem(ActualAdDesc);
			this->actualDisplayURL = GetItem(ActualDisplayURL);
			this->actualDestinationURL = GetItem(ActualDestinationURL);
			this->matchTypeId = this->ToInt(GetItem(MatchTypeId));
		}
	}
	AdsItem() = delete;
};

class AdsInvertIndex{
public:
	/* save invert index */
	unordered_map<string, vector<AdsItem*>> adsMap;
	/* constructor */
	AdsInvertIndex(vector<AdsItem>& adsSet) : Weight(100, 10, 1){
		addAdsSet(adsSet);
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
			//createIndex_AdTitileKeywords(titleKeywords, adsItem);
			//createIndex_AdTextKeywords(textKeywords, adsItem);
		}
	}
	/* forbid copy constructor and assignment*/
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
			std::sort(ret.begin(),ret.end());
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

	void addToAdsMap(string& key, AdsItem& val){
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

};

vector<string>& loadFromFile(const string& fname, int maxItem = 0){
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
	return *adsLines;
}

vector<AdsItem> stringToAds(const vector<string>& lines){
	vector<AdsItem> allAds;
	allAds.reserve(lines.size());
	for (auto & x : lines){
		allAds.push_back(x);
	}
	return allAds;
}

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

int main() {
	using namespace std;

	string filename = "C:/Users/v-zeye/Desktop/Zhang Liangjie/AdsCorpus0809_900K_WithCampaignId.txt";
	clock_t begin, end;
	//1
	begin = clock();
	auto adsLines = loadFromFile(filename);
	end = clock();
	cout << end - begin << endl;
	//2
	begin = clock();
	//auto allAds = stringToAds(filename);
	auto allAds = stringToAds(adsLines);
	end = clock();
	cout << end - begin << endl;
	//3
	begin = clock();
	AdsInvertIndex index(allAds);
	end = clock();
	cout << end - begin;
	while (true){
		string x;
		cin >> x;
		auto ret = index.search(x, 10);
		for (auto & x : ret){
			x->print();
		}
		cout << endl;
	}
	return 0;
}