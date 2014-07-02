#include <bits/stdc++.h>
using namespace std;
const int maxn=2005;
vector<int> e[maxn];
int d_in[maxn],t_deg[maxn];
int n,m;
int seq[maxn],now,h,t;
int p[maxn],q[maxn],k[maxn];
void sol(int s)
{
	int u,v;
	h=t=0;
	memcpy(t_deg,d_in,sizeof(d_in));
	for (int i=1,p=1;i<=n;i++)
	{
		for (;p<=n && ::p[v=q[p]]<i;p++)
			if (!t_deg[v] && v!=s)
				seq[++t]=v;
		if (h<t)
		{
			u=seq[++h];
			for (vector<int>::iterator c=e[u].begin();c!=e[u].end();c++)
				if (!--t_deg[*c] && *c!=s && ::p[*c]<i)
					seq[++t]=*c;
		}else
			return;
	}
}
bool comp(const int &_a,const int &_b)
{
	return p[_a]<p[_b];
}
int main()
{
	int tp,tu,tv;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&tp),p[i]=n-tp,q[i]=i;
	sort(&q[1],&q[n+1],comp);
	for (int i=1;i<=m;i++) scanf("%d%d",&tu,&tv),e[tv].push_back(tu),d_in[tu]++;
	sol(0);
	for (int t=n;t;t--) printf("%d%c",seq[t],(t>1)?' ':'\n');
	for (int i=1;i<=n;i++) sol(i),printf("%d%c",n-t,i<n?' ':'\n');
	return 0;
}
