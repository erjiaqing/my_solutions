#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=5005;
int bit[maxn];
int a[maxn];
int fgcd[maxn];
int valf[maxn];
int bads[maxn];
int prime[maxn*100];
int isprime[500000];
int dp[maxn][maxn];
vector<pair<int,int> > p;
typedef vector<pair<int,int> >::iterator vii;
int n,m;
inline int lowbit(const int &x) {return x&(-x);}
int gcd(int a,int b)
{
	if (b)
		return gcd(b,a%b);
	return a;
}
int sqr(int x)
{
	return x*x;
}
int q(int x)
{
	return binary_search(&bads[1],&bads[m+1],x)?-1:1;
}
int f(int x)
{
	int ret=0;
	for (vii pp=p.begin();sqr(pp->first)<=x;pp++)
	{
		while (x%(pp->first)==0)
		{
			ret+=pp->second;
			x/=pp->first;
		}
	}
	if (x>1)
		ret+=q(x);
	return ret;
}
int main()
{
	int ans=0;
//	for (int i=1;i<maxn;i++)
//		bit[i]=1;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	reverse(&a[0],&a[n]);
	fgcd[n-1]=a[n-1];
	for (int i=n-2;i>=0;i--)
		fgcd[i]=gcd(fgcd[i+1],a[i]);
//	scanf("%d",&m);
	for (int i=0;i<m;i++)
		scanf("%d",&bads[m]);
	memset(isprime,-1,sizeof(isprime));
	int pnt=1;
	for (int i=2;i<200000;i++)
		if (isprime[i])
		{
			if (bads[pnt]==i)
				p.push_back(pair<int,int>(i,-1)),pnt++;
			else
				p.push_back(pair<int,int>(i,1));
			for (int j=i+i;j<200000;j+=i)
				isprime[j]=false;
		}
	for (int i=0;i<n;i++)
		ans+=f(a[i]);
	for (int i=0;i<n;i++)
		valf[i]=f(fgcd[i]);
	for (int i=n;i>1;i--)
	{
		for (int j=0;j<i;j++)
		{
			dp[i][j]=dp[i+1][j];
			dp[i][j]=max(dp[i][j],dp[i+1][i]-(valf[i]-valf[j])*(n-i));
		}
	}
	ans+=dp[1][0];
	printf("%d\n",ans);
	return 0;
}
