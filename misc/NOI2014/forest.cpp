#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int maxn=50005,maxm=100005;
struct edge
{
	int u,v,a,b;
	edge(){}
	edge(const int &_u,const int &_v,const int &_a,const int &_b):
		u(_u),v(_v),a(_a),b(_b){}
}e[maxm*2];
int te,h[maxn];
int n,m,tal;
int d[maxn],inq[maxn],al[maxm],alns[maxm];
//const int sn[]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536};
//const int cn=16;
//queue<int> Q;
int fa(int u)
{
	return d[u]==u?d[u]:d[u]=fa(d[u]);
}
int comp(const edge &a,const edge &b)
{
	return a.b<b.b;
}
void uni(int u,int v)
{
	if (fa(u)!=fa(v))
		d[fa(u)]=d[v];
}
int spfa(int lima,int limb)
{
	int u,v,ve,maxr=0;
	for (int i=0;i<te;i++)
	{
		if (e[i].b>limb) break;
		if (e[i].a>lima) continue;
		if (fa(e[i].u)!=fa(e[i].v))
		{
			uni(e[i].u,e[i].v);
		}
		if (fa(n)==fa(1))
			return e[i].b;
	}
	return 0x3fffffff;
}
int getbl(int ai,int lb)
{
//	cerr<<ai<<" "<<lb<<endl;
	if (alns[ai])
		return alns[ai];
	for (int i=1;i<=n;i++) d[i]=i;
	int res=spfa(ai,lb);
	return (fa(n)==fa(1)?(alns[ai]=res):0x3fffffff);
}
int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	//memset(h,-1,sizeof(h));
	scanf("%d%d",&n,&m);
	int ta,tb,tu,tv;
	for (int i=0;i<m;i++)
	{
		scanf("%d%d%d%d",&tu,&tv,&ta,&tb);
		if (tv<tu) swap(tu,tv);
		if (tv==tu) continue;
		e[te++]=edge(tu,tv,ta,tb);
		al[tal++]=ta;
	}
	sort(&al[0],&al[tal]);
	sort(&e[0],&e[te],comp);
//	tal=unique(&al[0],&al[tal])-&al[0];
	int lima=0x3fffffff,limb=0x3fffffff,ans=0x3fffffff;
	for (int i=0;i<tal;i++)
	{
		limb=getbl(al[i],limb);
		for (int j=65536;j>0;j>>=1)
			if (i+j<tal && al[i+j]<maxn)
				if (getbl(al[i+j],limb)==limb)
					i+=j;
	}
	for (int i=0;i<maxn;i++)
		if (alns[i])
			ans=min(ans,i+alns[i]);
	printf("%d\n",ans==0x3fffffff?-1:ans);
	return 0;
}
