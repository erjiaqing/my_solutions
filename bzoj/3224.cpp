#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const double a=0.75;
struct gtn{
	int s[2],n,f,sz;
}t[maxn];
int e[maxn],ec;
int tn,root;
void init()
{
	tn=2;
	root=1;
	t[1].n=-2147483647;t[1].sz=2;t[1].s[1]=2;
	t[2].n= 2147482647;t[2].sz=1;t[2].f=1;
}
void travel(int po)
{
	if (t[po].s[0]) travel(t[po].s[0]);
//	cerr<<po<<" ["<<t[po].n<<"] ";
	e[++ec]=po;
	if (t[po].s[1]) travel(t[po].s[1]);
}
int rebuild(int l,int r)
{
	if (r<l) return 0;
	int mid=(l+r)/2,po=e[mid];
	t[t[po].s[0]=rebuild(l,mid-1)].f=po;
	t[t[po].s[1]=rebuild(mid+1,r)].f=po;
	t[po].sz=t[t[po].s[0]].sz+t[t[po].s[1]].sz+1;
	return po;
}
void rebuild(int po)
{
	ec=0;
	travel(po);
	int fa=t[po].f,ws=(t[t[po].f].s[1]==po);
	int npo=rebuild(1,ec);
	t[t[fa].s[ws]=npo].f=fa;
	if (po==root) root=npo;
}
bool balance(int po)
{
	return t[po].sz*a >= t[t[po].s[0]].sz &&
		   t[po].sz*a >= t[t[po].s[1]].sz;
}
void insert(int num)
{
	int po=++tn,now=root,ws;
	t[tn].n=num;t[tn].sz=1;
	while (1)
	{
//		cerr<<now<<endl;
		ws=(num>=t[now].n);t[now].sz++;
		if (t[now].s[ws]) now=t[now].s[ws];
		else{t[t[now].s[ws]=po].f=now;break;}
	}
	int inv=0;
//	cerr<<"~~~";
	for (int i=po;i;i=t[i].f) if (!balance(i)) inv=i;
	if (inv) rebuild(inv);
}
int Rank(int num)
{
	int now=root,ans=0;
	while (now)
	{
//		cerr<<now<<" "<<t[now].n<<" "<<t[now].sz;
		if (t[now].n<num) ans+=t[t[now].s[0]].sz+1,now=t[now].s[1];
		else now=t[now].s[0];
	}
	return ans;
}
int getk(int k)
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
int getn(int n)
{
	int now=root;
	while (1)
	{
		if (t[now].n==n) return now;
		else now=t[now].s[t[now].n<n];
	}
}
void erase(int po)
{
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
int succ(int num)
{
	int now=root,ans=2147483647;
	while (now)
	{
		if (t[now].n>num) ans=min(ans,t[now].n),now=t[now].s[0];
		else now=t[now].s[1];
	}
	return ans;
}
int pred(int num)
{
	int now=root,ans=-2147483647;
	while (now)
	{
		if (t[now].n<num) ans=max(ans,t[now].n),now=t[now].s[1];
		else now=t[now].s[0];
	}
	return ans;
}
int n,op,x;
int main()
{
	init();
//	cerr<<"~";
	scanf("%d",&n);
//	cerr<<"~";
	while (n--)
	{
//		travel(root);
//		cerr<<endl;
//		cerr<<" > \n";
		scanf("%d%d",&op,&x);
		if (op==1) insert(x);
		else if (op==2) erase(getn(x));
		else if (op==3) printf("%d\n",Rank(x));
		else if (op==4) printf("%d\n",t[getk(x+1)].n);
		else if (op==5) printf("%d\n",pred(x));
		else if (op==6) printf("%d\n",succ(x));
	}
	return 0;
}
