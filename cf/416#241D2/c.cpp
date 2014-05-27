#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
const int maxn=1005;
pair<int,int> c[maxn];
int sz[maxn];
int t[maxn];
set<pair<int,int> > s;
set<pair<int,int> >::iterator si;
int n,k;
int main()
{
	int tc,tp;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&tc,&tp);
		c[i]=make_pair(tp,i);
		sz[i]=tc;
	}
	sort(&c[1],&c[n+1],greater<pair<int,int> >());
	scanf("%d",&k);
	for (int i=1;i<=k;i++)
		scanf("%d",&t[i]),s.insert(make_pair(t[i],i));
	memset(t,0,sizeof(t));
	int ans1=0,ans2=0;
	for (int i=1;i<=n;i++)
	{
		si=s.lower_bound(make_pair(sz[c[i].second],0));
		if (si!=s.end())
		{
			t[c[i].second]=si->second;
			ans1++;ans2+=c[i].first;
			s.erase(si);
		}
	}
	printf("%d %d\n",ans1,ans2);
	for (int i=1;i<=n;i++)
		if (t[i])
			printf("%d %d\n",i,t[i]);
	return 0;
}
