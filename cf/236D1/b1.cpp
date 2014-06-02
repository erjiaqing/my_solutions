#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=5005;
int a[maxn],bp[maxn],g[maxn],vg[maxn];
int dp[maxn][maxn];
int n,m;
vector<pair<int,int> >Prime;
typedef vector<pair<int,int> >::iterator vpiii;
int ifp[100005];
int gcd(int a,int b)
{
	if (a<b) return gcd(b,a);
	if (b==0) return a;
	return gcd(b,a%b);
}
int p(int x)
{
	return binary_search(&bp[0],&bp[m],x)?-1:1;
}
int sqr(int x)
{
	return x*x;
}
int f(int x)
{
	int ret=0;
	for (vpiii p=Prime.begin();p!=Prime.end() && sqr(p->first)<=x;p++)
	{
		while (x%p->first==0)
		{
			x/=p->first;
			ret+=p->second;
		}
	}
	if (x>1)
		ret+=p(x);
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	a[n++]=1;
	for (int i=0;i<m;i++)
		scanf("%d",&bp[i]);
	int badPrimePointer=0;
	memset(ifp,-1,sizeof(ifp));
	for (int i=2;i<100005;i++)
		if (ifp[i])
		{
			if (badPrimePointer<m && bp[badPrimePointer]==i)
				Prime.push_back(make_pair(i,-1)),badPrimePointer++;
			else
				Prime.push_back(make_pair(i,1));
			for (int j=i+i;j<100005;j+=i)
				ifp[j]=false;
		}
	int ans=0;
	for (int i=0;i<n;i++)
		ans+=f(a[i]);
	reverse(&a[0],&a[n]);
	g[n-1]=a[n-1];
	for (int i=n-2;i>=0;i--)
		g[i]=gcd(g[i+1],a[i]);
	for (int i=0;i<n;i++)
		vg[i]=f(g[i]);
	for (int i=n-1;i>0;i--)
		for (int j=0;j<i;j++)
		{
			dp[i][j]=dp[i+1][j];
			dp[i][j]=max(dp[i][j],dp[i+1][i]-(vg[i]-vg[j])*(n-i));
		}
	ans+=dp[1][0];
	printf("%d\n",ans);
	return 0;
}
