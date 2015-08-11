/********************
 * HDU 5379         *
 * Author: EJQ      *
 ********************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 5;
const long long mod = 1000000007;
vector<int> e[maxn] , s[maxn];
typedef vector<int> :: iterator vii;
int que[maxn] , qh , qt;
int vis[maxn] , sz[maxn];
long long ans[maxn] , frac[maxn];
int n;
/*
long long dfs(int u)
{
	long long t = 1 , s = 0 , ns = 0;
	vis[u] = true;
	sz[u] = 1;
	for (int v = 0 ; v < e[u].size() ; v++)
	{
		if (!vis[e[u][v]])
		{
			(t *= dfs(e[u][v])) %= mod;
			if (sz[e[u][v]] > 1)
				ns++;
			else
				s++;
			sz[u] += sz[e[u][v]];
		}
	}
	if (ns > 2)
		return 0;
	if (sz[u] > 1)
	{
		if (ns == 2)
			(t *= frac[s]) %= mod;
		if (ns < 2)
			(t *= frac[s] * 2) %= mod;
	}
	return t;
}
*/
void work(int caseno)
{
	scanf("%d" , &n);
	for (int i = 1 ; i <= n ; i++)
	{
		e[i].clear();
		s[i].clear();
	}
	memset(vis , 0 , sizeof(vis));
	for (int i = 1 ; i < n ; i++)
	{
		int u , v;
		scanf("%d%d" , &u , &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	que[qh = qt = 0] = 1;
	vis[1] = true;
	while (qh <= qt)
	{
		int u = que[qh++];
		for (vii v = e[u].begin() ; v != e[u].end() ; v++)
		{
			if (!vis[*v])
			{
				vis[*v] = 1;
				s[u].push_back(*v);
				que[++qt] = *v;
			}
		}
	}
	for (int i = qt ; i >= 0 ; i--)
	{
		int cs = 0 , cn = 0;
		int u = que[i];
		ans[u] = 1;
		for (vii v = s[u].begin() ; v != s[u].end() ; v++)
		{
			int ss = s[*v].size();
			if (ss != 0)
			{
				cn++;
			}
			cs++;
			(ans[u] *= ans[*v]) %= mod;
		}
		if (cn > 2)
			ans[u] = 0;
		if (cs)
		{
			if (cn <= 1)
			{
				ans[u] = ans[u] * frac[cs - cn] % mod;
				ans[u] = ans[u] * 2 % mod;
			}
			if (cn == 2)
				ans[u] = ans[u] * frac[cs - cn] % mod;
		}
	}
	printf("Case #%d: %lld\n" , caseno , ans[1]);
}
int main()
{
	frac[0] = 1;
	for (int i = 1 ; i < maxn ; i++)
		frac[i] = frac[i - 1] * i % mod;
	int t ;
	scanf("%d" , &t);
	for (int c = 1 ; c <= t ; c++)
		work(c);
	return 0;
}
