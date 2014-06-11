#include <bits/stdc++.h>
using namespace std;
const int maxn=55;
int Ma[maxn][maxn],Mb[maxn][maxn],Ha[maxn][maxn],Hb[maxn][maxn];
int n;
bool check(int s)
{
	int sa,sb;
	for (int a=0;a<=n-s;a++)
	{
		for (int b=0;b<=n-s;b++)
		{
			sa=Ha[a+s][b+s]^Ha[a][b+s]^Ha[a+s][b]^Ha[a][b];
			for (int c=0;c<=n-s;c++)
			{
				for (int d=0;d<=n-s;d++)
				{
					sb=Hb[c+s][d+s]^Hb[c+s][d]^Hb[c][d+s]^Hb[c][d];
					if (sa==sb)
					{
						bool ok=true;
						for (int i=1;i<=s;i++)
						{
							for (int j=1;j<=s;j++)
							{
								ok&=(Ma[a+i][b+j]==Mb[c+i][d+j]);
								if (!ok)
									break;
							}
							if (!ok)
								break;
						}
						if (ok)
							return true;
					}
				}
			}
		}
	}
	return false;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&Ma[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&Mb[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			Ha[i][j]=Ha[i-1][j]^Ha[i][j-1]^Ha[i-1][j-1]^Ma[i][j],
			Hb[i][j]=Hb[i-1][j]^Hb[i][j-1]^Hb[i-1][j-1]^Mb[i][j];
	int l=1,r=n+1,m;
	while (l<r-1)
	{
		m=(l+r)/2;
		if (check(m))
			l=m;
		else
			r=m;
	}
	printf("%d\n",l);
	return 0;
}
