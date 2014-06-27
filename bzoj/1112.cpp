#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;
const double a=0.75;
struct tn  //tree node
{
	int s[2],v,f,sz,n;
}t[maxn*2];
int ttn,root;
int n,k,h[maxn];
int e[maxn],ec; //erase,erase count
long long bit[maxn];
int cnt[maxn];
#define lowbit(x) ((x)&(-(x)))
void bit_insert(int p,long long x)
{
	for (int _p=p;_p<maxn;_p+=lowbit(_p)) bit[_p]+=x;
	if (x>0)
		for (int _p=p;_p<maxn;_p+=lowbit(_p)) cnt[_p]++;
	else
		for (int _p=p;_p<maxn;_p+=lowbit(_p)) cnt[_p]--;
}
long long bit_query(int p)
{
	long long ret=0;
	for (;p>0;p-=lowbit(p)) ret+=bit[p];
	return ret;
}
int bit_count(int p)
{
	int ret=0;
	for (;p>0;p-=lowbit(p)) ret+=cnt[p];
	return ret;
}
void init()
{
	ttn=2;root=1;
	t[1].n=-13257829;t[1].sz=2;t[1].s[1]=2;
	t[2].n=13257829;t[2].sz=1;t[2].f=1;
}
bool balance(int po)
{
	return 
		t[po].sz*a >= t[t[po].s[0]].sz &&
		t[po].sz*a >= t[t[po].s[1]].sz;
}
void travel(int u)
{
	if (t[u].s[0]) travel(t[u].s[0]);
	e[++ec]=u;
	if (t[u].s[1]) travel(t[u].s[1]);
}
int build(int l,int r)
{
	if (l>r) return 0;
	int mid=(l+r)/2,po=e[mid];
	t[t[po].s[0]=build(l,mid-1)].f=po;
	t[t[po].s[1]=build(mid+1,r)].f=po;
	t[po].sz=t[t[po].s[0]].sz+t[t[po].s[1]].sz+1;
	return po;
}
void rebuild(int po)
{
	ec=0;travel(po);
	int fa=t[po].f,ws=(t[t[po].f].s[1]==po);
	int npo=build(1,ec);
	t[t[fa].s[ws]=npo].f=fa;
	if (po==root) root=npo;
}
void insert(int num)
{
	int now=root,npo=++ttn;
	t[npo].sz=1;t[npo].n=num;
	while (1)
	{
		t[now].sz++;
		bool ws=(num>=t[now].n);
		if (t[now].s[ws]) now=t[now].s[ws];
		else {t[t[now].s[ws]=npo].f=now;break;}
	}
	int inv=0;
	for (int i=npo;i;i=t[i].f) if (!balance(i)) inv=i;
	if (inv) rebuild(inv);
}
int getkth(int k)
{
	int now=root;
	while (1)
	{
		if (t[t[now].s[0]].sz==k-1) return now;
		else if (t[t[now].s[0]].sz>=k) now=t[now].s[0];
		else k-=t[t[now].s[0]].sz+1,now=t[now].s[1];
	}
	return now;
}
int getn(int num)
{
	int now=root;
	while (1)
	{
		if (t[now].n==num) return now;
		else now=t[now].s[t[now].n<num];
	}
}
void erase(int po)
{
//	cerr<<po<<" "<<t[po].n<<" "<<endl;
	if (t[po].s[0] && t[po].s[1])
	{
		int tpo=t[po].s[0];
		while (t[tpo].s[1]) tpo=t[tpo].s[1];
		t[po].n=t[tpo].n;
		po=tpo;
	}
	int son=(t[po].s[0])?t[po].s[0]:t[po].s[1],ws=(t[t[po].f].s[1]==po);
	t[t[t[po].f].s[ws]=son].f=t[po].f;
	for (int i=t[po].f;i;i=t[i].f) t[i].sz--;
	if (po==root) root=son;
}
long long calc()
{
	int po=getkth((k+1)/2+1);
	long long ret=0,a,b,c,d,nu=t[po].n;
	a=bit_query(t[po].n);c=bit_count(t[po].n);
	b=(bit_query(maxn-1)-a);d=bit_count(maxn-1)-c;
//	printf("%lld %lld %lld %lld %lld\n",nu,a,b,c,d);
	return c*nu-a+b-d*nu;
}
int main()
{
	long long ans=0,tans;
	init();
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) scanf("%d",&h[i]),h[i]++;
	for (int i=1;i<=k;i++) insert(h[i]),bit_insert(h[i],h[i]);
	ans=tans=calc();
	for (int i=k+1;i<=n;i++)
	{
//		insert(h[i]);bit_insert(h[i],h[i]);
		erase(getn(h[i-k]));bit_insert(h[i-k],-h[i-k]);
		insert(h[i]);bit_insert(h[i],h[i]);
		tans=calc();
//		cerr<<ans<<" "<<tans<<endl;
		ans=min(ans,tans);
	}
	printf("%lld\n",ans);
	return 0;
}
