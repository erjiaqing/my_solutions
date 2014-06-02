#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
//typedef long long lld;
int Set[maxn];
long long Size[maxn];
bool Sel[maxn];
int Find(int u)
{
	return (u==Set[u])?(u):(Set[u]=Find(Set[u]));
}
void Union(int u,int v)
{
	int fu=Find(u),fv=Find(v);
	Size[fv]+=Size[fu];
	Set[fu]=fv;
}
double Tot=0;
vector <int> e[maxn];
vector <pair<long long,int> > node;
long long a[maxn];
long long n;
int m;
int main()
{
	int u,v;
	scanf("%lld%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for (int i=1;i<=n;i++)
		Set[i]=i,Size[i]=1;
	for (int i=1;i<=n;i++)
		node.push_back(make_pair(a[i],i));
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	sort(node.begin(),node.end(),greater<pair<int,int> >());
	for (int i=0;i<n;i++)
	{
		int fa,fb;
		Sel[node[i].second]=true;
		for (vector<int>::iterator vi=e[node[i].second].begin();vi!=e[node[i].second].end();vi++)
		{
			if (Sel[*vi])
			{
				fb=Find(*vi);fa=Find(node[i].second);
				if (fb!=fa)
				{
					Tot+=node[i].first*Size[fa]*Size[fb];
					Union(fb,fa);
				}
			}
		}
	}
	Tot/=(n)*(n-1)/2;
	printf("%.6lf\n",Tot);
	return 0;
}
