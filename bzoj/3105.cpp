#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=105,bit=31,inf=1000000000;
int v[maxn],c[maxn];
long long a[maxn];
int n,m;
long long ans=0;
bool gauss(int n,int m)
{
	int k=1;
	for (int i=1;i<=n;i++)
	{
		int p=0;
		for (int j=k;j<=n;j++)
			if (a[j]&(1<<(i-1)))
			{
				p=j;break;
			}
		if (p)
		{
			swap(a[k],a[p]);
			for (int j=k+1;j<=n;j++)
				if (a[j]&(1<<(i-1)))
					a[j]^=a[k];
			k++;
		}
	}
	for (int i=1;i<=n;i++)
		if (a[i]==(1<<m))
			return 0;
	return 1;
}
bool judge(int x)
{
	for (int i=1;i<=m;i++)
		a[i]=0;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=bit;j++)
			if (v[i]&(1<<(j-1)))
				a[j]|=(1<<(i-1));
	for (int j=1;j<=bit;j++)
		if (x&(1<<(j-1)))
			a[j]|=(1<<m);
	return !gauss(bit,m);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	sort(&c[1],&c[n+1],greater<int>());
	v[m=1]=c[1];
	for (int i=2;i<=n;i++)
		if (judge(c[i]))
			v[++m]=c[i];
		else
			ans+=c[i];
	printf("%lld\n",ans);
	return 0;
}

