#include <cstdio>
#include <cstring>

const int maxn = 1000 + 2;
int up[maxn][maxn], dn[maxn][maxn], lf[maxn][maxn], ri[maxn][maxn];
int mat[maxn][maxn];
int pq[maxn];
int n, m;

unsigned int get(unsigned int a, unsigned int b)
{
	unsigned int parta = a * (a + 1) / 2 * (b + 1);
	unsigned int partb = b * (b + 1) / 2 * (a + 1);
	return parta + partb + (a + 1) * (b + 1);
}

void sol(int mdzz_pe)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &mat[i][j]);
	memset(up, 0, sizeof(up));
	memset(dn, 0, sizeof(dn));
	memset(lf, 0, sizeof(lf));
	memset(ri, 0, sizeof(ri));
	pq[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int qh = 0;
		for (int j = 1; j <= m; j++)
		{
			while (qh && mat[i][pq[qh]] > mat[i][j]) qh--;
			lf[i][j] = pq[qh] + 1;
			pq[++qh] = j;
		}
	}
	//--
	pq[0] = m + 1;
	for (int i = 1; i <= n; i++)
	{
		int qh = 0;
		for (int j = m; j >= 1; j--)
		{
			while (qh && mat[i][pq[qh]] > mat[i][j]) qh--;
			ri[i][j] = pq[qh] - 1;
			pq[++qh] = j;
		}
	}
	//--
	pq[0] = 0;
	for (int j = 1; j <= m; j++)
	{
		int qh = 0;
		for (int i = 1; i <= n; i++)
		{
			while (qh && mat[pq[qh]][j] < mat[i][j]) qh--;
			up[i][j] = pq[qh] + 1;
			pq[++qh] = i;
		}
	}
	//--
	pq[0] = n + 1;
	for (int j = 1; j <= m; j++)
	{
		int qh = 0;
		for (int i = n; i >= 1; i--)
		{
			while (qh && mat[pq[qh]][j] < mat[i][j]) qh--;
			dn[i][j] = pq[qh] - 1;
			pq[++qh] = i;
		}
	}
	unsigned int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans += ((unsigned int)mat[i][j])
				* get(j - lf[i][j], ri[i][j] - j)
				* get(i - up[i][j], dn[i][j] - i);
	printf("%u\n", ans);
	return;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol(t);
	return 0;
}
