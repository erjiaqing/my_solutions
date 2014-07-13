#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
long long row_dec,col_dec;
long long row[maxn],col[maxn];
int a[maxn][maxn];
struct seg_tree{
	int pos[maxn*4];
	long long val[maxn];
	int _max()
	{
		return pos[1];
	}
	void init(int x,int l,int r)
	{
		if (l==r) {pos[x]=l;return;}
		int mid=(l+r)/2;
		init(x*2,l,mid);
		init(x*2+1,mid+1,r);
		if (pos[x*2]==0) pos[x]=pos[x*2+1];
		else if (pos[x*2+1]==0) pos[x]=pos[x*2];
		else
		{
			if (val[pos[x*2]]>val[pos[x*2+1]])
				pos[x]=pos[x*2];
			else
				pos[x]=pos[x*2+1];
		}
	}
	void _edt(int x,int l,int r,int p,int v)
	{
		if (l==r)
		{
			val[p]+=v;
			return;
		}
		int mid=(l+r)/2;
		if (p<=mid) _edt(x*2,l,mid,p,v);
		else _edt(x*2+1,mid+1,r,p,v);
		if (pos[x*2]==0) pos[x]=pos[x*2+1];
		else if (pos[x*2+1]==0) pos[x]=pos[x*2];
		else 
		{
			if (val[pos[x*2]]>val[pos[x*2+1]])
				pos[x]=pos[x*2];
			else
				pos[x]=pos[x*2+1];
		}
	}
}r,c;
int n,m,k,p;
long long ans=0;
int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&p);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			row[i]+=a[i][j];
			col[j]+=a[i][j];
		}
	r.val[0]=c.val[0]=-1000000000000000ll;
//	r.init(1,1,n);c.init(1,1,m);
	for (int i=1;i<=n;i++)
		r.val[i]=row[i];
	for (int i=1;i<=m;i++)
		c.val[i]=col[i];
	r.init(1,1,n);c.init(1,1,m);
	int q1,q2;
	long long v1,v2;
	while (k--)
	{
		q1=r._max();v1=r.val[q1]-row_dec;
		q2=c._max();v2=c.val[q2]-col_dec;
		if (q1==0 || q2==0) cerr<<"!!\n";
//		printf("%d %lld %d %lld\n",q1,v1,q2,v2);
		if (v1>v2)
		{
			ans+=v1;
			r._edt(1,1,n,q1,-p*m);
			col_dec+=p;
		}else
		{
			ans+=v2;
			c._edt(1,1,m,q2,-p*n);
			row_dec+=p;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
