class DiameterOfRandomTree {
public:
	vector<int> e[55];
	double dp[55][150];
	int max_mx;
	void dfs(int u, int f, int mx) {
		dp[u][0] = 1.0;
		for (int v : e[u]) {
			if (v == f) continue;
			dfs(v, u, mx);
			vector<double> nu(max_mx, 0.0);
			for (int i = 0; i <= mx; i++)
				for (int dy = 1; dy <= 2; dy++)
					for (int j = 0; i + j + dy <= mx; j++) {
						nu[max(j + dy, i)] += dp[u][i] * dp[v][j] * 0.5;
					}
			for (int i = 0; i < max_mx; i++)
				dp[u][i] = nu[i];
			for (int i = max_mx; i < 150; i++)
				dp[u][i] = 0;
		}
	}
	double getExpectation(vector<int> a, vector<int> b) {
		for (int i = 0; i < (int)a.size(); i++) {
			e[a[i]].push_back(b[i]);
			e[b[i]].push_back(a[i]);
		}
		double ans = 0;
		max_mx = a.size() * 2 + 1;
		vector<double> r(max_mx, 0.0);
		for (int i = 0; i < max_mx; i++) {
			memset(dp, 0, sizeof(dp));
			dfs(0, -1, i);
			for (int j = 0; j <= i; j++)
				r[i] += dp[0][j];
		}
		for (int i = 1; i < max_mx; i++)
			ans += (r[i] - r[i - 1]) * i;
		return ans;
	}
};

