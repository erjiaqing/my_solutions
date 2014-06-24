#include <bits/stdc++.h>
using namespace std;
const int maxn=600005,maxt=18000005;
int tot,a[maxn],b[maxn],rt[maxn],s[maxt],t[maxt][2];
//Q:可持久化就是动态加点么？求解释
void insert(int x,int &y,int v,int d)
{
	s[y=++tot]=s[x]+1;
	if (d<0)
		return;
	int p=(v>>d)&1;
	t[y][p^1]=t[x][p^1];
	insert(t[x][p],t[y][p],v,d-1);
}
int query(int x,int y,int v,int d)
{
	if (d<0)
		return 0;
	int p=(v>>d)&1;
	if (s[t[y][p^1]]-s[t[x][p^1]])
		return (1<<d)+query(t[x][p^1],t[y][p^1],v,d-1);
	return query(t[x][p],t[y][p],v,d-1);
}
int main()
{
	int n,m;
	char op[5];
	scanf("%d%d",&n,&m);
	insert(rt[0],rt[1],0,24);
	n++;
	for (int i=2;i<=n;i++)
	{
		scanf("%d",&a[i]);
		insert(rt[i-1],rt[i],b[i]=b[i-1]^a[i],24);
	}
	int l,r,x;
	while (m--)
	{
		scanf("%s",op);
		if (op[0]=='A')
		{
			scanf("%d",&a[++n]);
			insert(rt[n-1],rt[n],b[n]=b[n-1]^a[n],24);
		}else
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",query(rt[l-1],rt[r],b[n]^x,24));
		}
	}
	return 0;
}
