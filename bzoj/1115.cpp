#include <bits/stdc++.h>
using namespace std;
int u,n,a[1005],sg,p;
int main()
{
	ios::sync_with_stdio(0);
	cin>>u;
	while (u--)
	{
		sg=0,p=0;
		cin>>n;p=((n&1)^1);
		for (int i=1;i<=n;i++) (cin>>a[i]),sg^=(((i&1)^p)?(a[i]-a[i-1]):0);
		cout<<(sg?"TAK\n":"NIE\n");
	}
	return 0;
}
