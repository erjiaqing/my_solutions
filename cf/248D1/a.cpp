#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
vector <int > ch[maxn];
vector <int >::iterator vii;
long long decr[maxn];
long long ans=0,tans=0,ttans=0;
int a[maxn];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	for (int i=2;i<=m;i++)
		ans+=abs(a[i]-a[i-1]);
	ttans=ans;
	a[0]=a[1];a[m+1]=a[m];
//	for (int i=1;i<=m;i++)
//		decr[a[i]]+=(abs(a[i]-a[i-1])+abs(a[i+1]-a[i]));
	for (int i=1;i<=m;i++)
	{
		//		if (a[i]<=a[i-1] && a[i]<=a[i+1])
//		{
		if (a[i]!=a[i-1])
			ch[a[i]].push_back(a[i-1]);
		if (a[i]!=a[i+1])
			ch[a[i]].push_back(a[i+1]);
		decr[a[i]]+=(abs(a[i]-a[i-1])+abs(a[i+1]-a[i]));
//		}
//		else if (a[i]>=a[i-1] && a[i]>=a[i+1])
//		{
//			if (a[i]!=a[i-1])
//			ch[a[i]].push_back(a[i-1]);
//			if (a[i]!=a[i+1])
//			ch[a[i]].push_back(a[i+1]);
//			decr[a[i]]+=(abs(a[i]-a[i-1])+abs(a[i+1]-a[i]));
//		}
	}
	for (int i=1;i<=n;i++)
		sort(ch[i].begin(),ch[i].end());
	int t1,t2;
	for (int i=1;i<=n;i++)
	{
		t1=0;t2=0x3f3f3f3f;
		int decc=ch[i].size()/2;
		for (int j=0;j<ch[i].size();j++)
			t1+=abs(ch[i][decc]-ch[i][j]);
		decc++;
		if (decc<ch[i].size())
		{
			t2=0;
			for (int j=0;j<ch[i].size();j++)
				t2+=abs(ch[i][decc]-ch[i][j]);
		}
//		printf("%d %d %d %d\n",i,decr[i],t1,t2);
		decr[i]-=min(t1,t2);
		ans=min(ans,ttans-decr[i]);
	}
//	int v1,v2;
//	for (int i=1;i<=n;i++)
//		for (vii=ch[i].begin();vii!=ch[i].end();vii++)
//		{
//			tans=0;
//			v1=(a[1]==i)?*vii:a[1];
//			for (int j=2;j<=m;j++)
//			{
//				v2=(a[j]==i)?*vii:a[j];
//				tans+=abs(v2-v1);
//				v1=v2;
//			}
//			cerr<<i<<" "<<*vii<<" "<<tans<<endl;
//			ans=min(ans,tans);
	printf("%lld\n",ans);
	return 0;
}
