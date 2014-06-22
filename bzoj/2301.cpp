#include <bits/stdc++.h>
using namespace std;
const int maxn=50005;
int u[maxn],f[maxn];//这里u->μ
int a,b,c,d,k;
void prep()
{
	memset(f,-1,sizeof(f));
	f[0]=f[1]=0;u[1]=1;
	for (int i=1;i<maxn;i++)
	{
		if (f[i])
		{
			u[i]=-1;
			for (int j=i+i;j<maxn;j+=i)
			{
				if (!((j/i)%i))
					u[j]=0;
				else
					u[j]=-u[j/i];
				f[j]=0;
			}
		}
	}
	for (int i=1;i<maxn;i++)
		u[i]+=u[i-1];
}
int calc(int n,int m)
{
	n/=k;m/=k;
	if (n>m)
		swap(n,m);
	int ans=0;
	for (int l=1;l<=n;)
	{
		int r=min(n/(n/l),m/(m/l));
		ans+=(u[r]-u[l-1])*(n/l)*(m/l);
		l=r+1;
	}
	return ans;
}
int main()
{
	int n;
	prep();
	scanf("%d",&n);
	while (~scanf("%d%d%d%d%d",&a,&b,&c,&d,&k))
		printf("%d\n",calc(b,d)-calc(a-1,d)-calc(c-1,b)+calc(a-1,c-1));
	return 0;
}
