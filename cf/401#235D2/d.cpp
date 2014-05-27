#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[20],b[20],m,bi;
int app[1<<19][20];
long long n;
long long dp[1<<19][105];
int main()
{
	scanf("%lld%d",&n,&m);
	while (n)
	{
		a[bi++]=n%10;
		b[a[bi-1]]++;
		n/=10;
	}
	for (int i=0;i<bi;i++)
		if (a[i])
			dp[1<<i][a[i]%m]=1;
	for (int i=1;i<(1<<bi);i++)
		for (int j=0;j<bi;j++)
			if (((1<<j)&i)==0)
			{
				bool flag=1;
				for (int x=0;x<j;x++)
					if ((a[j]==a[x]) && ((1<<x) & i)==0) {flag=false;break;}
				for (int x=j+1;x<bi;x++)
					if ((a[j]==a[x]) && ((1<<x) & i)!=0) {flag=false;break;}
				if (flag)
					app[i][++app[i][0]]=j;
			}
	for (int i=1;i<(1<<bi);i++)
		for (int j=0;j<m;j++)
			for (int k=1;k<=app[i][0];k++)
					dp[i|(1<<app[i][k])][(j*10+a[app[i][k]])%m]+=dp[i][j];
	printf("%lld\n",dp[(1<<bi)-1][0]);
	return 0;
}
