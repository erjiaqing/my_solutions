typedef pair<pair<int, int>, int> pii;
#define x first
#define y second
class FleetFunding {
public:
	bool check(int k, const int m, vector<pii> v) {
		vector<int> vl(m + 1, k);
		for (int i = 1; i <= m; i++) {
			for (auto n = v.begin(); n != v.end(); n++) {
				if (n->x.x >= i && n->x.y <= i) {
					int add = min(n->y, vl[i]);
					vl[i] -= add;
					n->y -= add;
				}
			}
		}
		for (int i = 1; i <= m; i++) if (vl[i]) return false;
		return true;
	}
	int maxShips(int m, vector<int> k, vector<int> a, vector<int> b) {
		vector<pii> v;
		int n = k.size();
		for (int i = 0; i < n; i++)
			v.push_back(make_pair(make_pair(b[i], a[i]), k[i]));
		sort(v.begin(), v.end());
		int ans = 0;
		for (int i = (1 << 30); i; i >>= 1)
			if (check(ans | i, m, v))
				ans |= i;
		return ans;
	}
};
