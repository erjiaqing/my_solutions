#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
long long a[maxn][maxn];
long long sum[maxn][maxn];
int row, col;
int n;
long long sumrow = 0, sumcol = 0, sumdiag = 0, tsum;
long long ans = 0;

bool check()
{
	for (int i = 0; i < n; i++)
	{
		long long sum = 0;
		for (int j = 0; j < n; j++)
			sum += a[i][j];
		if (sum != sumrow)
			return false;
	}
	for (int j = 0; j < n; j++)
	{
		long long sum = 0;
		for (int i = 0; i < n; i++)
			sum += a[i][j];
		if (sum != sumrow)
			return false;
	}
	long long sum = 0;
	for (int i = 0; i < n; i++)
		sum += a[i][i];
	if (sum != sumrow) return false;
	sum = 0;
	for (int i = 0; i < n; i++)
		sum += a[i][n - i - 1];
	if (sum != sumrow) return false;
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%lld", &a[i][j]);
	if (n == 1)
	{
		puts("1");
		return 0;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (a[i][j] == 0)
			{
				row = i;col = j;
			}
	for (int i = 0; i < n; i++)
	{
		if (i == row)
		{
			continue;
		} else {
			for (int j = 0; j < n; j++)
				sumrow += a[i][j];
			break;
		}
	}
	tsum = sumrow;
	for (int j = 0; j < n; j++)
		tsum -= a[row][j];
	a[row][col] = tsum;
	if (tsum <= 0)
	{
		puts("-1");
		return 0;
	}
	if (check())
	{
		printf("%lld\n", a[row][col]);
	} else {
		printf("-1\n");
	}
	return 0;
}
