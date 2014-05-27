#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxh=1000005,maxn=1000005,mod=1000000007;
struct edge{
	int t,n;
	edge(){}
	edge(int _t,int _n):
		t(_t),n(_n){}
}e[maxh*2];int f[maxh],tote;
void addedge(int s,int t)
{
	int e1=tote++,e2=tote++;
	e[e1]=edge(t,f[s]);f[s]=e1;
	e[e2]=edge(s,f[t]);f[t]=e2;
}
int gcd(int a,int b)
{
	return (a%b)?gcd(b,a%b):b;
}
long long n,h[maxn],use[maxh],cnt[maxh],p2[maxn];
long long point[maxn],out[maxn],wait[maxn];
long long father[maxn],edge[maxn],mark[maxn];
long long must[maxn],s,F[maxn][2],ans=1;
void pre()
{
	for (long long i=2;i*2<=maxh;i++)
		for (long long j=1;j*i*2<=maxh && j<i ; j++)
			if ((i&1)!=(j&1) && gcd(i,j)==1 && i*i-j*j<=maxh)
			{
				int a=i*i-j*j,b=2*i*j;
				addedge(a,b);
			}
}
void dp(int p)
{
	F[p][0]=1;F[p][1]=p2[cnt[p]]-1;
	if (mark[p] && must[p]) F[p][0]=0;
	if (mark[p] && !must[p]) F[p][1]=0;
	for (int i=f[p];~i;i=e[i].n)
	{
		if (!out[i] && e[i].t!=father[p])
		{
			int q=e[i].t;
			if (cnt[q]==0)
				continue;
			dp(q);
			(F[p][0]*=(F[q][0]+F[q][1]))%=mod;
			(F[p][1]*=F[q][0])%=mod;
		}
	}
}
void dfs1(int p)
{
//	printf("[DFS1] %d\n",p);
	use[p]=true;point[++s]=p;
	for (int v=f[p];~v;v=e[v].n)
	{
		if (cnt[e[v].t] && e[v].t!=father[p])
		{
			if (!use[e[v].t])
			{
				father[e[v].t]=p;
				dfs1(e[v].t);
			}else
			{
				out[v]=true;
				edge[++edge[0]]=v;
				mark[e[v].t]=true;
			}
		}
	}
}
void dfs2(int p,int n,long long &ans)
{
	if (p>n)
	{
		for (int i=1;i<=edge[0];i++)
		{
			int x=edge[i],a=e[x].t,b=e[x^1].t;
			if (must[a]&must[b])
				return;
		}
		dp(point[1]);
		(ans+=F[point[1]][0]+F[point[1]][1])%=mod;
		return;
	}
	must[wait[p]]=true;dfs2(p+1,n,ans);
	must[wait[p]]=false;dfs2(p+1,n,ans);
}
long long work(int p)
{
//	printf("[WORK] %d\n",p);
	s=edge[0]=wait[0]=0;
	dfs1(p);
	long long tot=0;
	for (int i=1;i<=s;i++)
		if (mark[point[i]])
			wait[++wait[0]]=point[i];
	dfs2(1,wait[0],tot);
	return tot;
}
int main()
{
	memset(f,-1,sizeof(f));
	pre();
	scanf("%lld",&n);
	p2[0]=1;
	for (int i=1;i<=n;i++)
	{
		(p2[i]=p2[i-1]*2)%=mod;
		scanf("%lld",&h[i]);
		cnt[h[i]]++;
	}
	sort(&h[1],&h[n+1]);
	for (int i=1;i<=n;i++)
		if (!use[h[i]])
			(ans*=work(h[i]))%=mod;
	printf("%lld\n",ans-1);
	return 0;
}
