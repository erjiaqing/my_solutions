#include <bits/stdc++.h>
using namespace std;

const int maxn = 505;

char mp[maxn][maxn];
char a[maxn][maxn], b[maxn][maxn];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%s", mp[i]);
	memset(a, '.', sizeof a);
	memset(b, '.', sizeof b);
	for (int i = 0; i < n; i++)
		a[i][m] = b[i][m] = 0;
	for (int i = 0; i < n; i++)
	{
		a[i][0] = '#';
		b[i][m - 1] = '#';
		if (i & 1)
			for (int j = 0; j < m - 1; j++)
				a[i][j] = '#';
		else
			for (int j = 1; j < m; j++)
				b[i][j] = '#';
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (mp[i][j] == '#')
				a[i][j] = b[i][j] = '#';
	for (int i = 0; i < n; i++)
		puts(a[i]);
	puts("");
	for (int i = 0; i < n; i++)
		puts(b[i]);
	return 0;
}
