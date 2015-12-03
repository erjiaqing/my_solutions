#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <string>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 120 + 5;
struct planet{
	string s;
	double x, y, z;
	void read() {
		cin >> s >> x >> y >> z;
	}
}p[maxn];
double d[maxn][maxn];
map<string, int> sid;
int n;
double sqr(double x){return x * x;}
double getln(int i, int j)
{
	return sqrt(sqr(p[i].x - p[j].x) +
	sqr(p[i].y - p[j].y) +
	sqr(p[i].z - p[j].z));
}
void work()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		p[i].read();
		sid[p[i].s] = i;
	}
	for (int i = 0; i < maxn; i++)
		for (int j = 0; j < maxn; j++)
			d[i][j] = 1e50;
	for (int i = 0; i < n; i++)
		d[i][i] = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			d[i][j] = d[j][i] = getln(i, j);
	int wh;
	cin >> wh;
	for (int i = 0; i < wh; i++)
	{
		string s1, s2;
		int i1, i2;
		cin >> s1 >> s2;
		i1 = sid[s1];
		i2 = sid[s2];
		d[i1][i2]= 0;
	}
	/*for (int i = 0; i < n; i++, (cerr << endl))
		for (int j = 0; j < n; j++)
			cerr << d[i][j] << "\t";*/
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	int query;
	cin >> query;
	for (int i = 0; i < query; i++)
	{
		string s1, s2;
		int i1, i2;
		cin >> s1 >> s2;
		i1 = sid[s1];
		i2 = sid[s2];
		double ans = 1e100;
		//cerr << i1 << " " << i2 << endl;
		/*ans = min(ans, d[i1][n + i2]);
		ans = min(ans, d[i1 + n][i2]);
		ans = min(ans, d[i1 + n][i2 + n]);
		ans = min(ans, d[i2 + n][i1 + n]);
		ans = min(ans, d[i2 + n][i1]);
		ans = min(ans, d[i1 + n][i2]);*/
		printf("The distance from %s to %s is %.0f parsecs.\n", p[i1].s.c_str(), p[i2].s.c_str(), d[i1][i2]);
	}
}
int main()
{
	//ios::sync_with_stdio(0);
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		printf("Case %d:\n", i);
		work();
	}
	return 0;
}
