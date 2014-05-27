#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=10005;
int match[maxn*2];
vector <int> e[maxn*2];
typedef vector <int>::iterator ii;
int vis[maxn*2];
int n,t,u1,u2;
bool find(int u)
{
	for (ii v=e[u].begin();v!=e[u].end();v++)
	{
		if (!vis[*v])
		{
			vis[*v]=true;
			if (match[*v]==-1 || find(match[*v]))
			{
				match[*v]=u;
				match[u]=*v;
				return true;
			}
		}
	}
	return false;
}
bool hungary()
{
	int ans=0;
	for (int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if (find(i))
			ans++;
		else
			return false;
	}
	return ans==n;
}
int main()
{
	memset(match,-1,sizeof(match));
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		u1=(i-t);if (u1<=0) u1+=n;
		u2=(i+t);if (u2>n)  u2-=n;
		if (u1>u2)
			swap(u1,u2);
		e[i].push_back(u1+n);
		e[i].push_back(u2+n);
	}
	if (hungary())
	{
		for (int i=1;i<n;i++)
			printf("%d ",match[i]-n-1);
		printf("%d\n",match[n]-n-1);
	}else
	{
		printf("No Answer\n");
	}
	return 0;
}
