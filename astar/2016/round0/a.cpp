#include <iostream>
#include <cstring>
using namespace std;
const int mod = 9973;
const int maxl = 100000 + 2;
int h[maxl];
int ih[maxl], inv[256];
int n;
char str[maxl];
int pow_mod(int a, int b, int mod)
{
	int ret = 1;
	while (b)
	{
		if (b & 1)
			(ret *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return ret;
}
int main()
{
	h[0] = ih[0] = 1;
	for (int i = 1; i < 256; i++)
		inv[i] = pow_mod(i, mod - 2, mod);
	while (~scanf("%d", &n))
	{
		scanf("%s", str + 1);
		int len = strlen(str + 1), a, b;
		for (int i = 1; i <= len; i++)
		{
			h[i] = h[i - 1] * (str[i] - 28) % mod;
			ih[i] = ih[i - 1] * inv[str[i] - 28] % mod;
		}
		while(n--)
		{
			scanf("%d%d", &a, &b);
			if (a > b)
			{
				int t = a;
				a = b;
				b = t;
			}
			printf("%d\n", h[b] * ih[a - 1] % mod);
		}
	}
	return 0;
}
