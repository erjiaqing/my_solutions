#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>
using namespace std;
const int maxn=100005,maxm=300005;
vector<int> e[maxn];
stack<int> sta;
typedef vector<int>::iterator vii;
int cost[maxn];
int n,m;
int dfn[maxn],low[maxn],bel[maxn],scc[maxn],scn,did;
int ins[maxn];
int minc[maxn],mincount[maxn];
void tarjan(int u)
{
	int vv;
	dfn[u]=low[u]=++did;
	ins[u]=true;
	sta.push(u);
	for (vii v=e[u].begin();v!=e[u].end();v++)
	{
		if (!dfn[*v])
		{
			tarjan(*v);
			low[u]=min(low[u],low[*v]);
		}else if (ins[*v])
		{
			low[u]=min(low[u],dfn[*v]);
		}
	}
	if (dfn[u]==low[u])
	{
		scn++;
		do
		{
			vv=sta.top();sta.pop();
			ins[vv]=false;
			bel[vv]=scn;
		}while (vv!=u);
	}
}
int main()
{
	int u,v;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&cost[i]);
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
		scanf("%d%d",&u,&v),e[u].push_back(v);
	for (int i=1;i<=n;i++)
		if (!dfn[i])
			tarjan(i);
	memset(minc,0x3f,sizeof(minc));
	for (int i=1;i<=n;i++)
	{
		if (cost[i]<minc[bel[i]])
		{
			minc[bel[i]]=cost[i];
			mincount[bel[i]]=1;
		}else if (cost[i]==minc[bel[i]])
		{
			mincount[bel[i]]++;
		}
	}
	int ans=0,ansc=1;
	for (int i=1;i<=scn;i++)
	{
		ans+=minc[i];
		ansc*=mincount[i];
	}
	printf("%d %d\n",ans,ansc);
	return 0;
}
