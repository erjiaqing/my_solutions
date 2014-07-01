#include <bits/stdc++.h>
using namespace std;
const int maxn=55;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
typedef vpii::iterator vpiii;
vpii e[maxn];
int n,a,b;
int edg[maxn][maxn];
char s[maxn];
int d1[maxn],d2[maxn],inq[maxn],d[maxn][maxn];
queue<int> Q;
int Br;
void spfa(int s)
{
	memset(inq,0,sizeof(inq));
	memset(d[s],0x7f,sizeof(d[s]));Br=d[s][s];
	Q.push(s);d[s][s]=0;inq[s]=1;
	while (!Q.empty())
	{
		int u=Q.front();Q.pop();inq[u]=0;
		for (vpiii v=e[u].begin();v!=e[u].end();v++)
		{
			if (d[s][v->first]>d[s][u]+v->second)
			{
				d[s][v->first]=d[s][u]+v->second;
				if (!inq[v->first]) inq[v->first]=1,Q.push(v->first);
			}
		}
	}
}
void spfa1()
{
	memset(inq,0,sizeof(inq));
	memset(d1,0xac,sizeof(d1));
	Q.push(0);d1[0]=1;inq[0]=1;
	while (!Q.empty())
	{
		int u=Q.front();Q.pop();inq[u]=0;
		for (vpiii v=e[u].begin();v!=e[u].end();v++)
		{
			if (d1[v->first]<d1[u]+v->second)
			{
				d1[v->first]=d1[u]+v->second;
				if (!inq[v->first]) inq[v->first]=1,Q.push(v->first);
			}
		}
	}
}
void spfa2()
{
	memset(inq,0,sizeof(inq));
	memset(d2,0x7f,sizeof(d2));
	Q.push(0);d2[0]=3;inq[0]=1;
	while (!Q.empty())
	{
		int u=Q.front();Q.pop();inq[u]=0;
		for (vpiii v=e[u].begin();v!=e[u].end();v++)
		{
			if (d2[v->first]>d2[u]+v->second)
			{
				d2[v->first]=d2[u]+v->second;
				if (!inq[v->first]) inq[v->first]=1,Q.push(v->first);
			}
		}
	}
}
/*********************************************************************/
int sgn(int a,int b)
{
	return (d[a][b])?(d[a][b]>0)?1:-1:0;
}
bool chk(int I,int J,int di,int dj)
{
	if (d[I][J]!=Br)
		if ((di >  dj && d[I][J]>=0)||
			(di == dj && d[I][J]!=0)||
			(di  < dj && d[I][J]<=0)) return false;
	return true;
}
bool chk(int A,int B,int i,int j,int da,int db,int di,int dj)
{
	if (!chk(A,B,da,db)) return false;
	if (!chk(A,i,da,di)) return false;
	if (!chk(A,j,da,dj)) return false;
	if (!chk(B,i,db,di)) return false;
	if (!chk(B,j,db,dj)) return false;
	if (!chk(i,j,di,dj)) return false;
	return true;
}
int cmp(int A,int B,int i,int j)
{
	int c1=0,c2=0,c3=0;
	for (int I=d1[A];I<=d2[A];I++)
	for (int J=d1[B];J<=d2[B];J++)
	for (int K=d1[i];K<=d2[i];K++)
	for (int L=d1[j];L<=d2[j];L++)
		if (chk(A,B,i,j,I,J,K,L))
		{
			if (I+J> K+L) c1++;
			if (I+J==K+L) c2++;
			if (I+J <K+L) c3++;
		}
	if (c1  && !c2 && !c3) return 1;
	if (!c1 &&  c2 && !c3) return 0;
	if (!c1 && !c2 &&  c3) return -1;
	return 233;
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for (int j=1;j<=n;j++)
		{
			if (s[j]=='+') edg[i][j]=1;
			else if (s[j]=='-') edg[i][j]=2;
			else if (s[j]=='=') edg[i][j]=3;
		}
	}
	for (int i=1;i<=n;i++)
		e[0].push_back(pii(i,0));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (edg[i][j]==1) e[j].push_back(pii(i,1));
			else if (edg[i][j]==2) e[i].push_back(pii(j,1));
			else if (edg[i][j]==3) e[i].push_back(pii(j,0)),e[j].push_back(pii(i,0));
		}
	spfa1();
	for (int i=1;i<=n;i++) spfa(i);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (d[i][j]!=Br && i!=j)
				d[j][i]=-d[i][j];
	for (int i=1;i<=n;i++) e[i].clear();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (edg[i][j]==1) e[i].push_back(pii(j,-1));
			if (edg[i][j]==2) e[j].push_back(pii(i,-1));
			if (edg[i][j]==3) e[i].push_back(pii(j,0)),e[j].push_back(pii(i,0));
		}
	spfa2();
//	for (int i=1;i<=n;i++) printf("%d %d\n",d1[i],d2[i]);
	int c1=0,c2=0,c3=0;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
		{
			if (i==a || i==b || j==a || j==b) continue;
			int opt=cmp(a,b,i,j);
			if (opt==1) c1++;
			if (opt==0) c2++;
			if (opt==-1) c3++;
		}
	printf("%d %d %d\n",c1,c2,c3);
	return 0;
}
