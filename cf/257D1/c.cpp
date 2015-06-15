#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
int n,np[maxn],p[maxn],tp;
int match[maxn],unmatch[maxn],li[maxn],cli,used[maxn];
int prep()
{
	for (int i=2;i<(maxn+1) / 2;i++)
		if (!np[i])
			for (int j=i+(p[tp++]=i);j<=(maxn+1)/2;j+=i)
				np[j]=1;
}
int main()
{
	prep();
	scanf("%d",&n);
	match[1]=-1;for (int i=(n+1)/2+1;i<maxn;i++) if(np[i]==0) match[i]=-1;
	for (int i=tp-1;i>=0;i--)
	{
		cli=0;
		if (p[i]>n) continue;
		for (int j=p[i];j<=n;j+=p[i])
			if (used[j]==0)
				li[cli++] = j;
		if (cli==1) continue;
		if (cli&1)
		{
			for (int j=1;j<cli;j++) li[j]=li[j+1];
			cli--;
		}
		for (int j=0;j<cli-1;j+=2)
			match[li[j]]=li[j+1],match[li[j+1]]=-1,used[li[j]]=used[li[j+1]]=1;
	}
	int ans=0;
	for (int i = 1;i <= n ; i++)
		if ( match [ i ] > 0 )
			ans += 1;
	printf("%d\n",ans);
	for (int i=1;i<=n;i++)
		if (match[i]>0)
			printf("%d %d\n",i,match[i]);
	return 0;
}
