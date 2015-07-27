#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000 + 5 , maxk = 25 + 5;
int a[maxn];
long long seg[maxn][maxn];
long long dp[maxk][maxn];
int n , k;
void work()
{
	memset(seg , 0 , sizeof(seg));
	for (int i = 1 ; i <= n ; i++)
		scanf("%d" , &a[i]);
	for (int i = 1 ; i <= n ; i++)
	{
		seg[i][i] = 0;
		long long lg = 0 , sm = 0 , m = a[i] , slg = 0 , ssm = 0;
		priority_queue<long long , vector<long long> , greater<long long> > A;
		priority_queue<long long> B;
		long long it;
		for (int j = i + 1 ; j <= n ; j++)
		{
			if (a[j] < m)
			{
				B.push(a[j]);
				sm++;
				ssm += a[j];
			}else
			{
				A.push(a[j]);
				lg++;
				slg += a[j];
			}
			while (lg - sm >= 2)
			{
				it = A.top();A.pop();
				B.push(m);
				slg -= it;lg--;
				ssm += m;sm++;
				m = it;
			}
			while (sm - lg >= 2)
			{
				it = B.top();B.pop();
				A.push(m);
				ssm -= it;sm--;
				slg += m;lg++;
				m = it;
			}
//			cerr << i << " " << j << " " << m << endl;
			seg[i][j] = m * sm - ssm + slg - m * lg;
//			printf("%d %d %lld %lld\n" , i , j , m , seg[i][j]);
		}
	}
	memset(dp , 0x7f , sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1 ; i <= k ; i++)
		for (int j = 0 ; j <= n ; j++)
			for (int l = j + 1 ; l <= n ; l++)
				if (dp[i - 1][j] != 0x7f7f7f7f7f7f7f7fll)
				{
					if (dp[i][l] == 0x7f7f7f7f7f7f7f7fll)
						dp[i][l] = dp[i - 1][j] + seg[j + 1][l];
					else
						dp[i][l] = min(dp[i][l] , dp[i - 1][j] + seg[j + 1][l]);
				}
	printf("%lld\n" , dp[k][n]);
}
int main()
{
	while ((~scanf("%d%d" , &n , &k)) && n && k)
		work();
	return 0;
}
