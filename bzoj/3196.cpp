#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn=50005,block=255;
const int inf=0x7fffffff,minf=0x80000000;
int blocks,size[block],arr[block][block];
int n,m,a[maxn];
int *lower(int *const s,int *const t,const int x)
{
	int *const pos=lower_bound(s,t,x);
	return ((*pos==x)?(upper_bound(s,t,x)-1):(pos-1));
}
int gmin()
{
	int ret=inf;
	for (int i=0;i<blocks;i++)
		ret=min(ret,arr[i][0]);
	return ret;
}
int gmax()
{
	int ret=minf;
	for (int i=0;i<blocks;i++)
		ret=max(ret,arr[i][size[i]-1]);
	return ret;
}
int Count(int s,int t,int x)
{
	int bs=s/block,bt=t/block;
	int cnt=0;
	if (bs==bt)
	{
		for (int i=s;i<=t;i++)
			cnt+=a[i]<x;
		return cnt;
	}
	for (int i=s;i<(bs+1)*block;i++)
		cnt+=a[i]<x;
	for (int i=bt*block;i<=t;i++)
		cnt+=a[i]<x;
	for (int i=bs+1;i<bt;i++)
		cnt+=lower(&arr[i][0],&arr[i][size[i]],x)-&arr[i][1];
	return cnt;
}
int query2(int s,int t,int k)
{
	int l=gmin()-1,r=gmax(),mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		int cn=Count(s,t,mid);
		if (cn>=k)
			r=mid;
		else
			l=mid;
	}
	return r;
}
int query4(int s,int t,int k)
{
	int ret=k;
	int x=Count(s,t,k);
	while (ret>=k)
		ret=query2(s,t,x--);
	return ret;
}
int query5(int s,int t,int k)
{
	int ret=k;
	int x=(t-s+1)-Count(s,t,k);
	while (ret<=k)
		ret=query2(s,t,x++);
	return ret;
}
int main()
{
	int op,l,r,x,k;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		arr[i/block][size[i/block]++]=a[i];
	}
	blocks=1+(n-1)/block;
	for (int i=0;i<blocks;i++)
		sort(&arr[i][0],&arr[i][size[i]]);
	while (m--)
	{
		scanf("%d",&op);
		if (op==1)
		{
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",Count(l-1,r-1,k));
		}else if (op==2)
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",query2(l-1,r-1,x));
		}else if (op==3)
		{
			scanf("%d%d",&k,&x);
			k--;
			int blk=k/block;
			int pos=lower_bound(&arr[blk][0],&arr[blk][size[blk]],a[k])-&arr[blk][0];
			arr[blk][pos]=a[k]=x;
			sort(&arr[blk][0],&arr[blk][size[blk]]);
		}else if (op==4)
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",query4(l-1,r-1,x));
		}else if (op==5)
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",query5(l-1,r-1,x));
		}
	}
	return 0;
}
