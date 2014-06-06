#include <bits/stdc++.h>
using namespace std;
typedef long long i64d;
const int maxn=100005,mod=1000000007;
vector<int> g[maxn];
int fac[maxn],ifac[maxn];
int dp[maxn],rdp[maxn];
int q,n,f;
int pow(int a,int k)
{
	int ret=1;
	while (k)
	{
		if (k&1) ret=i64d(ret)*a%mod;
		a=i64d(a)*a%mod;k>>=1;
	}
	return ret%mod;
}
int C(int a,int b)
{
	if (b<0 || b>a) return 0;
	if (b==0) return 1;
	int ans=(i64d(fac[a])*ifac[b])%mod;
	ans=(i64d(ans)*ifac[a-b])%mod;
	return ans;
}
int Dp(int n,int f)
{
//	printf("%d %d\n",n,f);
	if (f> n) return 0;
	if (f==n) return 1;
	if (rdp[n]==q) return dp[n];
	rdp[n]=q;
	int &ret=dp[n];ret=C(n-1,f-1);
	for (vector<int>::iterator g=::g[n].begin();g!=::g[n].end();g++)
	{
		if (*g==n) continue;
		ret-=Dp(*g,f);
		if (ret<0) ret+=mod;
	}
	return ret;
}
int main()
{
	int Q;
	fac[0]=ifac[0]=1;
	for (int i=1;i<=100000;i++)
		for (int j=i;j<=100000;j+=i)
			g[j].push_back(i);
	for (int i=1;i<=100000;i++)
		fac[i]=(i64d(fac[i-1])*i)%mod,ifac[i]=int(pow(fac[i],mod-2));
	scanf("%d",&Q);
	for (q=1;q<=Q;q++)
		scanf("%d%d",&n,&f),printf("%d\n",Dp(n,f));
	return 0;
}
