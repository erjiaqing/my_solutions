#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
typedef pair< pair<double , double> , int > ppiii;
ppiii p[maxn];
double ans[maxn] , s2 = sqrt(2);
double sx[2] , sy[2];
double cx[2] , cy[2];
int n;
bool comp1(const ppiii &a,const ppiii &b)
{
	return a.first.first < b.first.first;
}
bool comp2(const ppiii &a,const ppiii &b)
{
	return a.first.second < b.first.second;
}
void work()
{
	sx[0] = sx[1] = sy[0] = sy[1] = 0;
	cx[0] = cx[1] = cy[0] = cy[1] = 0;
	memset(ans , 0 , sizeof(ans));
	scanf("%d" , &n);
	for (int i = 0 ; i < n ; i++)
	{
		double ox , oy , nx , ny;
		scanf("%lf%lf" , &ox , &oy);
		nx = oy;ny = -ox;
		nx = (ox + nx) / 2;
		ny = (oy + ny) / 2;
		p[i].first.first = nx;
		p[i].first.second = ny;
		sx[1] += nx;
		sy[1] += ny;
		p[i].second = i;
	}
	cx[1] = cy[1] = n;
	sort(&p[0] , &p[n] , comp1);
	for (int i = 0 ; i < n ; i++)
	{
		double xx = p[i].first.first;
		cx[0]++;cx[1]--;
		sx[0] += xx;sx[1] -= xx;
		ans[p[i].second] += cx[0] * xx - sx[0] + sx[1] - cx[1] * xx;
	}
	sort(&p[0] , &p[n] , comp2);
	for (int i = 0 ; i < n ; i++)
	{
		double yy = p[i].first.second;
		cy[0]++;cy[1]--;
		sy[0] += yy;sy[1] -= yy;
		ans[p[i].second] += cy[0] * yy - sy[0] + sy[1] - cy[1] * yy;
	}
	double rans = 1e15;
	for (int i = 0 ; i < n ; i++)
		rans = min(rans , ans[i]);
	printf("%.0f\n" , rans);
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		work();
	return 0;
}
