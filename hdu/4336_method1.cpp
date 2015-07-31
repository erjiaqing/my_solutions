#include <bits/stdc++.h>
using namespace std;
const int maxn = 20 + 5;
double p[maxn];
double dp[(1 << 20) + 5];
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
	for (int i = 0 ; i < n ; i ++)
		scanf("%lf" , &p[i]);
	memset(dp , 0 , sizeof(dp));
	dp[(1 << n) - 1] = 0;
	for (int i = (1 << n) - 2 ; i >= 0 ; i --)
	{
		double tp = 0;
		dp[i] = 1;
		for (int j = 0 ; j < n ; j++)
			if ((i & (1 << j)) == 0)
			{
				dp[i] += dp[i | (1 << j)] * p[j];
				tp += p[j];
			}
		dp[i] /= tp;
	}
	printf("%.12lf\n",dp[0]);
}
int main()
{
	while (~scanf("%d" , &n))
		work();
	return 0;
}
