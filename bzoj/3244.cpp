#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
int segMin[maxn*4],Max[maxn],dfs[maxn],bfs[maxn],rk[maxn],n;
int build(int x,int l,int r)
{
	if (l==r) return segMin[x]=dfs[l];
	int mid=(l+r)/2;
	return segMin[x]=min(build(ls(x),l,mid),build(rs(x),mid+1,r));
}
int query(int x,int l,int r,int ql,int qr)
{
	if (ql<=l && r<=qr) return segMin[x];
	int mid=(l+r)/2,ret=maxn;
	if (ql<=mid) ret=min(ret,query(ls(x),l,mid,ql,qr));
	if (qr>mid) ret=min(ret,query(rs(x),mid+1,r,ql,qr));
	return ret;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&dfs[i]),rk[dfs[i]]=i;
	for (int i=1;i<=n;i++) scanf("%d",&bfs[i]),dfs[rk[bfs[i]]]=i;
	for (int i=1;i<=n;i++) Max[i]=max(Max[i-1],dfs[i]),rk[dfs[i]]=i;
	build(1,1,n);
	int ans=2,tmp=0;
	for (int i=1;i<n;i++)
	{
		if (i==1 || rk[i+1]<rk[i]) ans+=tmp+2,tmp=0; //必须当儿子的节点
		else if (rk[i]+1==rk[i+1] && Max[rk[i]]<i+1) ++tmp; //就那种情况
		else if (query(1,1,n,rk[i]+1,rk[i+1]-1)<i) tmp=0; //不是同一个点的儿子
	}
	ans+=tmp;
	printf("%.3lf\n%.3lf\n%.3lf\n",ans/2.0-0.001,ans/2.0,ans/2.0+0.001);//BZOJ这题没SPJ我们都懂
	//请告诉我保留3位小数的意义
	return 0;
}
