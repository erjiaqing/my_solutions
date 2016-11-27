#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int maxn = 200000 + 5;
int ans[maxn], a[maxn], n;
typedef pair<long long, int> pli;
vector<pli> e[maxn];

tree<pli, null_type, less<pli>, rb_tree_tag, 
	  tree_order_statistics_node_update> s;

void dfs(int u, long long deep)
{
	int ans1 = s.order_of_key(pli(deep, n + 10));
	for (pli v : e[u])
		dfs(v.second, deep + v.first);
	ans[u] = s.order_of_key(pli(deep, n + 10)) - ans1;
	s.insert(pli(deep - a[u], u));
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 2; i <= n; i++)
	{
		int p, v;
		scanf("%d%d", &p, &v);
		e[p].push_back(pli(v, i));
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
