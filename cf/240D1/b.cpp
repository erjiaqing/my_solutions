#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=2005,mod=1000000007;
int dp[maxn][maxn];
int n,k;
int main()
{
	cin>>n>>k;
	for (int i=1;i<=n;i++)
		dp[i][1]=1;
	for (int i=2;i<=k+1;i++)
		for (int j=1;j<=n;j++)
			for (int l=j;l<=n;l+=j)
				(dp[j][i]+=dp[l][i-1])%=mod;
	cout<<dp[1][k+1]<<endl;
	return 0;
}
