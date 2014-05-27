#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct P/*ipe*/{
	int x,y,h;
}p[25];
struct Link{
	int S,T,H;
};
bool comp(P a,P b)
{
	return a.x<b.x;
}
int X[105],Y[105];
int dfs(int pipe,int needh)//returns with V
{
}
int x,y,d,n,l;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].h);
	sort(&p[1],&p[n+1],comp);
	for (int i=1;i<=n;i++)
		X[p[i].x]=i;
	return 0;
}
