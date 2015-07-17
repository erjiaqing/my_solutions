#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 5;
long long p[maxn];
set <long long> s;
int main()
{
	int n;
	long long m , ans = 0 , t;
	scanf("%d%lld" , &n , &m);
	s.insert(m);
	for (int i = 1 ; i <= n ; i++)
	{
		scanf("%lld" , &p[i]);
		( ( ( p[i] += p[i - 1] ) %= m ) += m ) %= m;
		t = *s.upper_bound(p[i]);
		ans = max(ans , p[i] - t + m);
		s.insert(p[i]);
	}
	printf("%lld\n" , ans);
	return 0;
}
