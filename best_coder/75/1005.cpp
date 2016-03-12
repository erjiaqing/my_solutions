#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;
const int MAXN=450,MAXM=5005;
//--Graph
const int S=420,T=421,S0=422,S1=423,S2=424,INF=99999999;
struct Edge{int t,v,c,op,next;}E[MAXM];
int pFirst[MAXN],totE;
int Dis[MAXN],Pre[MAXN],NEd[MAXN];
bool inQ[MAXN];
int an[MAXN];
//--Problem
void clear(){
	memset(pFirst, 0, sizeof(pFirst));
	totE = 0;
}
void AddEdge(int s,int t,int v,int c)
{
    int E1=++totE,E2=++totE;
	//cerr << s << "-- " << c << " ( " << v << " ) " << " --> " << t << endl;
    E[E1].t=t;E[E1].v=v;E[E1].c= c;E[E1].op=E2;E[E1].next=pFirst[s];
    pFirst[s]=E1;
    E[E2].t=s;E[E2].v=0;E[E2].c=-c;E[E2].op=E1;E[E2].next=pFirst[t];
    pFirst[t]=E2;
}
inline int X(int i)
{
    return i*2-1;
}
inline int Y(int i)
{
    return i*2;
}
bool Spfa()
{
    memset(Dis,0x3f,sizeof(Dis));
    memset(Pre,-1,sizeof(Pre));
    memset(NEd,-1,sizeof(NEd));
    memset(inQ,0,sizeof(inQ));
    queue <int> Q;
    Q.push(S);
    Dis[S]=0;
    int u,v;
    while (!Q.empty())
    {
        u=Q.front();Q.pop();
        inQ[u]=false;
        for (int p=pFirst[u];p;p=E[p].next)
        {
            v=E[p].t;
            if (E[p].v>0)
                if (Dis[v]>Dis[u]+E[p].c)
                {
                    Dis[v]=Dis[u]+E[p].c;
                    Pre[v]=u;NEd[v]=p;
                    if (!inQ[v])
                    {
                        inQ[v]=true;
                        Q.push(v);
                    }
                }
        }
    }
    return (Pre[T]!=-1);
}
pair<int, int> MinCostMaxFlow()
{
    int u;
    int Cost=0,tmpflow, totflow = 0;
    while (Spfa())
    {
        tmpflow=INF;
        for (u=T;Pre[u]!=-1;u=Pre[u])
            tmpflow=min(tmpflow,E[NEd[u]].v);
		totflow += tmpflow;
        for (u=T;Pre[u]!=-1;u=Pre[u])
        {
            E[NEd[u]].v-=tmpflow;
            E[E[NEd[u]].op].v+=tmpflow;
            Cost+=tmpflow*E[NEd[u]].c;
        }
    }
    return make_pair(Cost, totflow);
}
int main()
{
    int tmp;
	int TT;
	scanf("%d", &TT);
	while (TT--) {
		int n, k, m, p, q, tot = 0;
		clear();
		//cerr << "XD";
		scanf("%d%d",&n,&k);
		//cerr << " " << n << " " << k << ";\n";
		AddEdge(S, S0, k, 0);
		for (int i=1;i<=n;i++)
			scanf("%d",&an[i]), tot += an[i];
		scanf("%d%d%d", &m, &p, &q);
		AddEdge(S, S1, INF, q);
		AddEdge(S0, S1, INF, 0);
		for (int i = 1; i < min(p, n + 1); i++)
		{
			tmp = an[i];
		    AddEdge(S0,X(i),tmp,0);
		    AddEdge(X(i),T,tmp,0);
			AddEdge(S,Y(i),tmp,0);
	        if (i<n)
		        AddEdge(Y(i),Y(i+1),INF,0);
		}
		for (int i = p; i <= n; i++)
		{
			tmp = an[i];
			AddEdge(S1, X(i), tmp, 0);
			AddEdge(X(i),T,tmp,0);
			AddEdge(S, Y(i), tmp, 0);
			if (i < n)
				AddEdge(Y(i), Y(i + 1), INF, 0);
		}
		for (int i = 0; i < m; i++) {
			int _s, _t;
			scanf("%d%d", &_s, &_t);
			for (int j = 1; j <= n; j++)
				if (j + _t <= n) AddEdge(Y(j), X(j + _t), INF, _s);
		}
		pair<int, int> res = MinCostMaxFlow();
		if (res.second < tot)
			printf("No solution\n");
		else
			printf("%d\n",res.first);
	}
    return 0;
}
