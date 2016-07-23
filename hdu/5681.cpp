#include <bits/stdc++.h>
using namespace std;
const int maxn = 20005, maxk = 105;

long long dp[maxk][maxn];
long long a[maxn], b[maxn], d[maxn], r[maxn];

typedef pair<int, int> pii;
#define x first
#define y second
vector<pii> e[maxn];

int n, k;

int get_leftmost(long long q)
{
	return lower_bound(&d[0], &d[n + 1], q) - &d[0];
}

int get_rightmost(long long q)
{
	return upper_bound(&d[0], &d[n + 1], q) - &d[0] - 1;
}

void sol()
{
	scanf("%d%d", &n, &k);
	memset(dp, 0x3f, sizeof(dp));
	d[1] = 100001;
	for (int i = 2; i <= n; i++)
	{
		scanf("%lld", &d[i]);
		d[i] += d[i - 1];
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld%lld", &a[i], &r[i], &b[i]);
		e[i].clear();
	}
	for (int i = 1; i <= n; i++)
	{
		int lm = get_leftmost(d[i] - r[i]),
			rm = get_rightmost(d[i] + r[i]);
		e[rm].push_back(pii(lm, a[i]));
	}
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
		dp[0][i] = dp[0][i - 1] + b[i];
	for (int j = 1; j <= k; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			dp[j][i] = min(dp[j][i], dp[j][i - 1] + b[i]);
			for (pii seg : e[i])
				dp[j][i] = min(dp[j][i], dp[j - 1][seg.x - 1] + seg.y);
		}
		for (int i = n - 1; i; i--)
			dp[j][i] = min(dp[j][i], dp[j][i + 1]);
	}
	long long ans = 0x3f3f3f3f3f3f3f3fll;
	for (int i = 0; i <= k; i++)
		ans = min(ans, dp[i][n]);
	printf("%lld\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
