#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 2;
double dst[maxn][maxn];
double dp[maxn];
int pre[maxn], pos[maxn], w[maxn];
int n, l;

bool check(double rat)
{
	dp[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		dp[i] = 1e10;
		for (int j = 0; j < i; j++)
		{
			if (dp[j] + dst[j][i] - rat * w[i] < dp[i])
			{
				dp[i] = dp[j] + dst[j][i] - rat * w[i];
				pre[i] = j;
			}
		}
	}
	return dp[n] <= 0;
}

int main()
{
	scanf("%d%d", &n, &l);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &pos[i], &w[i]);
	for (int i = 0; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			dst[i][j] = sqrt(fabs(1.0 * (pos[j] - pos[i]) - l));
	double l = 0, r = 1e10;
	while (r - l > 1e-8)
	{
		double mid = (r + l) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	//	cerr << mid << endl;
	}
	vector<int> p, q;
	int cur = n;
//	p.push_back(n);
	while (cur != 0) p.push_back(cur), cur = pre[cur];
	q.insert(q.end(), p.rbegin(), p.rend());
	for (int v : q)
		printf("%d ", v);
	return 0;
}
