#include <iostream>
#include <cstdio>
#include <cstring>
#include <utility>
#include <queue>
using namespace std;
#define x first
#define y second
const int maxn=1005;
const int dx[]={ 1, 1, 1, 0, 0,-1,-1,-1},
	      dy[]={-1, 0, 1,-1, 1,-1, 0, 1};
typedef pair<int,int> pii;
int f[maxn*maxn];
int ma[maxn][maxn];
int pos[maxn][maxn];
int b[maxn*maxn],s[maxn*maxn];
bool vis[maxn][maxn];
int n,tot;
int find_father(int x)
{
	if (f[x]!=x)
		return f[x]=find_father(f[x]);
	return f[x];
}
void uni(int x,int y)
{
	int fx=find_father(x);
	f[fx]=y;
}
void push_up(int x)
{
	int fx=find_father(x);
	b[fx]=max(b[fx],b[x]);
	s[fx]=min(s[fx],s[x]);
}
pii bfs()
{
	int ux,uy,nx,ny;
	pii tmp;
	queue <pii> Q;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (!vis[i][j])
			{
//				printf("(%d,%d)\n",i,j);
				Q.push(make_pair(i,j));
				vis[i][j]=true;
				while (!Q.empty())
				{
					tmp=Q.front();Q.pop();
					ux=tmp.x;uy=tmp.y;
//					printf("[Vis]%d %d\n",ux,uy);
					for (int k=0;k<8;k++)
					{
						nx=ux+dx[k];ny=uy+dy[k];
						if (nx>0&&nx<=n&&ny>0&&ny<=n)
						{
							b[pos[ux][uy]]=max(ma[nx][ny],b[pos[ux][uy]]);
							s[pos[ux][uy]]=min(ma[nx][ny],s[pos[ux][uy]]);
							if (ma[nx][ny]==ma[ux][uy]&&!vis[nx][ny])
							{
//								printf("--> %d,%d\n",nx,ny);
								vis[nx][ny]=true;
								uni(pos[nx][ny],pos[ux][uy]);
								Q.push(make_pair(nx,ny));
							}
						}
					}
				}
			}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			push_up(pos[i][j]);
	tmp=make_pair(0,0);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (f[pos[i][j]]==pos[i][j])
			{
//				if (b[pos[i][j]]==ma[i][j])
//					printf("B %d %d\n",i,j);
				tmp.x+=(b[pos[i][j]]==ma[i][j]);
				tmp.y+=(s[pos[i][j]]==ma[i][j]);
			}
		}
	return tmp;
}
int main()
{
	memset(s,0x3f,sizeof(s));
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			pos[i][j]=++tot;
			f[pos[i][j]]=pos[i][j];
			scanf("%d",&ma[i][j]);
			b[pos[i][j]]=s[pos[i][j]]=ma[i][j];
		}
	pii ans=bfs();
	printf("%d %d\n",ans.x,ans.y);
	return 0;
}
