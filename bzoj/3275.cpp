#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
const int maxn=3005;
struct edge{
	int s,t,n,v;
	edge(){}
	edge(int _s,int _t,int _n,int _v):
		s(_s),t(_t),n(_n),v(_v){}
}e[maxn*maxn+maxn*2];
int h[maxn],cur[maxn],path[maxn],path_n,te;
int numb[maxn],even[maxn],eid[maxn],odd[maxn],oid[maxn];
int ce,co;
int n,ans;
void addedge(int s,int t,int v)
{
	int e1=te++,e2=te++;
	e[e1]=edge(s,t,h[s],v);h[s]=e1;
	e[e2]=edge(t,s,h[t],0);h[t]=e2;
}
int gcd(int x,int y)
{
	if (!(x%y))
		return y;
	return gcd(y,x%y);
}
bool check(int x,int y)
{
	int c=sqrt(x*x+y*y);
	if (c*c==x*x+y*y)
		return true;
	else if (gcd(x,y)==1)
		return true;
	return false;
}
int lay[maxn],s=0,t;
bool build()
{
    int u;
    memset(lay,-1,sizeof(lay));
    queue <int>Q;
    Q.push(s);lay[s]=0;
    while (!Q.empty())
    {
        u=Q.front();Q.pop();
        for (int c=h[u];~c;c=e[c].n)
            if (e[c].v&&lay[e[c].t]==-1)
            {
                lay[e[c].t]=lay[u]+1;
                Q.push(e[c].t);
            }
    }
    return lay[t]!=-1;
}
int dinic()
{
    int ret=0;
    while (build())
    {
        int path_n=0;
        int x=s;
        memcpy(cur,h,sizeof(cur));
        while (1)
        {
            if (x==t)
            {
                int mink=-1,delta=233333333;
                for (int i=0;i<path_n;i++)
                {
                    if (e[path[i]].v<delta)
                    {
                        delta=e[path[i]].v;
                        mink=i;
                    }
                }
                for (int i=0;i<path_n;i++)
                {
                    e[path[i]].v-=delta;
                    e[path[i]^1].v+=delta;
                }
                ret+=delta;
                path_n=mink;
                x=e[path[path_n]].s;
            }
            int ep;
            for (ep=cur[x];~ep;ep=e[ep].n)
            {
                if (e[ep].v)
                {
                    int y=e[ep].t;
                    if (lay[y]==lay[x]+1)
                        break;
                }
            }
            cur[x]=ep;
            if (~ep)
            {
                path[path_n++]=ep;
                x=e[ep].t;
            }else
            {
                if (!path_n)
                    break;
                lay[x]=-1;
                --path_n;
                x=e[path[path_n]].s;
            }
        }
    }
    return ret;
}
int main()
{
	scanf("%d",&n);t=n+1;
	memset(h,-1,sizeof(h));
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&numb[i]);
		ans+=numb[i];
		if (numb[i]%2==1)
		{
			odd[++co]=numb[i];
			oid[co]=i;
			addedge(0,i,numb[i]);
		}else
		{
			even[++ce]=numb[i];
			eid[ce]=i;
			addedge(i,n+1,numb[i]);
		}
	}
	for (int i=1;i<=co;i++)
		for (int j=1;j<=ce;j++)
			if (check(odd[i],even[j]))
				addedge(oid[i],eid[j],233333333);
	printf("%d\n",ans-dinic());
	return 0;
}
