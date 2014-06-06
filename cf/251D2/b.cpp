#include <bits/stdc++.h>
using namespace std;
typedef long long i64d;
const int maxn=100005;
int n,x,c[maxn];
long long a;
int main()
{
	scanf("%d%d",&n,&x);
	for (int i=0;i<n;i++) scanf("%d",&c[i]);
	sort(&c[0],&c[n]);
	for (int i=0;i<n;i++) a+=i64d(c[i])*x,x=max(1,x-1);
	printf("%lld\n",a);
	return 0;
}
