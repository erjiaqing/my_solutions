#include <bits/stdc++.h>
using namespace std;

char ans[1000000 + 5];

int main()
{
	long long a00, a01, a10, a11;
	cin >> a00 >> a01 >> a10 >> a11;
	long long sum0 = 0, sum1 = 0, n = 0;
	for (n = 1; n <= 1000000; n++)
		if (n * (n - 1) / 2 == a00 + a01 + a10 + a11)
			break;
	if (n > 1000000) {puts("Impossible");return 0;}
	if (a01 == 0 && a10 == 0 && n > 1 && a11)
	{
		sum0 = 0;
	} else
	{
		for (sum0 = 1; sum0 <= n; sum0++)
			if (sum0 * (sum0 - 1) / 2 == a00)
				break;
	}
	if (sum0 > n) {puts("Impossible");return 0;}
	sum1 = n - sum0;
	if (sum1 * (sum1 - 1) / 2 != a11) {puts("Impossible");return 0;}
	if (sum0 * sum1 != a01 + a10) {puts("Impossible");return 0;}
	memset(ans, '0', sizeof(char) * n);
	long long last0 = sum0, last1 = sum1, curr = 0;
	for (int i = 0; i < n; i++)
	{
		if (last0 + curr <= a10 && last1)
		{
			ans[i] = '1';
			curr += last0;
			last1--;
		} else
		{
			last0--;
		}
	}
	puts(ans);
	return 0;
}
