#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int k,a,b,v;
int main()
{
	scanf("%d%d%d%d",&k,&a,&b,&v);
	int put=0;
	for (int res=1;res<=1000;res++)
	{
		if (b>k-1)
		{
			put+=(k*v);
			b-=k-1;
		}
		else
		{
			put+=(b+1)*v;
			b-=b;
		}
		if (put>=a)
		{
			printf("%d\n",res);
			break;
		}
	}
	return 0;
}
