#include <algorithm>
#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
struct Work {
	int a, b, d;
	Work(){}
	Work(int _a, int _b, int _d):a(_a), b(_b), d(_d){}
};
bool operator < (const Work &_a, const Work &_b)
{
	return _a.d > _b.d ||
		   ( _a.d == _b.d && _a.a < _b.a );
}
priority_queue < Work > To , Fi;
int _min ( int a, int b) {return a < b ? a : b;}
void work()
{
	int ta, tb, td;
	int n;
   	double pz = 0;
	int t2, ti = 0;
	Work tmp, tmp2;
	scanf("%d", &n);
	for (int i = 0;i < n; i++) scanf("%d%d%d", &ta, &tb, &td),To.push(Work(ta, tb, td));
	for (int i = 0;i < n; i++)
	{
		tmp = To.top();To.pop();
		ti += tmp.b;
		Fi.push(Work(tmp.a, tmp.b, 0));
		while ( ti > tmp.d )
		{
			tmp2 = Fi.top();Fi.pop();
			t2 = _min ( ti - tmp.d , tmp2.b );
			ti -= t2;pz += 1.0 * t2 / tmp2.a;
			tmp2.b -= t2;
			if ( tmp2.b ) Fi.push(tmp2);
		}
	}
	printf("%.2f\n", pz);
}
int main()
{
	work();
	return 0;
}
