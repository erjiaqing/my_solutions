#include <iostream>
#include <cstdio>
using namespace std;

typedef unsigned int f;
const int maxn = 100000 + 1;

f vec[maxn * 4][3];
f laz[maxn * 4][3][3];
f tmat[3][3];

void mul(f _v[], f _m[][3], f _r[])
{
	for (int i = 0; i < 3; i++) _r[i] = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_r[j] += _v[i] * _m[i][j];
}

void mul(f _v[], f _m[][3])
{
	f tvec[3];
	mul(_v, _m, tvec);
	for (int i = 0; i < 3; i++)
		_v[i] = tvec[i];
}

void mul(f _m1[][3], f _m2[][3], f _r[][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_r[i][j] = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				_r[i][k] += _m1[i][j] * _m2[j][k];
}

void mul(f _m1[][3], f _m2[][3])
{
	f tmat[3][3];
	mul(_m1, _m2, tmat);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_m1[i][j] = tmat[i][j];
}

void add(f _v1[], f _v2[], f _tv[])
{
	for (int i = 0; i < 3; i++)
		_tv[i] = _v1[i] + _v2[i];
}

void add(f _v1[], f _v2[])
{
	f tvec[3];
	add(_v1, _v2, tvec);
	for (int i = 0; i < 3; i++)
		_v1[i] = tvec[i];
}

// ^ : Define of matrix

#define ls( _ ) ( ( _ ) << 1 )
#define rs( _ ) ( ls( _ ) | 1 )

void init(f _[][3], f v)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_[i][j] = 0;
	_[0][0] = _[1][1] = _[2][2] = v;
}

void init(f _[][3], f p, f q, f r, f s)
{
	_[0][0] = p * p;    _[0][1] = p * r;        _[0][2] = r * r;
	_[1][0] = 2 * p * q;_[1][1] = p * s + q * r;_[1][2] = 2 * r * s;
	_[2][0] = q * q;    _[2][1] = q * s;        _[2][2] = s * s;
}

void push_dn(int x)
{
	mul(vec[ls(x)], laz[x]);
	mul(vec[rs(x)], laz[x]);
	mul(laz[ls(x)], laz[x]);
	mul(laz[rs(x)], laz[x]);
	init(laz[x], 1u);
}

void push_up(int x)
{
	add(vec[ls(x)], vec[rs(x)], vec[x]);
}

f a[maxn], b[maxn];

void build(int x, int l, int r)
{
	init(laz[x], 1u);
	if (l == r)
	{
		vec[x][0] = a[l] * a[l];
		vec[x][1] = a[l] * b[l];
		vec[x][2] = b[l] * b[l];
		return;
	}
	int mid = (l + r) / 2;
	build(ls(x), l, mid);
	build(rs(x), mid + 1, r);
	push_up(x);
}

void op1(int x, int l, int r, int ql, int qr)
{
	if (ql == l && qr == r)
	{
		mul(vec[x], tmat);
		mul(laz[x], tmat);
		return;
	}
	push_dn(x);
	int mid = (l + r) / 2;
	if (qr <= mid)
		op1(ls(x), l, mid, ql, qr);
	else if (mid < ql)
		op1(rs(x), mid + 1, r, ql, qr);
	else
	{
		op1(ls(x), l, mid, ql, mid);
		op1(rs(x), mid + 1, r, mid + 1, qr);
	}
	push_up(x);
}

f op2(int x, int l, int r, int ql, int qr)
{
	if (ql == l && qr == r)
		return vec[x][1];
	push_dn(x);
	int mid = (l + r) / 2;
	f ret = 0;
	if (qr <= mid)
		ret = op2(ls(x), l, mid, ql, qr);
	else if (ql > mid)
		ret = op2(rs(x), mid + 1, r, ql, qr);
	else
		ret = op2(ls(x), l, mid, ql, mid) + op2(rs(x), mid + 1, r, mid + 1, qr);
	push_up(x);
	return ret;
}

int main()
{
	freopen("J.in", "r", stdin);
	freopen("j.out", "w", stdout);
	int n, m, o, x, y;
	f p, q, r, s;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		cin >> o >> x >> y;
		if (o == 1)
		{
			cin >> p >> q >> r >> s;
			init(tmat, p, q, r, s);
			op1(1, 1, n, x, y);
		} else {
			cout << op2(1, 1, n, x, y) << "\n";
		}
	}
	return 0;
}
