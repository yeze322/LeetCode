#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <set>
#include <sstream>
using std::stringstream;
using std::cin;
using std::cout;
using std::endl;
using std::string;

class BOX{
public:
	int red;
	int yellow;
	int blue;
	BOX(): red(0), yellow(0), blue(0) {};
	inline void input(char);
	inline bool exam();
	string minus;

};

void BOX::input(char ball){
	switch (ball)
	{
	case 'R':red++;break;
	case 'Y':yellow++;break;
	case 'B':blue++;break;
	}//put in balls
}

bool BOX::exam()
{
	int a[3];
	a[0] = abs(red-yellow);
	a[1] = abs(red-blue);
	a[2] = abs(blue-yellow);
	//cout<<"ball: "<<a[0]<<a[1]<<a[2]<<endl;

	if(a[0]>a[1]){
		a[0] ^= a[1];
		a[1] ^= a[0];
		a[0] ^= a[1];
	}
	if(a[1]>a[2]){
		a[2] ^= a[1];
		a[1] ^= a[2];
		a[2] ^= a[1];
	}
	if(a[0]>a[1]){
		a[0] ^= a[1];
		a[1] ^= a[0];
		a[0] ^= a[1];
	}
	string compare;
	stringstream out;
	out<<a[2]*10000+a[1]*100+a[0];
	compare = out.str();
	//cout<<"ball: "<<a[0]<<a[1]<<a[2]<<endl;
	//cout<<compare<<endl;
	if (compare==minus)
		return false;
	else
		return true;
}

int main()
{
	int xyz[3];
	string balls;
	while(cin>>xyz[0]>>xyz[1]>>xyz[2]>>balls){
		BOX box;
		if(xyz[0]>xyz[1]){
			xyz[0] ^= xyz[1];
			xyz[1] ^= xyz[0];
			xyz[0] ^= xyz[1];
		}
		if(xyz[1]>xyz[2]){
			xyz[2] ^= xyz[1];
			xyz[1] ^= xyz[2];
			xyz[2] ^= xyz[1];
		}
		if(xyz[0]>xyz[1]){
			xyz[0] ^= xyz[1];
			xyz[1] ^= xyz[0];
			xyz[0] ^= xyz[1];
		}
		stringstream out;
		out<<xyz[2]*10000+xyz[1]*100+xyz[0];
		box.minus = out.str();
		//cout<<box.minus<<endl;
		int len = balls.length();
		int max = 0;
		int most = 0;
		for(int i=0;i<len;++i){
			box.input(balls[i]);
			max++;
			if(!box.exam()){
				if(most<max)
					most = max;
				box.red = box.yellow = box.blue = 0;
				max = 0;
			}
		}
		if(most<max)
			most = max;
		cout<<most<<endl;
	}
	return 0;
}