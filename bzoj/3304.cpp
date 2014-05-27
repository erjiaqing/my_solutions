#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=505;
int f[2][maxn][maxn];
char x[maxn],y[maxn],z[maxn];
int lx,ly,lz,s,ans;
int main()
{
	scanf("%s%s%s",x+1,y+1,z+1);
	lx=strlen(x+1);ly=strlen(y+1);lz=strlen(z+1);
	for (int i=1;i<=lx;i++)
	{
		for (int j=1;j<=ly;j++)
		{
			for (int k=0;k<=lz;k++)
			{
				f[s^1][j][k]=max(max(f[s][j][k],f[s^1][j-1][k]),f[s][j-1][k]);
				/**
				 * f[i][j][k]=max| f[i-1][j][k]
				 *               | f[i][j-1][k]
				 *               | f[i-1][j-1][k]
				 */
				if (x[i]==y[j])
				{
					if (f[s][j-1][k] || k==0)
						f[s^1][j][k]=max(f[s^1][j][k],f[s][j-1][k]+1);
						// f[i][j][k]=max(f[i-1][j-1][k]+1)
					if (x[i]==z[k] && (f[s][j-1][k-1] || (k-1)==0))
						f[s^1][j][k]=max(f[s^1][j][k],f[s][j-1][k-1]+1);
						// f[i][j][k]=max(f[i-1][j-1][k-1]+1)
				}
			}
			ans=max(ans,f[s^1][j][lz]);
		}
		s^=1;
	}
	if (ans-1>0)
		printf("%d\n",ans);
	else
		printf("NO SOLUTION\n");
	return 0;
}
