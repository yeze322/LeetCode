#define u vector
#include <cstdio>
#include <vector>
using std::u;

struct v{
	int r;
	int d;
	u<int> e;
	v():r(0),d(0){}
};
#define p push_back
#define q 142857
#define s scanf
#define f(x,y) for(int i=x;i<y;i++)
int main()
{
	int N,M,K;
	s("%d %d %d",&N,&M,&K);
	int T = 0;
	u<v> L(N+1);
	int _;
	f(0,K){s("%d",&_);L[_].r = 1;}
	int l,g;
	f(0,M){s("%d %d",&l,&g);L[l].e.p(g);L[g].d++;}
	u<v*> z;
	f(1,N+1){if(L[i].d == 0)z.p(&L[i]);}
	while(!z.empty()){
		u<v*> n;
		for(v *x:z){
			int a = (x->r)%q;
			T = (T + a)%q;
			for(int t : x->e){
				L[t].d--;
				if(L[t].d == 0)
					n.p(&L[t]);
				L[t].r += a;
			}
		}
		z = n;
	}
	printf("%d\n",T);
	return 0;
}