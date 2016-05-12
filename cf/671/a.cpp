#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
const int maxn = 100000 + 1;
const double eps = 1e-8;

typedef pair<double, int> pdi;

double sqr(double x) {return x * x;}
double ax, ay, bx, by, tx, ty;
int n;
double p[maxn][2];
double d[maxn];
double sum;
vector<pdi> va, vb;
int main()
{
	ios::sync_with_stdio(0);
	cin >> ax >> ay >> bx >> by >> tx >> ty;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> p[i][0] >> p[i][1];
		d[i] = sqrt(sqr(p[i][0] - tx) + sqr(p[i][1] - ty));
		sum += d[i];
	}
	for (int i = 0; i < n; i++)
	{
		double da = sqrt(sqr(p[i][0] - ax) + sqr(p[i][1] - ay));
		double db = sqrt(sqr(p[i][0] - bx) + sqr(p[i][1] - by));

		va.push_back(pdi(d[i] - da, i));
		vb.push_back(pdi(d[i] - db, i));
	}

	sort(va.begin(), va.end(), greater<pdi>());
	sort(vb.begin(), vb.end(), greater<pdi>());
	
	double ans = 1e100;
	ans = min(sum * 2 - va[0].first, sum * 2 - vb[0].first);
	for (int i = 0; i < min((int)va.size(), 2); i++)
		for (int j = 0; j < min((int)vb.size(), 2); j++)
			if (va[i].second != vb[j].second)
				ans = min(ans, sum * 2 - va[i].first - vb[j].first);
	char buf[100];
	sprintf(buf, "%.12f\n", ans);
	cout << buf;
	return 0;
}
