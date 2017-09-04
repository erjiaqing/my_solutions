#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const double PI = acos(-1);
typedef complex<double> Complex;
const int N = 262144, L = 15, MASK = (1 << L) - 1;
Complex w[N];
void FFTInit()
{
	for (int i = 0; i < N; i++)
		w[i] = Complex(cos(2 * i * PI / N), sin(2 * i * PI / N));
}

void FFT(Complex p[], int n)
{
	for (int i = 1, j = 0; i < n - 1; i++)
	{
		for (int s = n; j ^= s >>= 1, ~j & s;);
		if (i < j) swap(p[i], p[j]);
	}
	for (int d = 0; (1 << d) < n; ++d)
	{
		int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
		for (int i = 0; i < n; i += m2) {
			for (int j = 0; j < m; j++) {
				Complex &p1 = p[i + j + m], &p2 = p[i + j];
				Complex t = w[rm * j] * p1;
				p1 = p2 - t;
				p2 = p2 + t;
			}
		}
	}
}

Complex A[N], B[N], C[N], D[N];
void mul(int a[N], int b[N])
{
	for (int i = 0; i < N; i++) {
		A[i] = Complex(a[i] >> L, a[i] & MASK);
		B[i] = Complex(b[i] >> L, b[i] & MASK);
	}
	FFT(A, N), FFT(B, N);
	for (int i = 0; i < N; i++)
	{
		int j = (N - i) % N;
		Complex da = (A[i] - conj(A[j])) * Complex(0, -0.5),
				db = (A[i] + conj(A[j])) * Complex(0.5, 0),
				dc = (B[i] - conj(B[j])) * Complex(0, -0.5),
				dd = (B[i] + conj(B[j])) * Complex(0.5, 0);
		C[j] = da * dd + da * dc * Complex(0, 1);
		D[j] = db * dd + db * dc * Complex(0, 1);
	}
	FFT(C, N), FFT(D, N);
	for (int i = 0; i < N; i++) {
		long long da = (long long)(C[i].imag() / N + 0.5) % mod,
			 db = (long long)(C[i].real() / N + 0.5) % mod,
			 dc = (long long)(D[i].imag() / N + 0.5) % mod,
			 dd = (long long)(D[i].real() / N + 0.5) % mod;
		a[i] = ((dd << (L * 2)) + ((db + dc) << L) + da) % mod;
	}
}

long long pow_mod(long long a, long long b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}

int ta[N], tb[N], nn[N], frac[N], ifrac[N];

struct DerangementsStrikeBack{
	int count(int n, int m)
	{
		FFTInit();
		memset(ta, 0, sizeof ta);
		memset(tb, 0, sizeof tb);
		memset(nn, 0, sizeof nn);
		memset(frac, 0, sizeof frac);
		memset(ifrac, 0, sizeof ifrac);
		nn[0] = frac[0] = ifrac[0] = 1;
		for (int i = 1; i <= m; i++)
		{
			frac[i] = ((long long)frac[i - 1]) * i % mod;
			ifrac[i] = pow_mod(frac[i], mod - 2);
			nn[i] = ((long long)(nn[i - 1])) * (n + i) % mod;
		}
		for (int i = 0; i <= m; i++)
		{
			ta[i] = ((long long)nn[i]) * ifrac[i] % mod;
			if (i & 1)
				tb[i] = (mod - ifrac[i]) % mod;
			else
				tb[i] = ifrac[i];
		}
		mul(ta, tb);
		int ans = 0;
		for (int i = 1; i <= m; i++)
			ans ^= (((long long)ta[i]) * frac[i] % mod);
		return ans;
	}
};

int main()
{
	int n, m;
	while (cin >> n >> m)
	{
		DerangementsStrikeBack sol;
		cout << sol.count(n, m) << endl;
	}
}
