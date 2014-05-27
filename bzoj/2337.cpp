#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

#define v first
#define c second

using namespace std;
const int maxn=105;
//-- 浮点数运算
const double eps=1e-8;
bool _l (double a,double b){return a<b-eps;}
bool _g (double a,double b){return b<a-eps;}
bool _le(double a,double b){return a<b+eps;}
bool _ge(double a,double b){return b<a+eps;}
bool _eq(double a,double b){return fabs(a-b)<eps;}
double g[maxn][maxn],ans[maxn],fians;
int d[maxn];
int n,m,u,v,c;
typedef pair<int,int> pii;
typedef vector<pii>::iterator piii;
vector<pii> e[maxn];
void gauss()
{
	int p;
	for (int i=1;i<=n;i++)
	{
		p=0;
		for (int j=i;j<=n;j++)
			if (!_eq(g[j][i],0))
			{
				p=j;
				break;
			}
		if (!p)
			continue;
		for (int j=1;j<=n+1;j++)
			swap(g[i][j],g[p][j]);
		for (int j=i+1;j<=n;j++)
		{
			double x=g[j][i]/g[i][i];
			for (int k=1;k<=n+1;k++)
				g[j][k]-=x*g[i][k];
		}
	}
	for (int i=n;i>=1;i--)
	{
		ans[i]=g[i][n+1];
		for (int j=i+1;j<=n;j++)
			ans[i]-=ans[j]*g[i][j];
		ans[i]/=g[i][i];
//		printf("ans[%d]=%.3lf\n",i,ans[i]);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&c);
		d[u]++;
		e[u].push_back(pii(v,c));
		if (u!=v)
		{
			d[v]++;
			e[v].push_back(pii(u,c));
		}
	}
	for (int i=1;i<=(1<<29);i<<=1)
	{
		memset(g,0,sizeof(g));
		double tmp;
		for (int u=1;u<=n;u++)
		{
			tmp=0;g[u][u]=1;
			for (piii v=e[u].begin();v!=e[u].end();v++)
			{
				if ((v->c)&i)
				{
					tmp+=1.0/d[u];
					g[u][v->v]+=1.0/d[u];
				}else
				{
					g[u][v->v]-=1.0/d[u];
				}
			}
			g[u][n+1]=tmp;
		}
		for (int j=1;j<=n+1;j++)
			g[n][j]=0;
		g[n][n]=1;
		gauss();
		fians+=ans[1]*i;
	}
	printf("%.3lf\n",fians);
	return 0;
}
