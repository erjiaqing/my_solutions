#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
long long f[1<<16][16];
int a[16],n,m,s;
int abs(int x)
{
	return (x<0)?(-x):(x);
}
int main()
{
	scanf("%d%d",&n,&s);
	m=(1<<n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		f[1<<i][i]=1;
	}
	for (int i=0;i<m;i++)
		for (int j=0;j<n;j++)
			if (i & (1<<j))
				for (int k=0;k<n;k++)
					if ((~i) & (1<<k))
						if (abs(a[k]-a[j])>s)
							f[i|(1<<k)][k]+=f[i][j];
	long long ans=0;
	for (int i=0;i<n;i++)
		ans+=f[m-1][i];
	printf("%lld\n",ans);
	return 0;
}
