class BearSpans {
public:
	vector<int> ans;
	set<pair<int, int> > se;
	int k, dep = 0;
	int cur;
	int n;
	void dfs(int lay, int l, int r) {
		if (lay == k || (r - l + 1) < 4) {
			dep = max(dep, lay);
			for (int i = l + 1; i <= r; i++) {
				ans.push_back(l);
				ans.push_back(i);
				se.erase(make_pair(l, i));
			}
			return;
		}
		int mid = (l + r) / 2;
		dfs(lay + 1, l, mid);
		dfs(lay + 1, mid + 1, r);
		ans.push_back(l);
		ans.push_back(mid + 1);
		se.erase(make_pair(l, mid + 1));
	}
	vector<int> findAnyGraph(int _n, int m, int _k) {
		k = _k;
		n = _n;
		if (int(log(n) / log(2) + 1e-6) < k) {ans.push_back(-1);return ans;}
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				se.insert(make_pair(i, j));
		dfs(1, 1, n);
		if (k > dep || ans.size() > m * 2){ans.clear();ans.push_back(-1);return ans;}
		while (ans.size() < m * 2) {
			pair<int, int> pi = *se.begin();
			ans.push_back(pi.first);
		   	ans.push_back(pi.second);
			se.erase(*se.begin());
		}
		return ans;
	}
};
