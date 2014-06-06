#include <bits/stdc++.h>
using namespace std;
int n,tt,t,d;
int main()
{
	scanf("%d%d",&n,&d);
	for (int i=1;i<=n;i++) scanf("%d",&t),tt+=t;
	d-=(n-1)*10+tt;
	if (d<0) printf("-1\n");
	else printf("%d\n",(d/5+(n-1)*2));
	return 0;
}
