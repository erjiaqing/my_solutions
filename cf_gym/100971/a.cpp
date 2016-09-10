#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 52;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m;
char mp[maxn][maxn];
int fa[maxn * maxn];
int id[maxn][maxn], tid = 0;
int flg = 0;

void f(int x) {return x == fa[x] ? x : fa[x] = f(fa[x]);}

void dfs(int x, int y, int num)
{
	id[x][y] = num
	for (int i = 0; i < 4; i++)
		if (!id[x + dx[i]][y + dy[i]] && mp[x + dx[i]][y + dy[i]] == '.')
			dfs(x + dx[i], y + dy[i], num);
}
int main()
{
	ios::sync_with_stdio(0);
	memset(mp, '#', sizeof(mp));
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> &mp[i][1];
		mp[i][m + 1] = '#';
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if(id[i][j] == 0 && mp[i][j] == '.')
				dfs(i, j, ++tid);
			else if (mp[i][j] == '?')
				id[i][j] = ++tid;
	return 0;
}
