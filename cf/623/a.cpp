#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
bool g[maxn][maxn];
vector<int> e[maxn];
char s[maxn];
int n, m;

bool dfs(int nd, char c) {
	if (s[nd]) return s[nd] == c;
	s[nd] = c;
	for (int nx : e[nd]) {
		bool tmp = dfs(nx, c == 'a' ? 'c' : 'a');
		if (tmp == false) return false;
	}
	return true;
}

int abs(int x) {
	return x > 0 ? x : -x;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		g[u][v] = g[v][u] = true;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (i == j || g[i][j]) continue;
			e[i].push_back(j);
		}
	bool tm = true;
	for (int i = 1; i <= n; i++)
		if (e[i].size() && !s[i])
			tm = tm && dfs(i, 'a');
	for (int i = 1; i <= n; i++)
		if (e[i].size() == 0)
			s[i] = 'b';
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (g[i][j] && abs(s[i] - s[j]) > 1)
				tm = false;
	if (tm) {cout << "Yes\n" << &s[1] << endl;}
	else {cout << "No\n";}
	return 0;
}
