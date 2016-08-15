#include <bits/stdc++.h>
using namespace std;

const int maxn = 55;
bool g[maxn][maxn][maxn][maxn];
int f[maxn][maxn][maxn][maxn], n, m;
int vis[maxn][maxn][maxn][maxn];
char mp[maxn][maxn];

typedef pair<int, int> pii;
#define x first
#define y second
vector<pii> go[26];

int mx4(int a, int b, int c, int d){return max(max(a, b), max(c, d));}

int dfs(int u, int v, int x, int y)
{
	if (u == x && v == y) return 0;
	if (u == x && v + 1 == y) return ((mp[u][v] - mp[x][y]) == ('a' - 'A'));
	if (u + 1 == x && v == y) return ((mp[u][v] - mp[x][y]) == ('a' - 'A'));
	if (!g[u][v][x][y]) return -9999;
	if (vis[u][v][x][y]) return f[u][v][x][y];
	vis[u][v][x][y] = 1;
	int ret = 0;
	if ('a' <= mp[u][v] && mp[u][v] <= 'z')
	{
		int ty = mp[u][v] - 'a';
		for (pii nx : go[ty])
			if (g[u][v][nx.x][nx.y] && g[nx.x][nx.y][x][y])
				ret = max(ret,
						max(1,
							mx4(
							dfs(u + 1, v, nx.x - 1, nx.y),
							dfs(u + 1, v, nx.x, nx.y - 1),
							dfs(u, v + 1, nx.x - 1, nx.y),
							dfs(u, v + 1, nx.x, nx.y - 1)) + 1) + mx4(0, 0, dfs(nx.x + 1, nx.y, x, y), dfs(nx.x, nx.y + 1, x, y)));
	}
	return f[u][v][x][y] = max(ret, max(dfs(u + 1, v, x, y), dfs(u, v + 1, x, y)));
}

int sol()
{
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));
	memset(vis, 0, sizeof(vis));
//	for (int i = 0; i < 26; i++) fr[i].clear();
	for (int i = 0; i < 26; i++) go[i].clear();
	for (int i = 1; i <= n; i++)
		scanf("%s", mp[i] + 1);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (mp[i][j] == '#') continue;
			//if ('a' <= mp[i][j] && mp[i][j] <= 'z') fr[mp[i][j] - 'a'].push_back(pii(i, j));
			if ('A' <= mp[i][j] && mp[i][j] <= 'Z') go[mp[i][j] - 'A'].push_back(pii(i, j));
			g[i][j][i][j] = 1;
			for (int k = i; k <= n; k++)
			{
				for (int l = j; l <= m; l++)
				{
					if (i == k && l == j) continue;
					if (mp[k][l] == '#') continue;
					g[i][j][k][l] = (g[i][j][k - 1][l] || g[i][j][k][l - 1]);
				}
			}
		}
	}
	if (!g[1][1][n][m]) return -1;
	return dfs(1, 1, n, m);
}

int main()
{
	while ((~scanf("%d%d", &n, &m)) && n)
		printf("%d\n", sol());
	return 0;
}
