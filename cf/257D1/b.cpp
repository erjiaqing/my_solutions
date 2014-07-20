#include <bits/stdc++.h>
using namespace std;
const int maxn=200005,maxm=400005;
struct edge{
	int v;
	long long c;
	int f;
	edge(){}
	edge(const int &_v,const long long &_c,const int &_f):
		v(_v),c(_c),f(_f){}
};
int n,m,k;
long long myi[maxn];
vector<edge> e[maxn];
typedef vector<edge>::iterator vei;
void addedge(int u,int v,long long c,int f)
{
	e[u].push_back(edge(v,c,f));
	e[v].push_back(edge(u,c,f));
}
queue<int> Q;
long long dis[maxn];
int inq[maxn],mcnt[maxn];
void spfa()
{
	int u,ev,vv;
	Q.push(1);
	while (!Q.empty())
	{
		u=Q.front();Q.pop();inq[u]=0;
//		cerr<<u<<endl;
		for (vei ev=e[u].begin();ev!=e[u].end();ev++)
		{
			vv=ev->v;
//			cerr<<" "<<vv;
			if (dis[u]+ev->c<dis[vv])
			{
				dis[vv]=dis[u]+ev->c;
				if (!inq[vv])
				{
					inq[vv]=1;
					Q.push(vv);
				}
			}
		}
//		cerr<<endl;
	}
}
int main()
{
//	memset(h,-1,sizeof(h));
	memset(myi,0x3f,sizeof(myi));
	scanf("%d%d%d",&n,&m,&k);
	int tu,tv;
	long long tc;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&tu,&tv,&tc);
		addedge(tu,tv,tc,0);
	}
	for (int i=1;i<=k;i++)
	{
		scanf("%d%lld",&tv,&tc);
		mcnt[tv]++;
		addedge(1,tv,tc,1);
	}
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	spfa();
	int ans=0;
	long long ty;
	for (int i=2;i<=n;i++)
	{
		bool flag=false;
		for (vei j=e[i].begin();j!=e[i].end();j++)
		{
			int v=j->v;
			if (!j->f)
			{
				if (dis[v]+j->c==dis[i])
				{
					flag=true;
					break;
				}
			}
		}
		if (flag)
			ans+=mcnt[i];
		else
			ans+=mcnt[i]-1;
	}
	printf("%d\n",ans);
	return 0;
}
