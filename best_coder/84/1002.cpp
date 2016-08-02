#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 5;
int a[maxn], f[maxn], b[maxn];
int n;

void sol()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	memset(f, 0x3f, sizeof(int) * (n + 2));
	f[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int len = lower_bound(&f[0], &f[n + 1], a[i]) - &f[0];
		b[i] = len;
		f[len] = min(f[len], a[i]);
	}
	for (int i = 1; i <= n; i++)
		printf("%d%c", b[i], i == n ? '\n' : ' ');
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
