#include <bits/stdc++.h>
using namespace std;

const int maxn = 50000 + 5;
long long numbers[maxn];

void sol()
{
	int n;
	scanf("%d", &n);
	numbers[n] = 0;
	for (int i = 0; i < n; i++) scanf("%lld", &numbers[i]);
	sort(&numbers[0], &numbers[n]);
	long long curmx = 0;
	long long lst = 0;
	//int ans = 0;
	for (int i = 0; i < n; i++)
	{
		curmx = max(curmx, numbers[i] - lst);
		lst = curmx;
	}
	printf("%lld\n", lst);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}

