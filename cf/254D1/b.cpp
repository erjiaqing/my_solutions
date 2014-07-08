#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
long long x;
int a[maxn],b[maxn],p[maxn],at[maxn];
int n,d;
long long getNextX()
{
	return x=(x*37+10007)%1000000007;
}
void init()
{
	for (int i=0;i<n;i++) a[i]=i+1;
	for (int i=0;i<n;i++) swap(a[i],a[getNextX()%(i+1)]);
	for (int i=0;i<n;i++) at[a[i]]=i;
	for (int i=0;i<n;i++) b[i]=(i<d);
	for (int i=0;i<n;i++) swap(b[i],b[getNextX()%(i+1)]);
	for (int i=0;i<n;i++) if (b[i]) p[++p[0]]=i;
}
int main()
{
	cin>>n>>d>>x;
	init();
	int s=30;
	for (int i=0;i<n;i++)
	{
		int j;
		for (j=n;j>=n-s;j--)
		{
			if (j>0 && i>=at[j] && b[i-at[j]])
			{
				printf("%d\n",j);
				break;
			}
		}
		if (j<n-s)
		{
			int mx=0;
			for (int j=1;j<=p[0] && p[j]<=i;j++)
				mx=max(mx,a[i-p[j]]);
			printf("%d\n",mx);
		}
	}
	return 0;
}
