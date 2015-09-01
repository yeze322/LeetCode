#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

vector<string> split(const string  &s, char delim) {
	vector<string> result;
	std::stringstream ss(s);
	string item;
	//to much copy here... not solved
	while (std::getline(ss, item, delim))
		result.push_back(item);
	return result;
}

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
		cout << adId << "|" << actualAdTitle <<"|"<< actualAdTitle << "|" << exactBid << endl;
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