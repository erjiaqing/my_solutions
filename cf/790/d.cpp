#include <bits/stdc++.h>
using namespace std;

const int maxn = 300000 + 5;
int c[maxn][3];
int nxt[maxn][3];
int mat[maxn][2];
long long sum[maxn][3];
map<long long, int> gnxt[3];
int li[maxn][3], lj[maxn][3];
int n;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &mat[i][0]);
	for (int i = 1; i <= n; i++) scanf("%d", &mat[i][1]);
	for (int i = 1; i <= n; i++)
	{
		sum[i][0] = sum[i - 1][0] + mat[i][0];
		sum[i][1] = sum[i - 1][1] + mat[i][1];
		sum[i][2] = sum[i][0] + sum[i][1];
	}
	nxt[n][0] = nxt[n][1] = nxt[n][2] = n + 1;
	for (int i = n; i >= 0; i--)
	{
		if (i != n)
		{
			nxt[i][0] = gnxt[0][sum[i][0]];
			nxt[i][1] = gnxt[1][sum[i][1]];
			nxt[i][2] = gnxt[2][sum[i][2]];
		}
		gnxt[0][sum[i][0]] = i;
		gnxt[1][sum[i][1]] = i;
		gnxt[2][sum[i][2]] = i;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (nxt[i][0]) nxt[i][0] = min(nxt[i][0], nxt[i + 1][0]);
		else nxt[i][0] = nxt[i + 1][0];
		if (nxt[i][1]) nxt[i][1] = min(nxt[i][1], nxt[i + 1][1]);
		else nxt[i][1] = nxt[i + 1][1];
		if (nxt[i][2]) nxt[i][2] = min(nxt[i][2], nxt[i + 1][2]);
		else nxt[i][2] = nxt[i + 1][2];
	}
	//	for (int i = 0; i <= n; i++)
	//		printf("%d %d %d\n", nxt[i][0], nxt[i][1], nxt[i][2]);
	//--
	for (int i = 0; i <= n; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			int j1 = nxt[li[i][k]][0];
			int j2 = nxt[lj[i][k]][1];
			if (j1 == j2)
			{
				if (c[j1][2] < c[i][k] + 2)
				{
					c[j1][2] = c[i][k] + 2;
					li[j1][2] = lj[j1][2] = j1;
				}
			} else
			{
				if (c[j1][0] < c[i][k] + 1 || (c[j1][0] == c[i][k] + 1 && lj[i][k] < lj[j1][0]))
				{
					c[j1][0] = c[i][k] + 1;
					li[j1][0] = j1;
					lj[j1][0] = lj[i][k];
				}
				if (c[j2][1] < c[i][k] + 1 || (c[j2][1] == c[i][k] + 1 && li[i][k] < li[j2][1]))
				{
					c[j2][1] = c[i][k] + 1;
					li[j2][1] = li[i][k];
					lj[j2][1] = j2;
				}
			}
			int h2 = nxt[i][2];
			if (c[h2][2] < c[i][k] + 1)
			{
				c[h2][2] = c[i][k] + 1;
				li[h2][2] = lj[h2][2] = h2;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= n; i++) for (int k = 0; k < 3; k++) ans = max(ans, c[i][k]);
	cout << ans << endl;
	return 0;
}
