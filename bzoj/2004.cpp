#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod=30031;
int N,K,P,x,y,t,zt[205],p[2005];
struct matrix{
	int a[205][205],w,h;
	matrix(){}
	matrix operator * (matrix b)
	{
		matrix ret;
		ret.w=b.w;ret.h=h;
		for (int i=1;i<=ret.h;i++)
			for (int j=1;j<=ret.w;j++)
			{
				int tmp=0;
				for (int k=1;k<=w;k++)
					(tmp+=a[i][k]*b.a[k][j])%=mod;
				ret.a[i][j]=tmp;
			}
		return ret;
	}
}g,ans;
void check(int z)
{
	int zk[12],s,zz=z;
	for (int i=1;i<=P;i++)
		zk[P-i+1]=z&1,z>>=1;
	s=0;
	for (int i=1;i<=P;i++)
	{
		s+=zk[i];
		if (s>K)
			return;
	}
	if (s!=K)
		return;
	zt[++t]=zz;
	p[zz]=t;
}
void make(int d)
{
	int z=(zt[d]<<1)&x;
	for (int i=1;i<=P;i++)
		if (!((z>>(i-1))&1)&&(z+(1<<(i-1)))>=y)
			g.a[d][p[z+(1<<(i-1))]]++;
}
int main()
{
	scanf("%d%d%d",&N,&K,&P);
	y=1<<(P-1);x=(1<<P)-1;
	for (int i=0;i<y;i++)
		check(y+i);
	g.h=g.w=t;
	for (int i=1;i<=t;i++)
		make(i);
	int b=p[((1<<K)-1)<<(P-K)];
	N-=K;ans.h=1;ans.w=t;ans.a[1][b]=1;
	while (N)
	{
		if (N&1)
			ans=ans*g;
		N>>=1;
		g=g*g;
	}
	printf("%d\n",ans.a[1][b]);
	return 0;
}

