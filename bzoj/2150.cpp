#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int maxm=55,maxn=maxm*maxm;
int dx[]={ 1, 1, 1, 1,-1,-1,-1,-1},
	dy[]={ 1,-1, 1,-1, 1,-1, 1,-1};
int m,n,r,c;
int id[maxm][maxm],vis[maxn],match[maxn],tt;
char mp[maxm][maxm];
vector <int> e[maxn];
typedef vector<int>::iterator ii;
bool check(int x,int y)
{
	return (x>0&&x<=m&&y>0&&y<=n&&(mp[x][y]=='.'));
}
bool dfs(int u)
{
	for (ii v=e[u].begin();v!=e[u].end();v++)
	{
		if (!vis[*v])
		{
			vis[*v]=true;
			if (!match[*v]||dfs(match[*v]))
			{
				match[*v]=u;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	scanf("%d%d%d%d",&m,&n,&r,&c);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
		{
			cin>>mp[i][j];
			id[i][j]=++tt;
		}
//	dx[0]*=r;dx[1]*=r;dx[4]*=r;dx[5]*=r;dx[2]*=c;dx[3]*=c;dx[6]*=c;dx[7]*=c;
//	dy[0]*=c;dy[1]*=c;dy[4]*=c;dy[5]*=c;dy[2]*=r;dy[3]*=r;dy[6]*=r;dy[7]*=r;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			if (mp[i][j]=='.')
			{
				if (check(i-c,j-r))
					e[id[i-c][j-r]].push_back(id[i][j]);
				if (check(i-c,j+r))
					e[id[i-c][j+r]].push_back(id[i][j]);
				if (check(i-r,j-c))
					e[id[i-r][j-c]].push_back(id[i][j]);
				if (check(i-r,j+c))
					e[id[i-r][j+c]].push_back(id[i][j]);
			}
	int ans=0,sum=0;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			if (mp[i][j]=='.')
			{
				memset(vis,0,sizeof(vis));
				ans+=dfs(id[i][j]);
				sum++;
			}
	printf("%d\n",sum-ans);
	return 0;
}
