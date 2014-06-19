#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
const int maxn=10005;
struct edge{
	int v,l,n;
	edge(){}
	edge(const int &_v,const int &_l,const int &_n):
		v(_v),l(_l),n(_n){}
}e[maxn*2];
int n,k,u,v,l,t,sz,cur,h[maxn],ans;
int s[maxn],f[maxn],d[maxn],mk[maxn*2],a[maxn];
void froot(int x,int p)
{
	s[x]=1;f[x]=0;
	for (int k=h[x];~k;k=e[k].n)
	{
		if (mk[k] && e[k].v != p)
		{
			froot(e[k].v,x);
			s[x]+=s[e[k].v];
			f[x]=max(f[x],s[e[k].v]);
		}
	}
	f[x]=max(f[x],sz-s[x]);
	if (f[x]<f[cur])
		cur=x;
}
void dfs(int x,int p)
{
	s[x]=1;
	a[++a[0]]=d[x];
	for (int k=h[x];~k;k=e[k].n)
	{
		if (mk[k] && e[k].v != p)
		{
			d[e[k].v] = d[x]+e[k].l;
			dfs(e[k].v,x);
			s[x]+=s[e[k].v];
		}
	}
}
int calc(int x,int init)
{
	int rt=a[0]=0;
	d[x]=init;
	dfs(x,0);
	sort(&a[1],&a[a[0]+1]);
	for (int l=1,r=a[0];l<r;)
	{
		if (a[l]+a[r]<=k)
			rt+=r-l++;
		else
			r--;
	}
	return rt;
}
void work(int x)
{
	ans+=calc(x,0);
	for (int k=h[x];~k;k=e[k].n)
	{
		if (mk[k])
		{
			mk[k^1]=false;
			ans-=calc(e[k].v,e[k].l);
			f[0]=sz=s[e[k].v];
			froot(e[k].v,cur=0);
			work(cur);
		}
	}
}
int main()
{
//	memset(h,-1,sizeof(h));t=0;
	while (~scanf("%d%d",&n,&k) && n)
	{
		memset(h,-1,sizeof(h)),t=0,ans=0;
		for (int i=1;i<n;i++)
			scanf("%d%d%d",&u,&v,&l),
			e[t]=edge(v,l,h[u]),mk[t]=1,h[u]=t++,
			e[t]=edge(u,l,h[v]),mk[t]=1,h[v]=t++;
		f[0]=sz=n;
		froot(1,cur=0);
		work(cur);
		printf("%d\n",ans);
	}
	return 0;
}
