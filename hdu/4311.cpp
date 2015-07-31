#include <bits/stdc++.h>
using namespace std;
typedef pair<pair<int , int> , int> ppiii;
const int maxn = 100000 + 5;
int cx[2] , cy[2];
long long sx[2] , sy[2];
long long ans[maxn];
pair<pair<int , int> , int> p[maxn];
int n;
long long abs(long long x)
{
	return x < 0 ? -x : x;
}
bool cmp1(const ppiii &x , const ppiii &y)
{
	return x.first.first < y.first.first;
}
bool cmp2(const ppiii &x , const ppiii &y)
{
	return x.first.second < y.first.second;
}
void work()
{
	long long rans = 0x3f3f3f3f3f3f3f3fll;
	sx[0] = sx[1] = sy[0] = sy[1] = 0;
	scanf("%d" , &n);
	for (int i = 0 ; i < n ; i++)
	{
		scanf("%d%d" , &p[i].first.first , &p[i].first.second);
		ans[i] = 0;
		sx[1] += p[i].first.first;
		sy[1] += p[i].first.second;
		p[i].second = i;
	}
	cx[1] = n;
	cx[0] = 0;
	cy[1] = n;
	cy[0] = 0;
	sort(&p[0] , &p[n] , cmp1);
	for (int i = 0 ; i < n ; i++)
	{
		long long tx = p[i].first.first;
		sx[0] += tx;
		sx[1] -= tx;
		cx[0]++;
		cx[1]--;
		ans[p[i].second] += tx * cx[0] - sx[0] + sx[1] - tx * cx[1];
	}
	sort(&p[0] , &p[n] , cmp2);
	for (int i = 0 ; i < n ; i++)
	{
		long long ty = p[i].first.second;
		sy[0] += ty;
		sy[1] -= ty;
		cy[0]++;
		cy[1]--;
		ans[p[i].second] += ty * cy[0] - sy[0] + sy[1] - ty * cy[1];
	}
	for (int i = 0 ; i < n ; i++)
		rans = min(rans , ans[i]);
	printf("%lld\n" , rans);
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		work();
}
