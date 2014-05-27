#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=1005;
vector<int>e[maxn];
typedef vector<int>::iterator ii;
int f[maxn][maxn],vis[maxn],n;
void dp(int u)
{
	int sum1,sum2,fa;
	sum1=sum2=fa=0;
	vis[u]=true;
	for (ii v=e[u].begin();v!=e[u].end();v++)
	{
		if (!vis[*v])
		{
			dp(*v);
			f[u][0]+=min(min(min(f[*v][0],f[*v][4]),f[*v][1]),min(f[*v][2],f[*v][3]));
			sum1+=min(min(f[*v][0],f[*v][1]),min(f[*v][2],f[*v][3]));
			sum2+=min(min(f[*v][0],f[*v][1]),f[*v][2]);
		}else
		{
			fa=*v;
		}
	}
	f[u][3]=sum2;
	f[u][4]=sum1;
	f[u][1]=f[u][2]=850522875;
	for (ii v=e[u].begin();v!=e[u].end();v++)
	{
		if (*v!=fa)
		{
			f[u][1]=min(f[u][1],f[*v][0]+sum1-min(min(f[*v][0],f[*v][1]),min(f[*v][2],f[*v][3])));
			f[u][2]=min(f[u][2],f[*v][1]+sum2-min(min(f[*v][0],f[*v][1]),f[*v][2]));
		}
	}
	f[u][0]++;
}
int main()
{
	scanf("%d",&n);
	int t;
	for (int i=1;i<n;i++)
	{
		scanf("%d",&t);
		e[t].push_back(i+1);
		e[i+1].push_back(t);
	}
	dp(1);
	printf("%d\n",min(min(f[1][0],f[1][1]),f[1][2]));
	return 0;
}
