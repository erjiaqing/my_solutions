#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxd=50005;
int f[maxd],u[maxd];
int n,a,b,c,d,ans;
int main()
{
	memset(f,-1,sizeof(f));
	f[0]=f[1]=false;
	u[1]=1;
	for (int i=2;i<=maxd;i++)
	{
		if (f[i])
		{
			u[i]=-1;
			for (int j=i+i;j<=maxd;j+=i)
			{
				f[j]=false;
				if (!((j/i)%i))
					u[j]=0;
				else
					u[j]=-u[j/i];
			}
		}
	}
	for (int i=1;i<maxd;i++)
		u[i]+=u[i-1];
	scanf("%d",&n);
	while (n--)
	{
		scanf("%d%d%d",&a,&b,&d);
		a/=d;b/=d;
		if (a>b)
			swap(a,b);
		ans=0;
		for (int i=1;i<=a;)
		{
			int pos=min(a/(a/i),b/(b/i));
			ans+=(u[pos]-u[i-1])*(a/i)*(b/i);
			i=pos+1;
		}
		printf("%d\n",ans);
	}
}
