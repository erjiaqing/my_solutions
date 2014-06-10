#include <bits/stdc++.h>
using namespace std;
const int maxn=3005;
//pair<int,int> f[maxn];
//#define a first
//#define b second
int f[maxn];
int ans=0,n,v;
int la,th;
int a,b;
int main()
{
	scanf("%d%d",&n,&v);
	for (int i=0;i<n;i++)
		scanf("%d%d",&a,&b),f[a]+=b;
	//sort(&f[0],&f[n]);
	for (int i=1;i<=3001;i++)
	{
		if (f[i-1]+f[i]<v)
		{
			ans+=f[i-1]+f[i];
			f[i]=0;
		}else
		{
			ans+=v;
			if (f[i-1]<v)
				f[i]-=v-f[i-1];
		}
	}
	printf("%d\n",ans);
	return 0;
}
