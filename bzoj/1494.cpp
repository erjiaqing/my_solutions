#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;
const int maxk=5,maxw=60;
const long long mod=65521;
int status[maxw],hash[1<<15];
int p[maxk+1],cot[maxk];
int val[]={1,1,1,3,16,125};
long long n;
int k;
int tot;
struct matrix{
	long long m[maxw][maxw];
	int h,w;
	matrix(int _h=0,int _w=0){
		h=_h;w=_w;
		memset(m,0,sizeof(m));
	}
	matrix operator * (const matrix & b) const
	{
		matrix ret(h,b.w);
		memset(ret.m,0,sizeof(ret));
		ret.h=h;ret.w=b.w;
		for (int i=0;i<h;i++)
			for (int j=0;j<b.w;j++)
				for (int k=0;k<w;k++)
					(ret.m[i][j]+=(m[i][k]*b.m[k][j]%mod))%=mod;
		return ret;
	}
	matrix operator ^ (long long k)
	{
		int kk=k;
		matrix b(h,w),c=(*this);
		memset(b.m,0,sizeof(b.m));
		b.w=w;b.h=h;
		for (int i=0;i<w;i++)
			b.m[i][i]=1;
		while (kk)
		{
			if (kk&1)
				b=b*c;
			c=c*c;
			kk>>=1;
		}
		return b;
	}
}g,f;
void dfs(int mask,int dep)
{
	if (dep==k)
	{
		g.m[0][tot]=1;
		memset(cot,0,sizeof(cot));
		for (int i=0;i<k;i++)
			cot[(mask>>(i*3))&7]++;
		for (int i=0;i<k;i++)
			g.m[0][tot]*=val[cot[i]];
		status[tot]=mask;
		hash[mask]=tot++;
		return;
	}
	int tmp=-1;
	for (int i=0;i<dep;i++)
		tmp=max(tmp,(mask>>(i*3))&7);
	for (int i=0;i<=tmp+1 && i<k;i++)
		dfs(mask<<3|i,dep+1);
}
int findp(int x)
{
	return p[x]==-1?x:p[x]=findp(p[x]);
}
int justify()
{
	bool vis[maxk];
	memset(vis,0,sizeof(vis));
	int tot=0;
	int mask=0;
	for (int i=k-1;i>=0;i--)
	{
		if (!vis[i])
		{
			vis[i]=true;
			mask|=tot<<(i*3);
			for (int j=i-1;j>=0;j--)
			{
				if (findp(i+1)==findp(j+1))
				{
					vis[j]=true;
					mask|=tot<<(j*3);
				}
			}
			tot++;
		}
	}
	return hash[mask];
}
void cal(int s,int mask)
{
	memset(p,-1,sizeof(p));
	for (int i=0;i<k;i++)
		for (int j=i+1;j<k;j++)
			if ((status[s]>>(i*3)&7)==(status[s]>>(j*3)&7))
			{
				int px=findp(i);
				int py=findp(j);
				if (px!=py)
				{
					p[px]=py;
				}
			}
	for (int i=0;i<k;i++)
		if ((mask>>i)&1)
		{
			int px=findp(i);
			int py=findp(k);
			if (px==py)
				return;
			p[px]=py;
		}
	bool flag=false;
	for (int i=1;i<=k;i++)
		if (findp(i)==findp(0))
		{
			flag=true;
			break;
		}
	if (!flag)
		return;
	f.m[s][justify()]++;
}
int main()
{
	scanf("%d%lld",&k,&n);
	tot=0;
	memset(f.m,0,sizeof(f.m));
	memset(g.m,0,sizeof(g.m));
	dfs(0,0);
	g.h=1;
	g.w=f.w=f.h=tot;
	for (int i=0;i<tot;i++)
		for (int mask=0;mask<(1<<k);mask++)
			cal(i,mask);
	g=g*(f^(n-k));
	printf("%lld\n",g.m[0][0]);
	return 0;
}
