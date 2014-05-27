#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
	long long m;
	cin>>m;
	int ans=0;
	while (m)
	{
		m>>=1;
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
