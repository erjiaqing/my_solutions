#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int Map[maxn][maxn];
int v[maxn],del[maxn],f[maxn],d[maxn];
int n,m;
int x,y;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&f[i]);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		Map[x][y]=Map[y][x]=true;
		d[x]++;d[y]++;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (Map[i][j])
				v[i]+=f[j];
	int Max=-1,Mpo=-1,ans=0,td=0;
	for (int i=1;i<=n;i++)
	{
		Max=0;Mpo=-1;td=0;
		for (int j=1;j<=n;j++)
			if (!del[j] && (f[j]> Max || (f[j]==Max && v[j]<v[Mpo])))
				Max=f[Mpo=j],td=f[j]*d[j];
		ans+=v[Mpo];
		del[Mpo]=1;
//		cerr<<Mpo<<endl;
		for (int j=1;j<=n;j++)
		{
			if (Map[Mpo][j])
			{
			//	cerr<<Mpo<<" "<<j<<"("<<d[j]<<endl;
				v[j]-=f[Mpo];
				d[j]--;
			}
			Map[j][Mpo]=Map[Mpo][j]=0;
		}
	}
	printf("%d\n",ans);
	return 0;
}

