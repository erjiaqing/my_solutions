#include <bits/stdc++.h>
using namespace std;
const int maxn=50005*2;
#define lowbit(x) ((x)&(-(x)))
int bit[maxn],pos[maxn];
int n,t;
int sum(int x)
{
	int ret=0;
	for (;x>0;x-=lowbit(x)) ret+=bit[x];
	return ret;
}
void add(int x,int v)
{
	for (;x<maxn;x+=lowbit(x)) bit[x]+=v;
}
int main()
{
	int ans=0;
	scanf("%d",&n);
	n*=2;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		if (pos[t])
		{
			ans+=sum(i)-sum(pos[t]);
			add(pos[t],-1);
		}else
		{
			pos[t]=i;
			add(pos[t],1);
		}
	}
	printf("%d\n",ans);
	return 0;
}
