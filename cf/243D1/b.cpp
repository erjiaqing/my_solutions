#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=105;
int mat[maxn][maxn];
int n,m,k;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			scanf("%d",&mat[i][j]);
	int ans=11,tmp,cnt;
	if (n>k)
	{
		for (int i=0;i<n;i++)
		{
			tmp=0;
			for (int j=0;j<n;j++)
			{
				cnt=0;
				for (int k=0;k<m;k++)
					cnt+=(mat[j][k]^mat[i][k]);
				tmp+=min(cnt,m-cnt);
			}
			ans=min(ans,tmp);
		}
	}else
	{
		for (int i=0;i<(1<<n);i++)
		{
			tmp=0;
			for (int j=0;j<m;j++)
			{
				cnt=0;
				for (int k=0;k<n;k++)
					cnt+=(mat[k][j]^((i>>k)&1));
				tmp+=min(cnt,n-cnt);
			}
			ans=min(ans,tmp);
		}
	}
	printf("%d\n",ans>k?-1:ans);
	return 0;
}
