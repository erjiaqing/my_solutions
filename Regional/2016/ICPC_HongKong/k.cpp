#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
const int maxm = 300000 + 5;
vector<int> bel[maxn];
vector<int> cls[maxm];
vector<int> e[maxm];
vector<int> play[maxm];
vector<int> rplay[maxm];
int sz[maxm], fa[maxm], ufs[maxm];
bool cmp(int i, int j)
{
	return sz[i] < sz[j];
}

int findfa(int x)
{
	if (ufs[x] != x)
		return ufs[x] = findfa(ufs[x]);
	return x;
}

void merge(int u, int v)
{
	ufs[findfa(v)] = findfa(u);
}

void dfs(int u)
{
	int tsum = 0;
	for (int v : e[u]) tsum += sz[v];
//	cerr << tsum << ' ' << u << ' ' << sz[u] << endl;
	if (tsum != sz[u])
		return;
	for (int v : e[u])
		dfs(v);
	size_t mxsize = play[e[u][0]].size();
	for (int i = 1; i < e[u].size(); i++)
	{
		int v = e[u][i];
		mxsize = min(mxsize, play[v].size());
		for (int j = 0; j < mxsize; j++)
			merge(play[e[u][0]][j], play[v][j]);
	}
	for (int i = 0; i < mxsize; i++)
		play[u].push_back(play[e[u][0]][i]);
}

int main()
{
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= p; i++) ufs[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int cn;
		scanf("%d", &cn);
		sz[i] = cn;
		for (int j = 0; j < cn; j++)
		{
			int si;
			scanf("%d", &si);
			bel[si].push_back(i);
			cls[cn].push_back(si);
		}
	}
	for (int i = 1; i <= n; i++)
		sort(bel[i].begin(), bel[i].end(), cmp);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < bel[i].size(); j++)
			if (!fa[bel[i][j - 1]])
				fa[bel[i][j - 1]] = bel[i][j];
//	for (int i = 1; i <= m; i++)
//		cerr << fa[i] << endl;;
	for (int i = 1; i <= m; i++)
		e[fa[i]].push_back(i);
//	for (int i = 1; i <= n; i++)
	for (int i = 1; i <= p; i++)
	{
		int cp;
		scanf("%d", &cp);
		play[cp].push_back(i);
	}
	sz[0] = n;
	dfs(0);
//	for (int i = 1; i <= p; i++)
//		findfa(i);
	for (int i = 1; i <= p; i++)
		rplay[findfa(i)].push_back(i);
//	for (int v : play[0].size())
	printf("%d\n", (int)play[0].size());
	for (int v : play[0])
	{
		int cr = findfa(v);
		printf("%d", (int)rplay[cr].size());
		for (int r : rplay[cr])
			printf(" %d", r);
		printf("\n");
	}
	return 0;
}
