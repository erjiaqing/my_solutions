#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <stack>
using namespace std;
map<string,int> mp1,mp2;
vector <int>e[4005];
stack <int> S;
typedef vector<int>::iterator ii;
string tmp1,tmp2;
int n,m;
int id,num,vis[4005],dfn[4005],low[4005],sze[4005],scc[4005];
void tarjan(int u)
{
	dfn[u]=low[u]=++id;
	S.push(u);
	for (ii v=e[u].begin();v!=e[u].end();v++)
	{
		if (!dfn[*v])
		{
			tarjan(*v);
			low[u]=min(low[u],low[*v]);
		}else if (!vis[*v])
		{
			low[u]=min(low[u],dfn[*v]);
		}
	}
	if (low[u]==dfn[u])
	{
		int v;
		num++;
		do
		{
			v=S.top();
			S.pop();
			vis[v]=1;
			scc[v]=num;
			sze[num]++;
		}while (u!=v);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		cin>>tmp1>>tmp2;mp1[tmp1]=mp2[tmp2]=i;
	}
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		cin>>tmp1>>tmp2;
		e[mp1[tmp1]].push_back(mp2[tmp2]);
	}
	for (int i=1;i<=n;i++)
		if (!vis[i])
			tarjan(i);
	for (int i=1;i<=n;i++)
	{
		if (sze[scc[i]]==1)
			printf("Safe\n");
		else
			printf("Unsafe\n");
	}
	return 0;
}
