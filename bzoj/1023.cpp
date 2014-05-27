#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
const int maxn=50005,maxk=1005;
vector<int>e[maxn];
typedef vector<int>::iterator ii;
int a[maxn*2];
int n,m,k;
int f[maxn],fa[maxn];
int queue[maxn*2],beg,end,ans;
int arr[maxn*2],b[maxn*2];
int num=0;
int low[maxn],dfn[maxn],sum[maxn];
void dp(int rt,int p)
{
	int n=sum[p]-sum[rt]+1,beg=1,end=1;
	for (int i=p;i!=rt;i=fa[i])
		a[n--]=f[i];
	a[n]=f[rt];n=sum[p]-sum[rt]+1;
	for (int i=n+1;i<=n+n;i++)
		a[i]=a[i-n];
	queue[beg]=1;
	for (int i=2;i<=n+n/2;i++)
	{
		while (beg<=end && queue[beg]<i-n/2)
			beg++;
		ans=max(ans,a[queue[beg]]+a[i]+i-queue[beg]);
		while (beg<=end && a[queue[end]]-queue[end]<=a[i]-i)
			end--;
		queue[++end]=i;
	}
	for (int i=2;i<=n;i++)
		f[rt]=max(f[rt],a[i]+min(i-1,n-i+1));
}
void tarjan(int u)
{
	low[u]=dfn[u]=++num;
	for (ii v=e[u].begin();v!=e[u].end();v++)
	{
		if (*v!=fa[u])
		{
			if (!dfn[*v])
			{
				fa[*v]=u;sum[*v]=sum[u]+1;
				tarjan(*v);
			}
			low[u]=min(low[u],low[*v]);
			if (dfn[u]<low[*v])
			{
				ans=max(ans,f[u]+f[*v]+1);
				f[u]=max(f[u],f[*v]+1);
			}
		}
	}
	for (ii v=e[u].begin();v!=e[u].end();v++)
		if (fa[*v]!=u && dfn[u]<dfn[*v])
			dp(u,*v);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&k);
		for (int j=1;j<=k;j++)
			scanf("%d",&a[j]);
		for (int j=2;j<=k;j++)
			e[a[j]].push_back(a[j-1]),e[a[j-1]].push_back(a[j]);
	}
	tarjan(1);
	printf("%d\n",ans);
	return 0;
}
