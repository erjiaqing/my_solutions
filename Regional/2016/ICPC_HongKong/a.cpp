#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
vector<int> e[maxn];
vector<int> path[maxn][maxn];
int colo[20001][maxn];
int target[maxn];
int appear[maxn];
int cur;

int dist[maxn][maxn];
int pre[maxn][maxn];
int n, k, m;

void calc_path(int u0, int *dst, int *pre)
{
	queue<int> q;
	q.push(u0);
	dst[u0] = 0;
	pre[u0] = u0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int v : e[u])
		{
			if (dst[v] > dst[u] + 1)
			{
				dst[v] = dst[u] + 1;
				pre[v] = u;
				q.push(v);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		int cur = i;
		if (dist[u0][i] > 200) continue;
		stack<int> s;
		while (cur != u0)
		{
			s.push(cur);
			cur = pre[cur];
		}
		path[u0][i].push_back(u0);
		while (!s.empty())
		{
			path[u0][i].push_back(s.top());
			s.pop();
		}
	}
}

bool check()
{
	for (int i = 1; i <= n; i++)
		if (colo[cur][i] != target[i]) return true;
	return false;
}

void newline()
{
	cur++;
	for (int i = 1; i <= n; i++)
		colo[cur][i] = colo[cur - 1][i];
}

#define _u path[u][v][i - 1]
#define _v path[u][v][i]
void swap_path(int u, int v)
{
	for (int i = 1; i < path[u][v].size(); i++)
	{
		newline();
		swap(colo[cur][_u], colo[cur][_v]);
	}
	for (int i = path[u][v].size() - 2; i >= 1; i--)
	{
		newline();
		swap(colo[cur][_u], colo[cur][_v]);
	}
}

void set_path(int u, int v)
{
	for (int i = 1; i < path[u][v].size() - 1; i++)
	{
		newline();
		swap(colo[cur][_u], colo[cur][_v]);
	}
	newline();
	colo[cur][path[u][v][path[u][v].size() - 1]] = colo[cur][path[u][v][path[u][v].size() - 2]];
	for (int i = path[u][v].size() - 2; i >= 1; i--)
	{
		newline();
		swap(colo[cur][_u], colo[cur][_v]);
	}
}
#undef _u
#undef _v

int main()
{
	memset(dist, 0x3f, sizeof dist);
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &colo[cur][i]);
		appear[colo[cur][i]] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &target[i]);
		if (appear[target[i]] == 0)
		{
			puts("Impossible\n");
			return 0;
		}
	}
	for (int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) calc_path(i, dist[i], pre[i]);
	while (check())
	{
		int u, v, flg = 0;
		for (int i = 1; i <= n && !flg; i++)
			for (int j = 1; j <= n && !flg; j++)
			{
				if (colo[cur][i] != target[i] &&
					colo[cur][j] != target[j] &&
					colo[cur][i] == target[j] &&
					colo[cur][j] == target[i])
				{
					u = i;
					v = j;
					flg = 1;
				}
			}
		for (int i = 1; i <= n && !flg; i++)
			for (int j = 1; j <= n && !flg; j++)
			{
				if (colo[cur][i] == target[j] &&
					colo[cur][j] != target[j] &&
					colo[cur][i] != target[i])
				{
					u = i;
					v = j;
					flg = 2;
				}
			}
		for (int i = 1; i <= n && !flg; i++)
			for (int j = 1; j <= n && !flg; j++)
			{
				if (colo[cur][j] != target[j] &&
					colo[cur][i] == target[j])
				{
					u = i;
					v = j;
					flg = 3;
				}
			}
		if (flg == 1 || flg == 2)
			swap_path(u, v);
		else if (flg == 3)
			set_path(u, v);
	}
	for (int i = 0; i <= cur; i++)
		for (int j = 1; j <= n; j++)
			printf("%d%c", colo[i][j], j != n ? ' ' : '\n');
	return 0;
}
