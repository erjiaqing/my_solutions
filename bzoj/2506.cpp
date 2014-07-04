#include <bits/stdc++.h>
using namespace std;
const int maxai=10005,maxn=100005,maxm=100005;
struct query{
	int l,r,p,k;
	int ans[2];
}q[maxn];
struct query2{
	int l,p,k,fl,src,ans;
	query2(){}
	query2(const int &_l,const int &_p,const int &_k,const int &_fl,const int &_src,const int &_ans):
		l(_l),p(_p),k(_k),fl(_fl),src(_src),ans(_ans){}
}q2[maxn*2];
bool comp(const query2 &a,const query2 &b)
{
	return a.l<b.l;
}
int app[maxai],a[maxn];
int n,m,tk;
int getans(int p,int k)
{
	int ans=0;
	for (int i=0;p*i+k<maxai;i++) ans+=app[p*i+k];
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&q[i].l,&q[i].r,&q[i].p,&q[i].k);
		q2[tk++]=query2(q[i].l-1,q[i].p,q[i].k,0,i,0);
		q2[tk++]=query2(q[i].r,q[i].p,q[i].k,1,i,0);
	}
	sort(&q2[0],&q2[tk],comp);
	int now=1;
	for (int i=0;i<tk;i++)
	{
		for (;now<=q2[i].l;now++)
			app[a[now]]++;
		q2[i].ans=getans(q2[i].p,q2[i].k);
		q[q2[i].src].ans[q2[i].fl]=q2[i].ans;
	}
	for (int i=1;i<=m;i++) printf("%d\n",q[i].ans[1]-q[i].ans[0]);
	return 0;
}
