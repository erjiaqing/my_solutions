#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
	int n,p,k,beg,end;
	scanf("%d%d%d",&n,&p,&k);
	beg=max(1,p-k);
	end=min(n,p+k);
	if (beg>1)
		printf("<< ");
	for (int i=beg;i<p;i++)
		printf("%d ",i);
	printf("(%d) ",p);
	for (int i=p+1;i<=end;i++)
		printf("%d ",i);
	if (end<n)
		printf(">>\n");
	return 0;
}
