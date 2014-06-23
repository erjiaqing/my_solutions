#include <bits/stdc++.h>
using namespace std;
const int maxn=20005,maxm=50005,inf=55131515;//Random number
struct edge{
	int u,v,w,p;
	edge(){}
	void read(int i){scanf("%d%d%d",&u,&v,&w);p=i;}
	friend bool operator < (const edge &a,const edge &b){return a.w<b.w;}
}e[25][maxm],d[maxm],t[maxm];
struct xy{int x,y;}q[maxm];
int n,m,qc;
int sum[maxn],f[maxn],sz[maxn],c[maxm],a[maxm];
long long ans[maxm];
//pair<pair<int,int>,long long>q[maxm];
void reset(edge *s,int tot)
{
	for (int i=1;i<=tot;i++) f[s[i].u]=s[i].u,f[s[i].v]=s[i].v;
}
int set_find(int u){return f[u]==u?u:f[u]=set_find(f[u]);}
void set_merge(int u,int v){f[set_find(u)]=set_find(v);}
void cont(int &tot,long long &cnt)
{
	int tmp=0;
	reset(d,tot);
	sort(&d[1],&d[tot+1]);
	for (int i=1;i<=tot;i++)
		if (set_find(d[i].u)!=set_find(d[i].v))
			set_merge(d[i].u,d[i].v),t[++tmp]=d[i];
	reset(t,tmp);
	for (int i=1;i<=tmp;i++)
		if (t[i].w!=-inf && set_find(t[i].u)!=set_find(t[i].v))
			set_merge(t[i].u,t[i].v),cnt+=t[i].w;
	tmp=0;
	for (int i=1;i<=tot;i++)
		if (set_find(d[i].u)!=set_find(d[i].v))
			t[c[d[i].p]=++tmp]=d[i],
			t[tmp].u=f[d[i].u],
			t[tmp].v=f[d[i].v];
	for (int i=1;i<=tmp;i++) d[i]=t[i];
	tot=tmp;
}
void redu(int &tot)
{
	int tmp=0;
	reset(d,tot);
	sort(&d[1],&d[tot+1]);
	for (int i=1;i<=tot;i++)
		if (set_find(d[i].u)!=set_find(d[i].v))
			set_merge(d[i].u,d[i].v),
			t[c[d[i].p]=++tmp]=d[i];
		else if (d[i].w==inf)
			t[c[d[i].p]=++tmp]=d[i];
	for (int i=1;i<=tmp;i++) d[i]=t[i];
	tot=tmp;
}
void solv(int l,int r,int lay,long long cnt)
{
	int tot=sum[lay];
	if (l==r) a[q[l].x]=q[l].y;
	for (int i=1;i<=tot;i++) e[lay][i].w=a[e[lay][i].p];
	for (int i=1;i<=tot;i++) d[i]=e[lay][i],c[d[i].p]=i;
	if (l==r)
	{
		ans[l]=cnt;
		reset(d,tot);
		sort(&d[1],&d[tot+1]);
		for (int i=1;i<=tot;i++)
			if (set_find(d[i].u)!=set_find(d[i].v))
				set_merge(d[i].u,d[i].v),ans[l]+=d[i].w;
		return;
	}
	for (int i=l;i<=r;i++) d[c[q[i].x]].w=-inf;
	cont(tot,cnt);
	for (int i=l;i<=r;i++) d[c[q[i].x]].w=inf;
	redu(tot);
	for (int i=1;i<=tot;i++) e[lay+1][i]=d[i];
	sum[lay+1]=tot;
	int mid=(l+r)/2;
	solv(l,mid,lay+1,cnt);
	solv(mid+1,r,lay+1,cnt);
}
int main()
{
	scanf("%d%d%d",&n,&m,&qc);
	for (int i=1;i<=m;i++) e[0][i].read(i),a[i]=e[0][i].w;
	for (int i=1;i<=qc;i++) scanf("%d%d",&q[i].x,&q[i].y);
	sum[0]=m;
	solv(1,qc,0,0);
	for (int i=1;i<=qc;i++) printf("%lld\n",ans[i]);
	return 0;
}
