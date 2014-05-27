#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=100005,maxt=2000005;
int k,tot,a[maxn],b[maxn],c[maxn];
int rt[maxn],g[maxn],s[maxt];
int l[maxt],r[maxt];
void insert(int x,int &y,int lft,int rgt,int v)
{
	s[y=++tot]=s[x]+1;
	if (lft==rgt)
		return;
	int mid=(lft+rgt)/2;
	if (v<=mid)
	{
		r[y]=r[x];
		insert(l[x],l[y],lft,mid,v);
	}else
	{
		l[y]=l[x];
		insert(r[x],r[y],mid+1,rgt,v);
	}
}
int query(int x,int y,int lft,int rgt,int v)
{
	if (s[y]-s[x]==0)
		return false;
	if (lft==rgt)
		return true;
	int mid=(lft+rgt)/2;
	return (v<=mid)?(query(l[x],l[y],lft,mid,v)):
		(query(r[x],r[y],mid+1,rgt,v));
}
bool cmp1(int x,int y)
{
	for (int i=0;i<k;i++)
	{
		if (a[x+i]<a[y+i])
			return true;
		if (a[x+i]>a[y+i])
			return false;
	}
	return false;
}
int cmp2(int x)
{
	for (int i=0;i<k;i++)
	{
		if (a[x+i]<b[i])
			return -1;
		if (a[x+i]>b[i])
			return 1;
	}
	return 0;
}
int dif(int x,int y)
{
	for (int i=0;i<k;i++)
		if (a[x+i]!=a[y+i])
			return true;
	return false;
}
int n,m,id=1;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[c[i]=i]);
	sort(&c[1],&c[n+1],cmp1);
	g[c[1]]=1;
	for (int i=2;i<=n;i++)
		g[c[i]]=(id+=dif(c[i-1],c[i]));
	for (int i=1;i+k-1<=n;i++)
		insert(rt[i-1],rt[i],1,id,g[i]);
//	printf("~~\n");
	while (m--)
	{
		int lft,rgt,x=0;
		scanf("%d%d",&lft,&rgt);
		for (int i=0;i<k;i++)
			scanf("%d",&b[i]);
		int f=0,t=n+1;
//		printf("##\n");
		while (f+1<t)
		{
			int mid=(f+t)/2;
			if (cmp2(c[mid])<=0)
				f=mid;
			else
				t=mid;
		}
//		printf("~~\n");
		printf("%s\n",((!cmp2(c[f]))&&query(rt[lft-1],rt[rgt-k+1],1,id,g[c[f]]))?"No":"Yes");
	}
	return 0;
}
