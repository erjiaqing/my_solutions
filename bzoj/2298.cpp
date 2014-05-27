#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
using namespace std;
const int maxn=100005;
typedef vector<int>::iterator ii;
typedef pair<int,int> ll;
typedef vector<ll>::iterator piii;
#define x first
#define y second
vector<int> match[maxn];
map<ll,int> sum;
int dp[maxn];
int n,tx,ty;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&tx,&ty);
		int l=tx+1,r=n-ty;
		if (l>r)
			continue;
		if (sum.find(ll(l,r))==sum.end())
		{
			match[r].push_back(l);
			sum[ll(l,r)]=1;
		}else
		{
			if (sum[ll(l,r)]<r-l+1)
				++sum[ll(l,r)];
		}
	}
	for (int i=1;i<=n;i++)
	{
		dp[i]=dp[i-1];
		for (ii j=match[i].begin();j!=match[i].end();j++)
			dp[i]=max(dp[i],dp[*j-1]+sum[ll(*j,i)]);
	}
	printf("%d\n",n-dp[n]);
	return 0;
}
