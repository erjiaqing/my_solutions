#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;

vector<int> e[maxn];
int from[maxn];
bool used[maxn];

bool match(int x)
{
	for (int v : e[x])
	{
		if (!used[v])
		{
			used[v] = true;
			if (from[v] == -1 || match(from[v]))
			{
				from[v] = x;
				return true;
			}
		}
	}
	return false;
}

bool hungary(int _n)
{
	memset(from, -1, sizeof from);
	for (int i = 1; i <= _n; i++)
	{
		memset(used, 0, sizeof used);
		if (!match(i)) return false;
	}
	return true;
}

bool sol()
{
	int n, s;
	scanf("%d%d", &n, &s);
	for (int i = 0; i < maxn; i++) e[i].clear();
	int lt_n = min(s, n);
	if (lt_n > 100) return false;
	for (int i = 1; i <= lt_n; i++)
		for (int j = 1; j <= lt_n; j++)
			if ((i + s + (n - lt_n)) % j == 0)
				e[i].push_back(j);
	return hungary(lt_n);
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		bool res = sol();
		printf("Case #%d: %s\n", i, res ? "Yes" : "No");
	}
	return 0;
}
