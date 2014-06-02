#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=100005;
int a[maxn],pos[maxn];
int p[maxn],tp;
bool ifp[maxn];
int n;
vector<pair<int,int> >o;
void eswap(int s,int t)
{
	swap(pos[a[s]],pos[a[t]]);
	swap(a[s],a[t]);
}
int main()
{
	memset(ifp,-1,sizeof(ifp));
	ifp[0]=ifp[1]=0;
	for (int i=2;i<maxn;i++)
		if (ifp[i])
			for (int j=i+i;j<maxn;j+=i)
				ifp[j]=false;
	for (int i=2;i<maxn;i++)
		if (ifp[i])
			p[tp++]=i;
//	cerr<<tp<<endl;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]),pos[a[i]]=i;
	for (int i=1;i<=n;i++)
	{
//		cerr<<i<<endl;
		while (a[i]!=i)
		{
			int j=p[upper_bound(&p[0],&p[tp],pos[i]-i+1)-1-p];
			o.push_back(make_pair(pos[i]-j+1,pos[i]));
			int pa=pos[i],pb=pos[i]-j+1;
			eswap(pa,pb);
//			cerr<<i<<" "<<j<<endl;
		}
	}
	printf("%d\n",o.size());
	for (int i=0;i<o.size();i++)
		printf("%d %d\n",o[i].first,o[i].second);
	return 0;
}
