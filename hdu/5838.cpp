#include <bits/stdc++.h>
using namespace std;

const int mod = 772002;

const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1, 0};
const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1, 0};
char mp[8][8];
int flg[8][8], bm[1 << 9], cbit[1 << 9];
int dp[30][1 << 9];
int ans[10];
vector<pair<int, int> > X, O;
int n, m;
#define x first
#define y second
int sel(int mask)
{
	int ret = 0;
	memset(flg, 0, sizeof(flg));
	for (int k = 0; k < X.size(); k++)
		if ((mask & (1 << k)) == 0)
			for (int d = 0; d < 9; d++)
				flg[X[k].x + dx[d]][X[k].y + dy[d]] = 1;
		else
			flg[X[k].x][X[k].y] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (flg[i][j] == 0)
				ret++;
	return ret;
}

void dfs(int level, int cnt)
{
	if (level == O.size())
	{
		for (int i = 0; i < (1 << X.size()); i++)
			bm[i] = sel(i);
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 1; i <= n * m; i++)
			for (int j = 0; j < (1 << (X.size())); j++)
			{
				dp[i][j] = dp[i - 1][j] * (bm[j] - i + 1 + cbit[j]);
				for (int k = 0; k < X.size(); k++)
					if (j & (1 << k))
						dp[i][j] += dp[i - 1][j ^ (1 << k)];
				dp[i][j] %= mod;
			}
		ans[cnt] += dp[n * m][(1 << (X.size())) - 1];
		ans[cnt] %= mod;
		return;
	}
	bool cango = 1;
	for (int i = 0; i < 8; i++)
		if (mp[O[level].x + dx[i]][O[level].y + dy[i]] == 'X')
			cango = 0;
	if (cango)
	{
		X.push_back(O[level]);
		mp[O[level].x][O[level].y] = 'X';
		dfs(level + 1, cnt + 1);
		mp[O[level].x][O[level].y] = '.';
		X.pop_back();
	}
	dfs(level + 1, cnt);
}

int sol()
{
	memset(mp, 0, sizeof(mp));
	for (int i = 1; i <= n; i++)
		scanf("%s", mp[i] + 1);
	X.clear();
	O.clear();
	memset(ans, 0, sizeof(ans));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (mp[i][j] == 'X')
			{
				X.push_back(make_pair(i, j));
				for (int k = 0; k < 8; k++)
					if (mp[i + dx[k]][j + dy[k]] == 'X')
						return 0;
			} else
				O.push_back(make_pair(i, j));
	dfs(0, 0);
	for (int i = 8; i >= 0; i--)
		ans[i] = (ans[i] + mod - ans[i + 1]) % mod;
	return ans[0];
}
int countbit(int x)
{
	int ret = 0;
	while (x)
	{
		ret += (x & 1);
		x >>= 1;
	}
	return ret;
}
int main()
{
	int cas = 0;
	for (int i = 0; i < (1 << 9); i++)
		cbit[i] = countbit(i);
	while (~scanf("%d%d", &n, &m))
		printf("Case #%d: %d\n", ++cas, sol());
	return 0;
}
