#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn=705;
const int dx[4]={ 0, 1, 0,-1},
	      dy[4]={ 1, 0,-1, 0};
int h[maxn][maxn],f[maxn][maxn];
int c[maxn][maxn];
int n,m;
char q[10];
bool chk(int x,int y)
{
	return (x>0&&x<=n&&y>0&&y<=n&&c[x][y]);
}
int dfs(int _x,int _y)
{
	if (~c[_x][_y])
		return 0;
	if (f[_x][_y])
		return f[_x][_y];
	f[_x][_y]=1;
	for (int i=0;i<4;i++)
		if (chk(_x+dx[i],_y+dy[i]) && h[_x][_y]>h[_x+dx[i]][_y+dy[i]])
			f[_x][_y]=max(f[_x][_y],dfs(_x+dx[i],_y+dy[i])+1);
	return f[_x][_y];
}
int main()
{
	scanf("%d",&n);
	memset(c,-1,sizeof(c));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&h[i][j]);
	scanf("%d",&m);
	int xx0,yy0,xx1,yy1,hh1;
	while (m--)
	{
		scanf("%s",q);
		if (q[0]=='Q')
		{
			int ans=0;
			memset(f,0,sizeof(f));
			for (int i=1;i<=n;i++)
				for (int j=1;j<=n;j++)
					ans=max(ans,dfs(i,j));
			printf("%d\n",ans);
		}else if (q[0]=='C')
		{
			scanf("%d%d%d",&xx0,&yy0,&hh1);
			h[xx0][yy0]=hh1;
		}else if (q[0]=='S')
		{
			scanf("%d%d%d%d",&xx0,&yy0,&xx1,&yy1);
			for (int i=xx0;i<=xx1;i++)
				for (int j=yy0;j<=yy1;j++)
					c[i][j]=0;
		}else if (q[0]=='B')
		{
			scanf("%d%d%d%d",&xx0,&yy0,&xx1,&yy1);
			for (int i=xx0;i<=xx1;i++)
				for (int j=yy0;j<=yy1;j++)
					c[i][j]=-1;
		}
	}
	return 0;
}
