#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn=100005;
vector <int> e[maxn];
typedef vector<int>::iterator ii;
struct list{
	int p,n;
}l[maxn];
int n,m,s,Ans[maxn];
int lin[maxn],inq[maxn];
queue<int>Q;
void del(int x)
{
	l[l[x].p].n=l[x].n;
	l[l[x].n].p=l[x].p;
}
int main()
{
	int tu,tv;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&tu,&tv);
		e[tu].push_back(tv);
		e[tv].push_back(tu);
	}
	for (int i=1;i<=n;i++)
	{
		l[i-1].n=i;l[i].p=i-1;
	}
	l[n].n=0;
	while (l[0].n)
	{
		int now=l[0].n,ans=1;
		del(now);
		Q.push(now);
		inq[now]=1;
		while (!Q.empty())
		{
			int u=Q.front();Q.pop();
			for (ii i=e[u].begin();i!=e[u].end();i++)
				lin[*i]=1;
			for (int i=l[0].n;i;i=l[i].n)
			{
				if (!lin[i]&&!inq[i])
				{
					inq[i]=true;
					Q.push(i);
					ans++;
					del(i);
				}
			}
			for (ii i=e[u].begin();i!=e[u].end();i++)
				lin[*i]=0;
		}
		Ans[s++]=ans;
	}
	sort(&Ans[0],&Ans[s]);
	printf("%d\n",s);
	for(int i=0;i<s-1;i++)
		printf("%d ",Ans[i]);
	printf("%d\n",Ans[s-1]);
	return 0;
}
