#include <bits/stdc++.h>
using namespace std;

#define ls(x) (((x)<<1))
#define rs(x) ((((x)<<1)|1))

int seg_max[262150],seg_pos[262150];
long long seg_sum[262150],arr[262150];
void seg_update(int x)
{
#ifdef DEBUG
	printf("x=%d ls=%d |p %d m %d s %lld| rs=%d |p %d m %d s %lld|\n",
			x,
			ls(x),seg_pos[ls(x)],seg_max[ls(x)],seg_sum[ls(x)],
			rs(x),seg_pos[rs(x)],seg_max[rs(x)],seg_sum[rs(x)]
			);
#endif
	if (seg_max[ls(x)]>seg_max[rs(x)])
	{
		seg_pos[x]=seg_pos[ls(x)];
		seg_max[x]=seg_max[ls(x)];
	}else
	{
		seg_pos[x]=seg_pos[rs(x)];
		seg_max[x]=seg_max[rs(x)];
	}
	seg_sum[x]=seg_sum[ls(x)]+seg_sum[rs(x)];
}
void seg_setval(int x,int l,int r,int p,int v)
{
	if (l==r)
	{
		seg_max[x]=seg_sum[x]=v;
		return;
	}
	int mid=(l+r)/2;
	if (p<=mid)
		seg_setval(ls(x),l,mid,p,v);
	else
		seg_setval(rs(x),mid+1,r,p,v);
	seg_update(x);
}
long long seg_getsum(int x,int l,int r,int ql,int qr)
{
	long long ans=0;
	if (ql <=l && r<=qr)
		return seg_sum[x];
	int mid=(l+r)/2;
	if (ql<=mid)
		ans+=seg_getsum(ls(x),l,mid,ql,qr);
	if (mid<qr)
		ans+=seg_getsum(rs(x),mid+1,r,ql,qr);
	return ans;
}
int seg_getmaxpos(int x,int l,int r,int ql,int qr)
{
	int lp=0,rp=0;
	if (ql<=l && r<=qr)
		return seg_pos[x];
	int mid=(l+r)/2;
	if (ql<=mid)
		lp=seg_getmaxpos(ls(x),l,mid,ql,qr);
	if (mid<qr)
		rp=seg_getmaxpos(rs(x),mid+1,r,ql,qr);
	if (lp==-1)
		return rp;
	if (rp==-1)
		return lp;
	if (arr[lp]>arr[rp])
		return lp;
	else
		return rp;
}
void seg_build(int x,int l,int r)
{
	if (l==r)
	{
		seg_max[x]=seg_sum[x]=arr[seg_pos[x]=l];
		return;
	}
	int mid=(l+r)/2;
	if (l<=mid)
		seg_build(ls(x),l,mid);
	if (mid<r)
		seg_build(rs(x),mid+1,r);
	seg_update(x);
}
int n,m;
#define Process1( l, r) printf("%lld\n",seg_getsum(1,1,n,l,r))
void Process2(int l,int r,int x)
{
	int tmp;
	while (arr[tmp=seg_getmaxpos(1,1,n,l,r)] >= x )
	{
//		cerr<<tmp<<endl;
		seg_setval(1,1,n,tmp,arr[tmp]=arr[tmp]%x);
	}
}
#define Process3( p, v) seg_setval(1,1,n,(p),(v))
int main()
{
	int op,l,r,x;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%lld",&arr[i]);
	seg_build(1,1,n);
	while (m--)
	{
		scanf("%d%d%d",&op,&l,&r);
		if (op==1)
			Process1(l,r);
		else if (op==2)
			scanf("%d",&x),Process2(l,r,x);
		else if (op==3)
			arr[l]=r,Process3(l,r);
#ifdef DEBUG
		for (int i=1;i<=n;i++)
			printf("%lld%c",arr[i],i==n?'\n':' ');
#endif
	}
	return 0;
}
