#include <bits/stdc++.h>
using namespace std;
const int maxc = 25 + 5 , maxt = 1000 + 5;
int dp[maxc][maxt];
int e[maxc][maxt] , p[maxc][maxt];
int _abs(int x)
{
	return x < 0 ? -x : x;
}
void work()
{
	int c , t , l;
	cin >> c >> t >> l;
	int th = 0;
	memset(dp , 0x3f , sizeof(dp));
	memset(e , 0 , sizeof(e));
	for (int i = 0 ; i < c ; i++)
		for (int j = 0 ; j < t ; j++)
			cin >> p[i][j] >> e[i][j];
	for (int i = 0 ; i < t ; i++)
	{
		dp[0][i] = p[0][i] + e[0][i];
		p[c][i] = l;
	}
	for (int k = 1 ; k <= c ; k++)
		for (int i = 0 ; i < t ; i++)
			for (int j = 0 ; j < t ; j++)
				dp[k][i] = min(dp[k][i] , dp[k - 1][j] + _abs(p[k][i] - p[k - 1][j]) + e[k][i]);
	int ans = 0x3f3f3f3f;
	for (int i = 0 ; i < t ; i++)
		ans = min(ans , dp[c][i]);
	printf("%d\n" , ans);
}
int main()
{
	ios::sync_with_stdio(0);
	int z;
	cin >> z;
	while (z--)
		work();
	return 0;
}
