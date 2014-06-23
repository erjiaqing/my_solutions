#include <bits/stdc++.h>
using namespace std;
const int maxn=100005,maxsqrtn=333;
int tot,n,m,len[maxsqrtn],mid;
int blen,ans,o,sum,x,y,bsz[maxsqrtn];
double p[maxsqrtn][maxsqrtn],w[maxn];
int main()
{
	scanf("%d%d",&n,&m);
	blen=sqrt(n);
	sum=(n-1)/blen+1;
	for (int i=1;i<sum;i++) len[i]=blen;
	len[sum]=n-(sum-1)*blen;
	while (m--)
	{
		scanf("%d%d",&x,&y);
		w[x]=1.0*y/x;
		int blk=(x-1)/blen+1;
		double wm=0;
		bsz[blk]=0;
		for (int j=(blk-1)*blen+1;j<=(blk-1)*blen+len[blk];j++)
			if (w[j]>wm)
				p[blk][++bsz[blk]]=wm=w[j];
		ans=bsz[1];
		wm=p[1][ans];
		for (int j=2;j<=sum;j++)
		{
			if (p[j][bsz[j]]>wm)
			{
				int l=1,r=bsz[j],tot=0;
				while (l<=r)
				{
					mid=(l+r)/2;
					if (p[j][mid]>wm) tot=mid,r=mid-1;
					else l=mid+1;
				}
				ans+=bsz[j]-tot+1;
				wm=p[j][bsz[j]];
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
