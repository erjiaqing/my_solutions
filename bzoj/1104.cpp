#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
const int maxn=1005;
const int dx[]={ 1, 0,-1, 0},
	      dy[]={ 0, 1, 0,-1};
int h[maxn][maxn],w[maxn][maxn];
int m,n;
//========================================================================
struct node{
	int x,y,n;
	node(){}
	node(int _x,int _y,int _n):x(_x),y(_y),n(_n){}
}e[maxn*maxn*10];
int h1[maxn],h2[maxn],t1;
void insert(int &hh,int x,int y)
{
	t1++;
	e[t1]=node(x,y,hh);hh=t1;
}
//========================================================================
int main()
{
	int tot=1000,nx,ny,_x,_y,ans=0;
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&h[i][j]);
			if (h[i][j]>0)
			{
				insert(h1[h[i][j]],i,j);
			}else
			{
				h[i][j]=-h[i][j];
			}
		}
	for (int i=1000;i>=1;i--)
		if (h1[i]>0)
		{
			tot=i;
			break;
		}
	memset(w,-1,sizeof(w));
	for (int i=1;i<=tot;i++)
	{
		while (1)
		{
			if (h2[i]>0)
			{
				nx=e[h2[i]].x;ny=e[h2[i]].y;
				h2[i]=e[h2[i]].n;
				for (int j=0;j<4;j++)
				{
					_x=nx+dx[j];_y=ny+dy[j];
					if (((_x>0)&&(_x<=m))&&((_y>0)&&(_y<=n))&&(w[_x][_y]==-1))
					{
						w[_x][_y]=max(w[nx][ny],h[_x][_y]);
						insert(h2[w[_x][_y]],_x,_y);
					}
				}
			}else if (h1[i]>0)
			{
				nx=e[h1[i]].x;ny=e[h1[i]].y;
				h1[i]=e[h1[i]].n;
				if (~w[nx][ny])
					continue;
				ans++;
				w[nx][ny]=h[nx][ny];
				for (int j=0;j<4;j++)
				{
					_x=nx+dx[j];_y=ny+dy[j];
					if (((_x>0)&&(_x<=m))&&((_y>0)&&(_y<=n))&&(w[_x][_y]==-1))
					{
						w[_x][_y]=max(h[_x][_y],w[nx][ny]);
						insert(h2[w[_x][_y]],_x,_y);
					}
				}
			}else
				break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
