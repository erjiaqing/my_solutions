#include <bits/stdc++.h>
using namespace std;
#define _X( _x ) ( (_x) + 20000 )
const int maxx = 40000 + 5;
const int maxn = 100 + 5;
int dp[2][maxn][maxx];
int t , n;
int xxx , yyy , txx , tyy;
inline int _abs(int x){return x < 0 ? -x : x;}
inline double sqr(double x) {return x * x;}
void work(int caseno)
{
	memset(dp[1] , 0xc0 , sizeof(dp[1]));
	memset(dp[0] , 0x3f , sizeof(dp[0]));
	scanf("%d%d%d" , &n , &xxx , &yyy);
	txx = xxx;tyy = yyy;
	dp[0][0][_X(0)] = dp[1][0][_X(0)] = 0;
	int Min = 0 , Max = 0;
	double ans = 0;
	for (int i = 1 ; i <= n ; i++)
	{
		scanf("%d%d" , &xxx , &yyy);
		for (int x = Min ; x <= Max ; x++)
		{
			if (dp[0][i - 1][_X(x)] != 0x3f3f3f3f)
				dp[0][i][_X(x - xxx)] = min(dp[0][i][_X(x - xxx)] , dp[0][i - 1][_X(x)] - yyy),
				dp[0][i][_X(x + xxx)] = min(dp[0][i][_X(x + xxx)] , dp[0][i - 1][_X(x)] + yyy);
			if (dp[1][i - 1][_X(x)] != 0xc0c0c0c0)
				dp[1][i][_X(x - xxx)] = max(dp[1][i][_X(x - xxx)] , dp[1][i - 1][_X(x)] - yyy),
				dp[1][i][_X(x + xxx)] = max(dp[1][i][_X(x + xxx)] , dp[1][i - 1][_X(x)] + yyy);
		}
		Min -= _abs(xxx);
		Max += _abs(xxx);
	}
	for (int i = Min ; i <= Max ; i++)
	{
		if (dp[0][n][_X(i)] != 0x3f3f3f3f)
			ans = max(ans , sqrt(sqr(i - txx) + sqr(dp[0][n][_X(i)] - tyy)));
		if (dp[1][n][_X(i)] != 0xc0c0c0c0)
			ans = max(ans , sqrt(sqr(i - txx) + sqr(dp[1][n][_X(i)] - tyy)));
	}
	printf("Case %d: %.3f\n" , caseno , ans);
}
int main()
{
	scanf("%d" , &t);
	for (int i = 1 ; i <= t ; i++)
		work(i);
	return 0;
}
