#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;

int n, m;
vector<int> v;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
vector<pipii> e;
int fa[maxn];

#define x first
#define y second

int getfa(int x)
{
	return (fa[x] == x) ? x : (fa[x] = getfa(fa[x]));
}

void unionfa(int u, int v)
{
	fa[getfa(u)] = getfa(v);
}

int sol()
{
	e.clear();
	v.clear();
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e.push_back(pipii(w, pii(u, v)));
	}
	sort(e.begin(), e.end());
	for (auto ed : e)
		if (getfa(ed.y.x) != getfa(ed.y.y))
		{
			unionfa(ed.y.x, ed.y.y);
			v.push_back(ed.x);
		}
	return v[v.size() / 2];
}

int main()
{
	while ((~scanf("%d%d", &n, &m)) && (n + m))
		printf("%d\n", sol());
	return 0;
}
