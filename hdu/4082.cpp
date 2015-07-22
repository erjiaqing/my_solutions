#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 20;
int gcd(int a , int b)
{
	if (b == 0) return a;
	return gcd(b , a % b);
}
int sqr(int x)
{
	return x * x;
}
struct TA {
	int A , B , C;
	void build (int _a , int _b , int _c)
	{
		int ta[] = {_a , _b , _c};
		sort(ta , ta + 3);
		int _gcd = gcd(gcd(_a , _b) , _c);
		A = ta[0] / _gcd;
		B = ta[1] / _gcd;
		C = ta[2] / _gcd;
//		fprintf(stderr , "%d %d %d\n" , A , B , C);
	}
}T[maxn * maxn * maxn];
#define x first
#define y second
pair<int , int> P[maxn];
bool comp(const TA &x , const TA &y)
{
	if (x.A < y.A) return true;
	if (x.A == y.A && x.B < y.B) return true;
	if (x.A == y.A && x.B == y.B) return x.C < y.C;
	return false;
}
bool same(const TA &x , const TA &y)
{
	return (x.A == y.A) && (x.B == y.B) && (x.C == y.C);
}
bool work()
{
	int n , tc = 0 , ans = 1 , maxans = 0;
	cin >> n;
	if (n == 0) return false;
	for (int i = 0 ; i < n ; i++)
		cin >> P[i].x >> P[i].y;
	sort(&P[0] , &P[n]);
	n = unique(&P[0] , &P[n]) - &P[0];
	for (int i = 0 ; i < n ; i++)
		for (int j = i + 1 ; j < n ; j++)
			for (int k = j + 1 ; k < n ; k++)
				if (P[i] != P[j] && P[j] != P[k] && (P[i].x - P[j].x) * (P[j].y - P[k].y) != (P[j].x - P[k].x) * (P[i].y - P[j].y))
				{
//					fprintf(stderr , "(%d , %d) (%d , %d) (%d , %d)\n" , P[i].x , P[i].y , P[j].x , P[j].y , P[k].x , P[k].y);
					T[tc++].build(sqr(P[i].x - P[j].x) + sqr(P[i].y - P[j].y) , sqr(P[j].x - P[k].x) + sqr(P[j].y - P[k].y) , sqr(P[k].x - P[i].x) + sqr(P[k].y - P[i].y));
				}
	if (tc)
	{
		sort(&T[0] , &T[tc] , comp);
		maxans = 1;
	}
	for (int i = 1 ; i < tc ; i++)
	{
		if (same(T[i - 1] , T[i]))
			ans++;
		else
			ans = 1;
		maxans = max(ans , maxans);
	}
	printf("%d\n" , maxans);
	return true;
}
int main()
{
	while (work());
	return 0;
}
