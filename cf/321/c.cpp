#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
char res[maxn];
int vis[maxn];
char mx[maxn];
vector<int> e[maxn];
int deg[maxn];
vector<int> q;
char mn = 'Z';
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
	{
		if (e[i].size() == 1)
		{
			q.push_back(i);
			mx[i] = res[i] = 'Z';
		}
		deg[i] = e[i].size();
	}
	int tr = 0;
	while (tr < q.size())
	{
		int v = q[tr];
		char tans = 0;
		int avail[27];
		memset(avail, 0, sizeof(avail));
		vis[v] = true;
		//cerr << v << endl;
		for (int nx : e[v])
		{
			if (vis[nx])
			{
				if (res[nx] == mx[nx])
					avail[res[nx] - 'A']++;
				else
					avail[mx[nx] - 'A']++,avail[res[nx] - 'A']++;
				mx[v] = min(mx[v] ? mx[v] : 'Z', min(res[nx], mx[nx]));
			} else {
				deg[nx]--;
				if (deg[nx] == 1)
					q.push_back(nx);
			}
		}
		bool flg = 0;

		for (int j = 0; j <= 25; j++)
			if (avail[j] == 2 && j && (avail[j - 1] == 0))
			{
				res[v] = j - 1 + 'A';
				break;
			}
			else if (avail[j] == 0)
				res[v] = j + 'A';
		/*
		for (int j = 25; j >= 0; j--)
			if (avail[j] == 0)
			{
				res[v] = ('A' + j);
				break;
			}*/
		//cerr << v << ": " << res[v] << endl;
		mx[v] = min(mx[v] ? mx[v] : 'Z', res[v]);
		mn = min(mn ? mn : 'Z', res[v]);
		if (!res[v])
		{
			printf("Impossible\n");
			return 0;
		}
		tr++;
	}
	for (int i = 1; i <= n; i++)
		printf("%c%s", res[i] - (mn - 'A'), i == n ? "\n" : " ");
	return 0;
}
