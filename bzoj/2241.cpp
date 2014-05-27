#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=105;
int a[maxn][maxn],b[maxn*2][maxn*2];
int n,m;
bool check(int r,int c)
{
	memset(b,0,sizeof(b));
	for (int i=1;i<=n+1;i++)
		for (int j=1;j<=m+1;j++)
			b[i][j]=a[i][j]+a[i-1][j-1]-a[i][j-1]-a[i-1][j];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int t=b[i][j];b[i][j]=0;
			b[i+r][j+c]-=t;b[i+r][j]+=t;b[i][j+c]+=t;
		}
	for (int i=1;i<=n+r;i++)
		for (int j=1;j<=m+c;j++)
			if (b[i][j])
				return 0;
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);int ans=0x3f3f3f3f;int sum=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&a[i][j]),sum+=a[i][j];
	for (int i=1;i<=n;i++)
		if (sum%i==0)
			for (int j=1;j<=m;j++)
				if (sum%(i*j)==0)
					check(i,j)?ans=min(ans,sum/(i*j)):0;
	printf("%d",ans);
	return 0;
}
