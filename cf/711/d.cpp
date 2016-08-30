#include <bits/stdc++.h>
using namespace std;
namespace ejq{
const int maxn = 200000 + 5;

const int mod = 1000000007;

typedef pair<int, int> pii;

struct edge{
	int to, next;
	int id;
}edge[maxn * 2];

int head[maxn], tot;
int vis[maxn], lay[maxn], fa[maxn];

int sz, n;

void addedge(int u, int v, int id)
{
	edge[tot].to = v;edge[tot].next = head[u];edge[tot].id = id;
	head[u] = tot++;
}

void dfs(int lay, int u, int pre)
{
	vis[u] = 1;
	ejq::lay[u] = lay;
	for (int i = head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].to;
		if (edge[i].id == pre) continue;
		if (vis[v] == 1)
		{
			int tmp = u;
			sz = 1;
			while (tmp != v)
			{
//				cerr << tmp << ' ';
				sz++, tmp = fa[tmp];
			}
//			cerr << tmp << endl;
		} else if (vis[v] == 0)
		{
			fa[v] = u;
			dfs(lay + 1, v, edge[i].id);
		}
	}
	vis[u] = 2;
}

long long powmod(long long a, int b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	tot = 0;
	memset(head, -1, sizeof head);
	for (int i = 1; i <= n; i++)
	{
		int ta;
		scanf("%d", &ta);
		addedge(i, ta, i);
		addedge(ta, i, i);
	}
	long long rans = 1;
	int tsz = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
		{
			sz = 0;
			dfs(1, i, -1);
			assert(sz > 0);
			if (sz > 0)
			{
				rans = rans * ((powmod(2, sz) - 2 + mod) % mod) % mod;
				tsz += sz;
			}
		}
	}
	tsz = n - tsz;
	long long tans2 = powmod(2, tsz);
	tans2 = tans2 * rans % mod;
	printf("%lld\n", tans2);
	return 0;
}

}
int main()
{
	return ejq::main();
}
