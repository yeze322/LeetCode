class Vec{
public:
	int length(){return len;}
private:
	int len;
};

class Vec2{
public:
	int length() const {return len;}
	int hehe(){return 0;}
private:
	int len;
};
class mmap{
public:
	mmap(int a){memory_ptr = new char [a];}
private:
	char *memory_ptr;
};
int padd_len(const Vec2& v, int n){
	int k = v.length();
	//int k2 = v.hehe();
	n = k;
	return n;
}
#include <string>
using namespace std;
class B{
public:
	string s;
};

class D:public B{
public:
	string t;
};
class A{
public:
	A(int a = 10){name = new char[100];}
	~A(){delete [] name;}
	A& operator = (const A&);
private:
	char *name;
};
A& A::operator=(const A&base){
	A *copy = new A;
	strcpy(copy->name,base.name);
	return *this;
}
void function(const A& base)
{
	A copy = base;
}

class wrong{
public:
	wrong(wrong& origion){data = origion.data;}
private:
	int data;
};

class Com{
public:
	Com operator+(const Com& x);
};
#include <stdlib.h>
int main()
{
	char *p = (char*)calloc(0,1);
}
