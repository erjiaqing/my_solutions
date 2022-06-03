#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
const int maxn=5005;
//int T[maxn*maxn];
#define x first
#define y second
typedef pair<short,short> pss;
pair<short,short> Pos[maxn*maxn];
int Num[maxn*maxn];
int Out[maxn+maxn];
bool Used[maxn*maxn];
//set<pair<pair<short,short>,int> > S;
//typedef set<pair<pair<short,short>,int> >::iterator sppssii;
long long a,b,c,d,x0;
int N,M,Q;
long long Rand()
{
	return x0=(a*x0*x0+b*x0+c)%d;
}
const int getPos(int x,int y)
{
	return ((x-1)*M+y);
}
void Fill(int x,int y)
{
	int tpos;
	for (int i=x+1;i<=N;i++)
		for (int j=y-1;j>0;j--)
		{
			if (Used[tpos=getPos(i,j)]) break;
			Used[tpos]=1;
		}
	for (int i=x-1;i>0;i--)
		for (int j=y+1;j<=M;j++)
		{
			if (Used[tpos=getPos(i,j)]) break;
			Used[tpos]=1;
		}
}
int main()
{
	freopen("random.in","r",stdin);
	freopen("random.out","w",stdout);
	scanf("%lld%lld%lld%lld%lld",&x0,&a,&b,&c,&d);
	scanf("%d%d%d",&N,&M,&Q);
	int num=0;
	for (int i=1;i<=N*M;i++) {Num[i]=i;swap(Num[i],Num[Rand()%i+1]);}
	int u,v;
	for (int i=1;i<=Q;i++)
	{
		scanf("%d%d",&u,&v);
		swap(Num[u],Num[v]);
	}
	for (int i=1;i<=N;i++)
		for (int j=1;j<=M;j++)
			Pos[Num[getPos(i,j)]]=pss(i,j);
	int tot=0;
	for (int i=1;i<=N*M;i++)
	{
		u=Pos[i].x;v=Pos[i].y;
		if (Used[getPos(u,v)])
			continue;
		Out[tot++]=i;
		Fill(u,v);
	}
	sort(&Out[0],&Out[tot]);
	for (int i=0;i<tot;i++)
		printf("%d%c",Out[i],(i==tot-1)?'\n':' ');
//	printf("\n");
	return 0;
}
