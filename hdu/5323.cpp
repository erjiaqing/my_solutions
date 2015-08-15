#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
long long ans = 0x3f3f3f3f3f3f3f3fll;
void dfs(long long a , long long b)
{
	//long long tans = 0;
	//printf(" > %lld %lld <\n" , a , b);
	if (b < a)
		return;
	if (a < 0)
		return;
	if (a == 0)
	{
	 	ans = min(ans , b);
		return;
	}
	long long len = b - a + 1;
	if (a < len) return;
	dfs(a - len , b);
	dfs(a - len - 1 , b);
	dfs(a , b + len);
	if (b != a)
		dfs(a , b + len - 1);
}
int main()
{
	long long a , b;
	while (~scanf("%lld%lld" , &a , &b))
	{
		ans = 0x3f3f3f3f3f3f3f3fll;
		dfs(a , b);
		printf("%lld\n" , ans == 0x3f3f3f3f3f3f3f3fll ? -1ll : ans);
	}
	return 0;
}

