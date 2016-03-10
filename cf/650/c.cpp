#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> vp;

#define x first
#define y second

const int maxn = 1000000 + 1;
int fa[maxn];
int fval[maxn];

int fin(int x) {return fa[x] = ((fa[x] == x) ? x : fin(fa[x]));}

void uni(int x, int y) {
	int fx = fin(x);
	int fy = fin(y);
	if (fx == 0 || fy == 0) return;
	fa[fy] = fx;
}

int main() {
	ios::sync_with_stdio(0);
	vector< vector<int> > v;
	vector< vp > ve;
	vector< pii > row_max, col_max;
	vector< int > row_max_id, col_max_id;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		v.push_back(vector<int>(m, 0));
	for (int i = 0; i < n; i++)
		row_max.push_back(pii(0, 0)),
		row_max_id.push_back(0);
	for (int i = 0; i < m; i++)
		col_max.push_back(pii(0, 0)),
		col_max_id.push_back(0);
	int cn = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			fa[cn] = cn;
			v[i][j] = cn++;
			int vl;
			cin >> vl;
			//cerr << v[i][j] << endl;
			ve.push_back(make_pair(vl, make_pair(i, j)));
		}
	sort(ve.begin(), ve.end());
	for (auto val : ve) {
		pii tr = row_max[val.y.x];int vr = fval[fin(row_max_id[val.y.x])];
		pii tc = col_max[val.y.y];int vc = fval[fin(col_max_id[val.y.y])];
		int vl = max(val.x == tr.y ? vr : vr + 1, 
					 val.x == tc.y ? vc : vc + 1);
		if (tr.y == val.x) uni(v[val.y.x][val.y.y], row_max_id[val.y.x]);
		if (tc.y == val.x) uni(v[val.y.x][val.y.y], col_max_id[val.y.y]);
		row_max[val.y.x] = pii(vl, val.x);
		col_max[val.y.y] = pii(vl, val.x);
		col_max_id[val.y.y] = row_max_id[val.y.x] = v[val.y.x][val.y.y];
		fval[fin(v[val.y.x][val.y.y])] = vl;
		//v[val.y.x][val.y.y] = vl;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << fval[fin(v[i][j])] << ' ';
		cout << '\n';
	}
	return 0;
}
