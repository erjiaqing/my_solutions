#include <bits/stdc++.h>
using namespace std;

typedef long long i64d;

const int maxs=405,mve=9;
long double dp[2][(1<<mve)][2][maxs];
i64d x,a,k,t,nw,nx,mask;
long double p;
int main()
{
	mask=(1<<mve)-1;
	cin>>x>>k>>p;p/=100;
	t=x;
	long long xm=x&i64d(mask),
		xl=(x&(1<<(i64d(mve))))>0,
		xc=0;
	x>>=mve;
	if (x==0)
		xc=200;
	else
	{
		while (1)
		{
			int b=x&1;
			if (b==xl)
				xc++;
			else
				break;
			x>>=1;
		}
	}
	dp[0][xm][xl][xc]=1;
	for (int i=0;i<k;i++)
	{
		nw=i&1;nx=nw^1;
		memset(dp[nx],0,sizeof(dp[nx]));
		for (int m=0;m<(1<<mve);m++)
		{
			for (int l=0;l<2;l++)
			{
				for (int s=0;s<maxs;s++)
				{
					long double tp=dp[nw][m][l][s];
					int nm=(m<<1)&mask;
					int nl=(m&(1<<(mve-1)))>0;
					int ns=s;
					if (l==nl) ns++;
					else ns=1;
					dp[nx][nm][nl][ns]+=tp*p;
					//--
					nm=m+1;
					if (nm!=(1<<mve))
						dp[nx][nm][l][s]+=tp*(1-p);
					else
						if (l==1)
							dp[nx][0][0][s]+=tp*(1-p);
						else
							dp[nx][0][1][1]+=tp*(1-p);
				}
			}
		}
	}
	nw=k&1;
	double ans=0;
	for (int m=0;m<(1<<mve);m++)
	{
		for (int l=0;l<2;l++)
		{
			for (int s=0;s<maxs;s++)
			{
				int cs=0;
				int ms=m;
				if (m)
					while (~ms&1)
						cs++,ms>>=1;
				else
				{
					cs=mve;
					if (l==0)
						cs+=s;
				}
				ans+=cs*dp[nw][m][l][s];
			}
		}
	}
	printf("%.16lf\n",ans);
	return 0;
}
