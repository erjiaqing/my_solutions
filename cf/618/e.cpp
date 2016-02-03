#include <bits/stdc++.h>
using namespace std;
#define ls( _ ) ( ( _ ) << 1 )
#define rs( _ ) ( ls( _ ) | 1 )
const int maxn = 300000 + 5;
const double pi = acos(-1);
int n, m;
char buf[256];
struct mat{
	double a[3][3];
	mat(const bool _ = false) {
		memset(a, 0, sizeof(a));
		if (_) a[0][0] = a[1][1] = a[2][2] = 1.;
	}
	mat operator * (const mat &_) {
		mat ret;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					ret.a[i][k] += a[i][j] * _.a[j][k];
		return ret;
	}
}seg[maxn * 4];

void pushdn(int x) {
	seg[ls(x)] = seg[ls(x)] * seg[x];
	seg[rs(x)] = seg[rs(x)] * seg[x];
	seg[x] = mat(true);
}

void segadd(int x,int l, int r, int ql, int qr, const mat &_) {
	if (ql == l && r == qr) {
		seg[x] = seg[x] * _;
		return;
	}
	int mid = (l + r) / 2;
	pushdn(x);
	if (qr <= mid) segadd(ls(x), l, mid, ql, qr, _);
	else if (ql > mid) segadd(rs(x), mid + 1, r, ql, qr, _);
	else segadd(ls(x), l, mid, ql, mid, _),
		segadd(rs(x), mid + 1, r, mid + 1, qr, _);
}

mat segget(int x, int l, int r, int _) {
	if (l == r) {
		return seg[x];
	}
	int mid = (l + r) / 2;
	if (_ <= mid) return segget(ls(x), l, mid, _) * seg[x];
	else return segget(rs(x), mid + 1, r, _) * seg[x];
}

void add(int x, const mat &r) {segadd(1, 0, n, x, n, r);}
mat get(int x) {return segget(1, 0, n, x);}

int main() {
	ios::sync_with_stdio(0);
	mat work;
	cin >> n >> m;
	for (int i = 0; i < maxn * 4; i++) {
		mat &f = seg[i];
		f.a[0][0] = f.a[1][1] = f.a[2][2] = 1;
	}
	work.a[0][0] = n;
	work.a[0][1] = 0;
	work.a[0][2] = 1;
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		if (x == 1) {
			mat cur, pre, nxt(true);
			double dx, dy, dg;
			cur.a[0][0] = y;
			cur.a[0][1] = 0;
			cur.a[0][2] = 1;
			pre.a[0][0] = y - 1;
			pre.a[0][1] = 0;
			pre.a[0][2] = 1;
			cur = cur * get(y);
			pre = pre * get(y - 1);
			dx = cur.a[0][0] - pre.a[0][0];
			dy = cur.a[0][1] - pre.a[0][1];
			dg = atan2(dy, dx);
			nxt.a[2][0] = cos(dg) * z;
			nxt.a[2][1] = sin(dg) * z;
			work = work * nxt;
			add(y, nxt);
		}
		else if (x == 2) {
			mat cur, nxt;
			double deg = z * pi / 180;
			double cdeg = cos(deg), sdeg = sin(deg);
			cur.a[0][0] = y - 1;
			cur.a[0][1] = 0;
			cur.a[0][2] = 1;
			cur = cur * get(y - 1);
			nxt.a[0][0] = cdeg;
			nxt.a[0][1] = -sdeg;
			nxt.a[2][0] = (1 - cdeg) * cur.a[0][0] - sdeg * cur.a[0][1];
			nxt.a[1][0] = sdeg;
			nxt.a[1][1] = cdeg;
			nxt.a[2][1] = sdeg * cur.a[0][0] + (1 - cdeg) * cur.a[0][1];
			nxt.a[2][2] = 1;
			work = work * nxt;
			add(y, nxt);
		}
		sprintf(buf, "%.8f %.8f\n", work.a[0][0], work.a[0][1]);
		cout << buf;
	}
}
