#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=105;
bool map[maxn][maxn];
int inq[maxn*2],tot;
int mark[maxn*2];
int n,m,tu,tv;
bool find(int x)
{
	for (int j=1;j<=n;j++)
	{
		if (!inq[j]&&map[x][j])
		{
			inq[j]=true;
			if (!mark[j] || find(mark[j]))
			{
				mark[j]=x;
				return true;
			}
		}
	}
	return false;
}
int getans()
{
	int ret=0;
	for (int i=1;i<=n;i++)
	{
		memset(inq,0,sizeof(inq));
		if (find(i))
			ret++;
	}
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&tu,&tv);
		map[tu][tv]=true;
	}
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				map[i][j]=map[i][j]||(map[i][k]&&map[k][j]);
	printf("%d\n",n-getans());
	return 0;
}
