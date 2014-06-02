#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,k,t;
int main()
{
	scanf("%d%d",&n,&k);
	if (k<n/2){printf("-1\n");return 0;}
	if (n==1 && k>0){printf("-1\n");return 0;}else if (n==1){printf("%d\n",3123341);return 0;}
	t=k-(n-2)/2;
	printf("%d %d",t,t*2);
	for (int i=3;i<=n;i++)
		printf(" %d",300000000+i);
	printf("\n");
	return 0;
}
