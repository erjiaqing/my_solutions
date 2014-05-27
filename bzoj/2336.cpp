#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
//#include <cstdlib>
using namespace std;
const int maxn=25;
struct task
{
	int flag,ta,tb;
	task(){}
	task(int _flag,int _ta,int _tb):
		flag(_flag),ta(_ta),tb(_tb){}
}t[maxn],ta[maxn],tb[maxn],a[maxn],b[maxn],t1[maxn],t2[maxn];
bool cmpa(task a,task b){return (a.ta==b.ta)?(a.tb<b.tb):(a.ta>b.ta);}
bool cmpb(task a,task b){return (a.tb==b.tb)?(a.ta<b.ta):(a.tb>b.tb);}
int ans=2147483647;
int n,sa,sb,st,num[maxn];
void work()
{
	sort(&a[0],&a[sa],cmpa);
	sort(&b[0],&b[sb],cmpb);
	int ta=0,tb=0;
	for (int i=0;i<sa;i++)
		ta+=a[i].ta;
	for (int i=0;i<sb;i++)
		tb+=b[i].tb;
	int t1=ta,t2=tb,tmp,ansa=1<<30;
	for (int i=1;i<=2000;i++)
	{
		ta=t1;tb=t2;
		for (int j=0;j<sa;j++)
			::ta[j]=a[j];
		for (int j=0;j<sb;j++)
			::tb[j]=b[j];
		if (sa)
			swap(a[rand()%sa],a[rand()%sa]);
		if (sb)
			swap(b[rand()%sa],b[rand()%sb]);
		tmp=0;
		for (int j=0;j<sa;j++)
		{
			tmp+=a[j].ta;
			tb=max(tb,tmp)+a[j].tb;
		}
		tmp=0;
		for (int j=0;j<sb;j++)
		{
			tmp+=b[j].tb;
			ta=max(ta,tmp)+b[j].ta;
		}
		tmp=max(ta,tb);
		if (tmp>=ansa)
		{
			for (int j=0;j<sa;j++)
				a[j]=::ta[j];
			for (int j=0;j<sb;j++)
				b[j]=::tb[j];
		}
		ansa=min(ansa,tmp);
		ans=min(ans,tmp);
	}
}
void dfs(int p)
{
	if (p==st)
	{
		for (int i=0;i<sa;i++)
			t1[i]=a[i];
		for (int i=0;i<sb;i++)
			t2[i]=b[i];
		work();
		for (int i=0;i<sa;i++)
			a[i]=t1[i];
		for (int i=0;i<sb;i++)
			b[i]=t2[i];
		return;
	}
	a[sa++]=t[num[p]];
	if (rand()%32768<=25000)
		dfs(p+1);
	sa--;
	b[sb++]=t[num[p]];
	if (rand()%32768<=25000)
		dfs(p+1);
	sb--;
}
int main()
{
	srand(0);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d%d%d",&t[i].flag,&t[i].ta,&t[i].tb);
		if (t[i].flag==1)
			a[sa++]=t[i];
		if (t[i].flag==2)
			b[sb++]=t[i];
		if (t[i].flag==3)
			num[st++]=i;
	}
	dfs(0);
	printf("%d\n",ans);
	return 0;
}
