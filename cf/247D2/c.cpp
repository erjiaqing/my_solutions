#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=105,maxk=105;
const int mod=1000000007;
int n,k,d;
int dp[maxn][maxk][2];
bool v[maxn][maxk][2];
int dfs(int rem,int lay,int flag)
{
	if (rem==0 && flag==1)
		return 1;
	else if (rem==0)
		return 0;
	if (v[rem][lay][flag])
		return dp[rem][lay][flag];
	v[rem][lay][flag]=true;
	int &res=dp[rem][lay][flag];
	for (int i=1;i<=k && i<=rem;i++)
		(res+=dfs(rem-i,lay,(flag||i>=d)))%=mod;
	return res;
}
int main()
{
	scanf("%d%d%d",&n,&k,&d);
	printf("%d\n",dfs(n,0,0));
	return 0;
}
