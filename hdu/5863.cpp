#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int jkpos[12][12];
int mxpos;
int n, m, dict;
struct matrix{
	long long a[70][70];
}b, t;

void X(const matrix &a, const matrix &b, matrix &r)
{
//	matrix r;
//  memset(r.a, 0, sizeof(r.a));
	for (int i = 0; i < mxpos; i++)
		for (int j = 0; j < mxpos; j++)
			r.a[i][j] = 0;
	for (int i = 0; i < mxpos; i++)
		for (int k = 0; k < mxpos; k++)
		{
			if (a.a[i][k])
			for (int j = 0; j < mxpos; j++)
				r.a[i][j] += a.a[i][k] * b.a[k][j] % mod;
		}
	for (int i = 0; i < mxpos; i++)
		for (int j = 0; j < mxpos; j++)
			r.a[i][j] %= mod;
}

int getid(int j, int k)
{
	if (jkpos[j][k] == -1)
		return jkpos[j][k] = mxpos++;
	return jkpos[j][k];
}

void build_matrix(matrix &mt)
{
	memset(jkpos, -1, sizeof(jkpos));
	memset(mt.a, 0, sizeof(mt.a));
	for (int j = 0; j <= m; j++)
	{
		if (j)
		{
			for (int k = j; k <= m; k++)
			{
				if (j < k)
					mt.a[getid(j - 1, k)][getid(j, k)] += dict;
				else
				{
					mt.a[getid(j - 1, k)][getid(j, k)] += dict;
					mt.a[getid(j - 1, k - 1)][getid(j, k)] += dict;
				}
			}
		} else {
			for (int k = 0; k <= m; k++)
				for (int j0 = 0; j0 <= k; j0++)
					mt.a[getid(j0, k)][getid(j, k)] += dict * (dict - 1);
		}
	}
}

long long sol()
{
//	freopen("1007.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &dict);
//	cerr << n << ' ' << m << ' ' << dict << endl;
	matrix mt, rm, tm;
	mxpos = 0;
	build_matrix(mt);
	long long ans = 0;
	memset(rm.a, 0, sizeof(rm));
	for (int i = 0; i < mxpos; i++)
		rm.a[i][i] = 1;
	while (n)
	{
		if (n & 1)
		{
			X(rm, mt, tm);
			rm = tm;
		}
		X(mt, mt, tm);
		mt = tm;
		n >>= 1;
	}
	for (int j = 0; j <= m; j++)
		ans += rm.a[getid(0, 0)][getid(j, m)];
	ans %= mod;
	return ans;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
//		cerr << t << endl;
		printf("%lld\n", sol());
	}
	return 0;
}
