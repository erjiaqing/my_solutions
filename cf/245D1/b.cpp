#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1005;
long long Map[maxn][maxn],f[maxn][maxn],g[maxn][maxn],F[maxn][maxn],G[maxn][maxn];
int m,n;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%lld",&Map[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			f[i][j]=max(f[i-1][j],f[i][j-1])+Map[i][j];
	for (int i=n;i>=1;i--)
		for (int j=1;j<=m;j++)
			g[i][j]=max(g[i+1][j],g[i][j-1])+Map[i][j];
	for (int i=n;i>=1;i--)
		for (int j=m;j>=1;j--)
			F[i][j]=max(F[i+1][j],F[i][j+1])+Map[i][j];
	for (int i=1;i<=n;i++)
		for (int j=m;j>=1;j--)
			G[i][j]=max(G[i-1][j],G[i][j+1])+Map[i][j];
	long long ans=0,tin,tout;
	for (int i=2;i<n;i++)
		for (int j=2;j<m;j++)
		{
			ans=max(ans,
			max(f[i-1][j]+g[i][j-1]+F[i+1][j]+G[i][j+1],
			    f[i][j-1]+g[i+1][j]+F[i][j+1]+G[i-1][j]));
		}
	printf("%lld\n",ans);
}
