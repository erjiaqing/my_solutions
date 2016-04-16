#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
int nxt[maxn], rnxt[maxn], vis[maxn], mxl[maxn];
//int incircle[maxn];
vector<int> ln[maxn];
void dfs1(int u, int x)
{
	//cerr << "dfs1 " << u << " " << x << endl;
	if (vis[x])
	{
		if (x != u) return;
		for (int i = 0; i < (int)ln[u].size(); i++){
			nxt[ln[u][i]] = 0;
		}
		return;
	}
	vis[x] = true;
	ln[u].push_back(x);
	if (nxt[x])
		dfs1(u, nxt[x]);
}
void dfs2(int x, int ln)
{
	mxl[x] = max(mxl[x], ln);
	if (nxt[x])
		dfs2(nxt[x], ln + 1);
}
int sol()
{
	int n, t, ans = 0;
	cin >> n;
	memset(nxt, 0, sizeof(nxt));
	memset(rnxt, 0, sizeof(rnxt));
	memset(vis, 0, sizeof(vis));
	memset(mxl, 0, sizeof(mxl));
	for (int i = 1; i <= n; i++)
	{
		cin >> t;
		ln[i].clear();
		nxt[i] = rnxt[i] = t;
	}
	for (int i = 1; i <= n; i++)
		memset(vis, 0, sizeof(vis)), dfs1(i, i);
	for (int i = 1; i <= n; i++)
		if (nxt[i] == 0)
			ans = max(ans, (int)ln[i].size());
	for (int i = 1; i <= n; i++)
		dfs2(i, 1);
	int tans = 0;
	for (int i = 1; i <= n; i++)
		if (rnxt[rnxt[i]] == i && rnxt[i] > i)
			tans += mxl[i] + mxl[rnxt[i]];
	ans = max(ans, tans);
	return ans;
}
int main()
{
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
		cout << "Case #" << i << ": " << sol() << endl;
	return 0;
}
