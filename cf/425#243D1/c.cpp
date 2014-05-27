#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
const int maxn=100005,maxj=305;
vector<int>nextb[maxn];
typedef vector<int>::iterator vii;
int dp[maxn][maxj];
int a[maxn],b[maxn];
int n,m,s,e,maxjj;
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&e);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for (int i=0;i<m;i++)
		scanf("%d",&b[i]),nextb[b[i]].push_back(i);
	sort(&b[1],&b[n+1]);
	int val,pre;
	vii pos;
	maxjj=s/e;
	int ans=0;
	for (int i=0;i<n;i++)
	{
		val=a[i];
		for (int j=0;j<=maxjj;j++)
		{
			dp[i][j]=0x3f3f3f3f;
			if (j==0)
				dp[i][j]=0;
			if (i)
				dp[i][j]=min(dp[i][j],dp[i-1][j]);
			pre=0x3f3f3f3f;
			if (i && j)
				pre=dp[i-1][j-1];
			if (j==1)
				pre=0;
			if (!j)
				continue;
			pos=lower_bound(nextb[val].begin(),nextb[val].end(),pre);
			if (pos!=nextb[val].end())
			{
				dp[i][j]=min(dp[i][j],*pos+1);
				if (i+1+*pos+1+j*e<=s)
					ans=max(ans,j);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
