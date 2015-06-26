#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
const int maxk = 1000 + 5;
long long c[maxk][maxk];
int ci,tc = 0;
int k;
long long ans = 1;
long long pow(long long a,int p)
{
	long long ret = 1 , tp = a;
	while (p)
	{
		if (p & 1)
			(ret *= tp) %= mod;
		(tp *= tp) %= mod;
		p >>= 1;
	}
	return ret;
}
int main()
{
	for ( int i = 0 ; i < maxk ; i++ ) c[0][i] = 1;
	for ( int i = 1 ; i < maxk ; i++ )
		for ( int j = 1 ; j < maxk ; j++ )
			c[i][j] = (c[i - 1][j] + c[i][j - 1]) % mod;
	scanf( "%d" , &k );
	for ( int i = 0 ; i < k ; i++ )
	{
		scanf( "%d" , &ci );
		ans = ans * c[ci - 1][tc + 1] % mod;
		tc += ci;
	}
	printf("%lld\n" , ans);
	return 0;
}
