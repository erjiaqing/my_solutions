/*
 * A & B = (A NAND B) NAND (A NAND B)
 * A | B = (A NAND A) NAND (B NAND B)
 * A ^ B = (A AND  B) NAND (A  OR  B)
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1005,maxk=105;
int n,k;
long long l,r;
long long a[maxn];
int p[maxk][maxk];
int f[maxk],top[maxk];
long long solve(long long x)
{
	if (x<0)
		return 0;
	long long ans=0;
	for (int i=0;i<k;i++)
		f[i]=-1;
	for (int i=k-1;i>=1;i--)
	{
		if (f[i]==0)
		{
			if (x&(1LL<<i))
			{
				int v=0;
				for (int j=0;j<i;j++)
					if (top[j]==1)
						v++;
				ans+=1LL<<v;
				break;
			}
			continue;
		}
		if (f[i]==1 && !(x&(1LL<<i))) break;
		if (f[i]==1) continue;
		if (x & (1LL<<i))
		{
			for (int j=0;j<i;j++)
				if (p[i][j])
					f[j]=0;
			int v=0;
			for (int j=0;j<i;j++)
				if (top[j]==1)
					v++;
			ans+=1LL<<v;
			for (int j=0;j<i;j++)
				if (p[i][j])
					f[j]=1;
		}else
		{
			for (int j=0;j<i;j++)
				if (p[i][j])
					f[j]=0;
		}
	}
	return ans;
}
int main()
{
	scanf("%d%d%lld%lld",&n,&k,&l,&r);
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for (int i=0;i<k;i++)
		for (int j=0;j<k;j++)
		{
			p[i][j]=1;
			for (int x=1;x<=n;x++)
			{
				long long tx=a[x]&(1LL<<i);
				long long ty=a[x]&(1LL<<j);
				if ((tx>0)^(ty>0))
					p[i][j]=0;
			}
		}
	for (int i=0;i<k;i++)
	{
		top[i]=1;
		for (int j=i+1;j<k;j++)
			if (p[i][j])
				top[i]=0;
	}
	r=min(r,(1LL<<k)-1);
	if (l>r)
		printf("0\n");
	else
		printf("%lld\n",solve(r)-solve(l-1));
	return 0;
}
