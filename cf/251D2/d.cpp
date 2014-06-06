#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
long long arra[maxn],arrb[maxn],ans;
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&arra[i]);
	for (int i=1;i<=m;i++) scanf("%lld",&arrb[i]);
	sort(&arra[1],&arra[n+1]);
	sort(&arrb[1],&arrb[m+1],greater<long long>());
	n=min(n,m);
	for (int i=1;i<=n && (arra[i]<arrb[i]);i++)
		ans+=arrb[i]-arra[i];
	printf("%lld\n",ans);
	return 0;
}
// A beautiful solution , wow!
