#define _CRT_SECURE_NO_WARNINGS
#define __main__

#include <iostream>
#include <string>

#include <thread>
#include <ctime>

#include "AdsItem.h"
#include "AdsInvertIndex.h"
#include "RuntimeMethods.h"
#include "JasonParser.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
//#undef __main__

#define defaultProt "2587"
int main(int argc, char ** argv){
	if (argc == 1){
		std::cerr << "fail to open file!" << std::endl;
		exit(1);
	}
	//string filename(argv[1]);
	string filename("C:/Users/v-zeye/Desktop/ZhangLiangjie/AdsCorpus0809_900K_WithCampaignId.txt");
	AdsInvertIndex* IRINDEX = createInvertIndex(filename);
	cout << "start main loop" << endl;
	
	string outputDir = "C:/Users/v-zeye/Desktop/ZhangLiangjie/INDEX";
	IRINDEX->writeToFile(outputDir);
	//create socket and bind and deal with jason.
	//using rapidjason

	//int count = 0;
	//string q;
	//while (true){
	//	cin >> q;
	//	if (q == "-quit") break;
	//	auto ret = IRINDEX->search(q, 10);
	//	for (auto & x: ret){
	//		x->print();
	//	}
	//}
	return 0;
}