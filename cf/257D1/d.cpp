#include <bits/stdc++.h>
using namespace std;
const int maxk = 20,maxn = (1<<20),mod=1000000007;
int f[maxn],a[maxn],k2[maxn],n;
void prepare()
{
	int x0,y0,x1,y1;
	for (int i=0;i<n;i++)
		f[a[i]]++;
	for (int i=0;i<maxk;i++)
	for (int j=0;j<(1<<20);j++)
		if (!(j&(1<<i)))
			f[j]+=f[j|(1<<i)];
}
int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",a+i);
	prepare();
	int ans=0,tg=0;
	k2[0]=1;
	for (int i=1;i<maxn;i++) k2[i]=(2*k2[i-1])%mod;
	for (int i=0;i<maxn;i++)
	{
		tg=0;
		for (int j=0;j<20;j++) if (i&(1<<j)) tg++;
		if (f[i]) (ans+=(((tg&1)?(-1):(1))*(k2[f[i]]-1)))%=mod;
	}
	printf("%d\n",ans<0 ? ans + mod : ans);
	return 0;
}
