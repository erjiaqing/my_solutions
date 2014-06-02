#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <utility>
using namespace std;
const int maxn=305;
set<pair<int,int> > S;
typedef set<pair<int,int> > :: iterator spiii;
int L[maxn][maxn],U[maxn][maxn],R[maxn][maxn],D[maxn][maxn],M[maxn][maxn];
int n,m,t,tp,tu,td;
int main()
{
	scanf("%d%d%d%d%d%d",&n,&m,&t,&tp,&tu,&td);
	int x0,y0,x1,y1,ans=0x7fffffff,val1,val2;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&M[i][j]);
			if (M[i][j]==M[i][j-1])
				L[i][j]=L[i][j-1]+tp,R[i][j]=R[i][j-1]+tp;
			else if (M[i][j]<M[i][j-1])
				L[i][j]=L[i][j-1]+td,R[i][j]=R[i][j-1]+tu;
			else if (M[i][j]>M[i][j-1])
				L[i][j]=L[i][j-1]+tu,R[i][j]=R[i][j-1]+td;
			//=.= 0.0 -.- ←_← →_→QwQ OAO OvO
			if (M[i][j]==M[i-1][j])
				U[i][j]=U[i-1][j]+tp,D[i][j]=D[i-1][j]+tp;
			else if (M[i][j]<M[i-1][j])
				U[i][j]=U[i-1][j]+td,D[i][j]=D[i-1][j]+tu;
			else if (M[i][j]>M[i-1][j])
				U[i][j]=U[i-1][j]+tu,D[i][j]=D[i-1][j]+td;
		}
	}
	spiii tans;
	pair<int,int> last;
	for (int i=1;i<=n;i++)
		for (int j=i+2;j<=n;j++)
		{
			for (int k=1;k<=m;k++)
			{
				if (k>=3)
				{
					val1=U[j][k]-U[i][k]+L[i][k]+R[j][k];
					tans=S.lower_bound(make_pair(t-(U[j][k]-U[i][k]+L[i][k]+R[j][k]),k));
					if (tans!=S.end())
					{
						if (abs(val1+tans->first-t)<abs(ans-t))
						{
							ans=val1+tans->first;
							x0=i,x1=j,y0=tans->second,y1=k;
						}
					}
					if (tans!=S.begin())
					{
						tans--;
						if (abs(val1+tans->first-t)<abs(ans-t))
						{
							ans=val1+tans->first;
							x0=i,x1=j,y0=tans->second,y1=k;
						}
					}
				}
				if (k>1)
					S.insert(last);
				last=make_pair(D[j][k]-D[i][k]-L[i][k]-R[j][k],k);
			}
			S.clear();
		}
	printf("%d %d %d %d\n",x0,y0,x1,y1);
/*	for (int i=1;i<=n;i++,printf("\n"))
		for (int j=1;j<=m;j++)
			printf("%d\t",L[i][j]);
			printf("\n");
	for (int i=1;i<=n;i++,printf("\n"))
		for (int j=1;j<=m;j++)
			printf("%d\t",R[i][j]);
			printf("\n");
	for (int i=1;i<=n;i++,printf("\n"))
		for (int j=1;j<=m;j++)
			printf("%d\t",U[i][j]);
			printf("\n");
	for (int i=1;i<=n;i++,printf("\n"))
		for (int j=1;j<=m;j++)
			printf("%d\t",D[i][j]);
	int a,b,c,d;
	while (~scanf("%d%d%d%d",&a,&b,&c,&d))
	{
		printf("%d\n",L[a][d]-L[a][b]+U[c][d]-U[a][d]+R[c][d]-R[c][b]+D[c][b]-D[a][b]);
	}*/
	return 0;
}
