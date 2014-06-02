#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=100005;
vector <int> e[maxn];
vector <int> s[maxn];
typedef vector<int>::iterator ii;
int n;
int vis[maxn],q[maxn],ql,qr;
int init[maxn],goal[maxn];
int sel[maxn],fasel[maxn],fafasel[maxn];
void dfs(int u)
{
	if ((fafasel[u]^init[u])!=goal[u])
		sel[u]=true;
	for (ii v=s[u].begin();v!=s[u].end();v++)
	{
		fasel[*v]^=(sel[u]^fafasel[u]);
		fafasel[*v]^=fasel[u];
		dfs(*v);
	}
}
int main()
{
	int u,v;
	scanf("%d",&n);
	for (int i=1;i<n;i++)
		scanf("%d%d",&u,&v),e[u].push_back(v),e[v].push_back(u);
	for (int i=1;i<=n;i++)
		scanf("%d",&init[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&goal[i]);
	q[ql=qr=1]=1;
	for (;ql<=qr;ql++)
	{
		vis[u=q[ql]]=1;
		for (ii v=e[u].begin();v!=e[u].end();v++)
			if (!vis[*v])
				s[u].push_back(q[++qr]=*v);
	}
	dfs(1);
	int cnt=0;
	for (int i=1;i<=n;i++)
		cnt+=sel[i];
	printf("%d\n",cnt);
	for (int i=1;i<=n;i++)
	{
		if (sel[i])
			printf("%d\n",i);
	}
	return 0;
}
