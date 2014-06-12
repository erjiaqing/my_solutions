#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
int n,m;
int w[maxn],mj[maxn];
long long th[50],we[50],cn[50],wc;
long long tw=0;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&w[i]),tw+=w[i];
	for (int i=1;i<=m;i++) scanf("%d",&mj[i]);
	sort(&mj[1],&mj[m+1]);
	wc=1;th[1]=mj[1];cn[1]=1;
	for (int i=2;i<=m;i++)
	{
		if (mj[i]!=th[wc])
		{
			wc++;
			th[wc]=mj[i];
			cn[wc]=1;
		}else
		{
			cn[wc]++;
		}
	}
	th[wc+1]=1<<30;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=wc;j++)
			we[j]+=w[i]%th[j+1]/th[j];
	bool ok=false;
	int ans=0;
	we[wc+1]=1;
	for (int i=1;i<=wc && !ok;i++)
	{
		while (cn[i])
		{
			int j=i;
			while (we[j]==0) j++;
			if (j==wc+1) {ok=true;break;}
			we[j]--;ans++;cn[i]--;
			for (int k=i;k<j;k++)
			{
				we[k]=th[k+1]/th[k]-1;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
