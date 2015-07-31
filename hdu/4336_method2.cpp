#include <bits/stdc++.h>
using namespace std;
const int maxn = 20 + 5;
double p[maxn];
double dp[(1 << 20) + 5];
double w[(1 << 20) + 5];
int n;
/*
void get_have()
{
	for (int i = 0 ; i < (1 << n) ; i++)
	{
		k[i] = p[0];
		for (int j = 0 ; j < n ; j++)
			k[i] += p[j + 1] * ((i & (1 << j)) != 0);
	}
}
*/
double sqr(double x) {return x * x;}
void work()
{
	p[0] = 1;
	for (int i = 1 ; i <= n ; i ++)
	{
		scanf("%lf" , &p[i]);
		p[0] -= p[i];
	}
	memset(w , 0 , sizeof(w));
	memset(dp , 0 , sizeof(dp));
	w[0] = 1;
	for (int i = 0 ; i < (1 << n) ; i ++)
	{
		double k = p[0];
		for (int j = 0 ; j < n ; j++)
			k += p[j + 1] * ((i & (1 << j)) != 0);
		for (int j = 0 ; j < n ; j++)
		{
			if ((i & (1 << j)) == 0)
			{
				w[i | (1 << j)] += w[i] * p[j + 1] / (1 - k);
				dp[i | (1 << j)] += p[j + 1] * dp[i] / (1 - k) + w[i] * p[j + 1] / sqr(1 - k);
				// 算贡献
			}
		}
	}
	printf("%.6lf\n",dp[(1 << n) - 1]);
}
int main()
{
	while (~scanf("%d" , &n))
		work();
	return 0;
}
