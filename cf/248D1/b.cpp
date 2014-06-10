#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int Lf[maxn],Rf[maxn];
void Init(int *Set,int n) {for (int i=0;i<=n+1;i++) Set[i]=i;}
int  Find(int *Set,int x) {return Set[x]==x?x:Set[x]=Find(Set,Set[x]);}
void Unio(int *Set,int u,int v) {Set[Find(Set,u)]=Find(Set,v);}
//--
int L[maxn][maxn],R[maxn][maxn],U[maxn][maxn],D[maxn][maxn];
int n,m,q,op,x,y,a[maxn][maxn],b[maxn],seq[maxn];
bool comp(int x,int y) {return b[x]<b[y];}
int calc(int n,int x)
{
	Init(seq,n);
	sort(&seq[1],&seq[n+1],comp);
	Init(Lf,n);Init(Rf,n);
	int ret=0;
	for (int i=n;i>=1;i--)
	{
		int l(Find(Lf,seq[i]-1)+1),r(Find(Rf,seq[i]+1)-1);
		if (l<=x && x<=r) ret=max(ret,(r-l+1)*b[seq[i]]);
		Unio(Lf,seq[i],seq[i]-1);Unio(Rf,seq[i],seq[i]+1);
	}
	return ret;
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	//--init
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			L[i][j]=((a[i][j])?(L[i][j-1]+1):0),
			U[i][j]=((a[i][j])?(U[i-1][j]+1):0);
	for (int i=n;i>=1;i--)
		for (int j=m;j>=1;j--)
			R[i][j]=((a[i][j])?(R[i][j+1]+1):0),
			D[i][j]=((a[i][j])?(D[i+1][j]+1):0);
	//--work
	while (q--)
	{
		scanf("%d%d%d",&op,&x,&y);
		if (op==1)
		{
			a[x][y]^=1;
			for (int i=x;i<=n;i++)
				U[i][y]=(a[i][y])?(U[i-1][y]+1):0;
			for (int i=x;i>=1;i--)
				D[i][y]=(a[i][y])?(D[i+1][y]+1):0;
			for (int j=y;j<=m;j++)
				L[x][j]=(a[x][j])?(L[x][j-1]+1):0;
			for (int j=y;j>=1;j--)
				R[x][j]=(a[x][j])?(R[x][j+1]+1):0;
		}else
		{
			int ans=0;
			for (int i=1;i<=m;i++) b[i]=U[x][i];
			ans=max(ans,calc(m,y));
			for (int i=1;i<=m;i++) b[i]=D[x][i];
			ans=max(ans,calc(m,y));
			for (int i=1;i<=n;i++) b[i]=L[i][y];
			ans=max(ans,calc(n,x));
			for (int i=1;i<=n;i++) b[i]=R[i][y];
			ans=max(ans,calc(n,x));
			printf("%d\n",ans);
		}
	}
	return 0;
}
