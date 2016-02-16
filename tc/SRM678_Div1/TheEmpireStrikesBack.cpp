#define maxn (100000 + 1)
#define mod (1000000007)
#define x first
#define y second
class TheEmpireStrikesBack {
public:
	vector<pair<long long, long long> > pt;
	vector<pair<long long, long long> > p;
	bool check(int t, int m) {
		int nw = 0;
		for (int i = 0; i < m; i++) {
			int mxy = p[nw].y;
			int mxx = -1;
			while (nw + 1 < p.size() && p[nw + 1].y + t >= mxy) nw++;
			mxx = p[nw].x;
			while (nw + 1 < p.size() && mxx + t >= p[nw + 1].x) nw++;
			if (++nw == p.size()) return true;
		}
		return false;
	}
	int find(int _AX, int BX, int CX, int _AY, int BY, int CY, int N, int M) {
		long long AX = _AX, AY = _AY;
		int mint = -1;
		pt.clear(), p.clear();
		pt.push_back(make_pair(AX, AY));
		for (int i = 1; i < N; i++)
			pt.push_back(make_pair(AX = ((AX * BX) + CX) % mod, AY = ((AY * BY) + CY) % mod));
		sort(pt.begin(), pt.end());
		for (int i = 0; i < N; i++) {
			while (p.size() && pt[i].y >= p[p.size() - 1].y) p.pop_back();
			p.push_back(pt[i]);
		}
		for (int i = (1 << 30); i; i >>= 1) {
			if (!check(mint + i, M)) mint += i;
		}
		return mint + 1;
	}
};

