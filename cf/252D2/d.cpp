#include <bits/stdc++.h>
using namespace std;
const int maxn=3005;
int v[maxn],p[maxn],po[maxn],n,m,k;
void set_vis(int u)
{
	for (;!v[u];u=p[u])
		v[u]=1;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&p[i]);
	scanf("%d",&m);
	for (int i=1;i<=n;i++) if (!v[i]) set_vis(i),k++;
	memset(v,0,sizeof(v));
	m=n-m;
	printf("%d\n",max(k-m,m-k));
	if (k>m)
	{
		set_vis(1);
		for (int i=2;i<=n && k>m;i++)
			if (!v[i])
			{
				printf("%d %d ",1,i);
				k--;
				set_vis(i);
			}
	}else if (k<m)
	{
		for (int i=1;i<=n && k<m;i++)
		{
			memset(po,-1,sizeof(po));
			int cur=0;
			for (int j=p[i];j!=i;j=p[j]) po[j]=cur++;
			po[i]=cur;
			cur=0;
			for (int j=i+1;j<=n && k<m;j++)
			{
				if (po[j]>=cur)
				{
					printf("%d %d ",i,j);
					k++;
					cur=po[j];
					swap(p[i],p[j]);
				}
			}
		}
	}
	printf("\n");
	return 0;
}
