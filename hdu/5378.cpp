/*
 * HDU 5378
 * Author: EJQ
 */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
const int maxn = 1000 + 5;
const long long mod = 1e9 + 7;
long long inv[maxn] , frac[maxn];
long long dp[maxn][maxn];
int n , k;
int fa[maxn];
vector<int> e[maxn];
typedef vector<int>:: iterator vit;
int qu[maxn] , sz[maxn] , qh , qt;
long long epow(long long a , int b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1)
			ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}
void work(int caseno)
{
	scanf("%d%d" , &n , &k);
	memset(dp , 0 , sizeof(dp));
	memset(fa , -1 , sizeof(fa));
	memset(sz , 0 , sizeof(sz));
	for (int i = 1 ; i <= n ; i++)
		e[i].clear();
	for (int i = 1 ; i < n ; i++)
	{
		int u , v;
		scanf("%d%d" , &u , &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	fa[1] = 0;
	qu[qh = qt = 0] = 1;
	while (qh <= qt)
	{
		int u = qu[qh++];
		for (vit v = e[u].begin() ; v != e[u].end() ; v++)
		{
			if (fa[*v] == -1)
			{
				fa[*v] = u;
				qu[++qt] = *v;
			}
		}
	}
	for (int i = qt ; i >= 0 ; i--)
	{
		sz[qu[i]]++;
		sz[fa[qu[i]]] += sz[qu[i]];
	}
	dp[n][0] = 1;
	for (int i = qt ; i >= 0 ; i--)
	{
		for (int j = 1 ; j <= k ; j++)
		{
			dp[i][j] = dp[i + 1][j] * (sz[qu[i]] - 1) % mod * inv[sz[qu[i]]] % mod + dp[i + 1][j - 1] * inv[sz[qu[i]]] % mod;
			dp[i][j] %= mod;
		}
	}
	printf("Case #%d: %lld\n" , caseno , frac[n] * dp[0][k] % mod);
}
int main()
{
	frac[0] = 1;
	for (int i = 1 ; i < maxn ; i++)
	{
		inv[i] = epow(i , mod - 2);
		frac[i] = frac[i - 1] * i % mod;
	}
	int t;
	scanf("%d" , &t);
	for (int i = 1 ; i <= t ; i++)
		work(i);
	return 0;
}
