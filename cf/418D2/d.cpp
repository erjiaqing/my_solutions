#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;

struct circ{
	long long x, y, r;
};

vector<int> e[maxn];
vector<circ> c;

long long sqr(long long x) {return x * x;}

int dep[maxn];

const double pi = acos(-1);

void dfs(int u)
{
	for (int v : e[u])
	{
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		long long x, y, r;
		scanf("%lld%lld%lld", &x, &y, &r);
		circ t = {x, y, r};
		c.push_back(t);
	}
	sort(c.begin(), c.end(), [](const circ &a, const circ &b) {
		return a.r > b.r;
		});
	for (int i = 0; i < n; i++)
		for (int j = i - 1; j >= 0; j--)
			if (sqr(c[i].x - c[j].x) + sqr(c[i].y - c[j].y) <= sqr(c[j].r))
			{
				e[j].push_back(i);
				break;
			}
	memset(dep, -1, sizeof dep);
	for (int i = 0; i < n; i++)
		if (dep[i] == -1)
		{
			dep[i] = 0;
			dfs(i);
		}
	long long tans = 0;
	double ans = 0;
	for (int i = 0; i < n; i++)
	{
		cerr << c[i].x << ' ' << c[i].y << ' ' << c[i].r << ' ' << dep[i] << endl;
		if (dep[i] % 4 <= 1)
			tans += sqr(c[i].r);
		else
			tans -= sqr(c[i].r);
	}
	printf("%.10f\n", pi * tans);
	return 0;
}
