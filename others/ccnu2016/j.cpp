#include <iostream>
#include <utility>
using namespace std;

typedef unsigned int f;
const int maxn = 100000 + 1;
#define x first
#define y second

struct m33{
	f a[3][3];
	
	m33()
	{
		for (int i = 0; i < 3; i++)
			a[i][0] = a[i][1] = a[i][2] = 0u;
	}
	m33(const f p, const f q, const f r, const f s)
	{
		a[0][0] = p * p;/***/a[0][1] = p * r;/********/a[0][2] = r * r;
		a[1][0] = 2u * p * q;a[1][1] = (p * s + q * r);a[1][2] = 2u * r * s;
		a[2][0] = q * q;/***/a[2][1] = q * s;/********/a[2][2] = s * s;
		//for (int i = 0; i < 3; i++)
		//	fprintf(stderr, "| %10u %10u %10u |\n", a[i][0], a[i][1], a[i][2]);
		//fprintf(stderr, "\n");
	}

	//f * operator[] (const int _)
	//{
	//	return &a[_][0];
	//}

	void x(m33 _)
	{
		f t[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				t[i][j] = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					t[i][k] += a[i][j] * _.a[j][k];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				a[i][j] = t[i][j];
	}
}; // 3 x 3 matrix
struct m13{
	f a[3];
	
	m13()
	{
		a[0] = a[1] = a[2] = 0u;
	}

	//f & operator[] (const int _)
	//{
	//	return a[_];
	//}
	
	void x(m33 _)
	{
		f t[3] = {0u, 0u, 0u};
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				t[j] += a[i] * _.a[i][j];
		for (int i = 0; i < 3; i++)
			a[i] = t[i];
	}

	m13 xx(m33 _)
	{
		m13 t;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				t.a[j] += a[i] * _.a[i][j];
		return t;
	}
}; // 1 x 3 matrix

typedef pair<m13, m33> pmm;
pmm segt[maxn * 4];
#define ls( _ ) ( ( _ ) << 1 )
#define rs( _ ) ( ls( _ ) | 1 )

void init(m33 &_, f v)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_.a[i][j] = 0;
	_.a[0][0] = _.a[1][1] = _.a[2][2] = v;
}

f a[maxn], b[maxn];

void push_up(int x)
{
	for (int i = 0; i < 3; i++)
		segt[x].x.a[i] = segt[ls(x)].x.a[i] + segt[rs(x)].x.a[i];
//	segt[x].x = segt[ls(x)].x + segt[rs(x)].x;
//	segt[x].x.x(segt[x].y);
}

void push_dn(int x)
{
	segt[ls(x)].x.x(segt[x].y);
	segt[rs(x)].x.x(segt[x].y);
	segt[ls(x)].y.x(segt[x].y);
	segt[rs(x)].y.x(segt[x].y);
	init(segt[x].y, 1u);
}

void build_segt(int x, int l, int r)
{
	init(segt[x].y, 1u);
	if (l == r)
	{
		segt[x].x.a[0] = a[l] * a[l];
		segt[x].x.a[1] = a[l] * b[l];
		segt[x].x.a[2] = b[l] * b[l];
		return;
	}
	int mid = (l + r) / 2;
	build_segt(ls(x), l, mid);
	build_segt(rs(x), mid + 1, r);
	push_up(x);
}

void operation1(int x, int l, int r, int ql, int qr, m33 _)
{
	if (l == ql && r == qr)
	{
		segt[x].x.x(_);
		segt[x].y.x(_);
		return;
	}
	int mid = (l + r) / 2;
	push_dn(x);
	if (qr <= mid)
		operation1(ls(x), l, mid, ql, qr, _);
	else if (mid < ql)
		operation1(rs(x), mid + 1, r, ql, qr, _);
	else
	{
		operation1(ls(x), l, mid, ql, mid, _);
		operation1(rs(x), mid + 1, r, mid + 1, r, _);
	}
	push_up(x);
}

f operation2(int x, int l, int r, int ql, int qr)
{
//	fprintf(stderr, "%d : %d - %d q %d - %d\n", x, l, r, ql, qr);
	if (l == ql && r == qr)
		return segt[x].x.a[1];
	push_dn(x);
	int mid = (l + r) / 2;
	f ret = 0;
	if (qr <= mid)
		ret = operation2(ls(x), l, mid, ql, qr);
	else if (ql > mid)
		ret = operation2(rs(x), mid + 1, r, ql, qr);
	else
		ret = operation2(ls(x), l, mid, ql, mid) + operation2(rs(x), mid + 1, r, mid + 1, qr);
	push_up(x);
	return ret;
}

#undef x
#undef y

int n, m, x, y, o;
f p, q, r, s;
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	build_segt(1, 1, n);
	for (int i = 0; i < m; i++)
	{
		cin >> o >> x >> y;
		if (o == 1)
		{
			cin >> p >> q >> r >> s;
			operation1(1, 1, n, x, y, m33(p, q, r, s));
		} else {
			cout << operation2(1, 1, n, x, y) << "\n";
		}
	}
	return 0;
}

