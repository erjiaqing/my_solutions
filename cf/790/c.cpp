#include <bits/stdc++.h>
using namespace std;

const int maxn = 75 + 5;
int dp[maxn][maxn][maxn][2];
char s[maxn];
int n, cv, ck, cx;

char tbuf[maxn];
int prevhash = -1;

int gettrans(int v, int k, int x, int l, char need)
{
	int cur = 0, tcv(0), tck(0), tcx(0);
	if (l == 1 && need == 'K') return 0x3f3f3f3f;
	if (prevhash != v * 80 * 80 + k * 80 + x)
	{
		for (int i = 0; i < n; i++)
		{
			if (s[i] == 'V')
			{
				if (tcv < v) tcv++;
				else tbuf[cur++] = 'V';
			} else if (s[i] == 'K')
			{
				if (tck < k) tck++;
				else tbuf[cur++] = 'K';
			} else
			{
				if (tcx < x) tcx++;
				else tbuf[cur++] = 'X';
			}
		}
		tbuf[cur] = 0;
	}
//	printf("<%s> %d %d %d %d\n", tbuf, v, k, x, l);
	prevhash = (v * 80 * 80 + k * 80 + x);
	for (int i = 0; tbuf[i]; i++)
		if (tbuf[i] == need) return i;
	return 0x3f3f3f3f;
}

int main()
{
	cin >> n >> s;
	for (int i = 0; s[i]; i++)
		if (s[i] == 'V') cv++;
		else if (s[i] == 'K') ck++;
		else cx++;
	memset(dp, 0x3f, sizeof dp);
	dp[0][0][0][0] = 0;
	for (int i = 0; i <= cv; i++)
		for (int j = 0; j <= ck; j++)
			for (int k = 0; k <= cx; k++)
				for (int l = 0; l < 2; l++)
				{
//					printf("%d %d %d %d = %d\n", i, j, k, l, dp[i][j][k][l]);
					if (i < cv)
						dp[i + 1][j][k][1] = min(dp[i + 1][j][k][1], dp[i][j][k][l] + gettrans(i, j, k, l, 'V'));
					if (j < ck)
						dp[i][j + 1][k][0] = min(dp[i][j + 1][k][0], dp[i][j][k][l] + gettrans(i, j, k, l, 'K'));
					if (k < cx)
						dp[i][j][k + 1][0] = min(dp[i][j][k + 1][0], dp[i][j][k][l] + gettrans(i, j, k, l, 'X'));
				}
	cout << min(dp[cv][ck][cx][0], dp[cv][ck][cx][1]) << endl;
	return 0;
}
