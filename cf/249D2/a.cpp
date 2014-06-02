#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,a=0,ai,ans=0,bus=0;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		if (ai<=bus)
		{
			bus-=ai;
		}else
		{
			bus=m-ai;
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
