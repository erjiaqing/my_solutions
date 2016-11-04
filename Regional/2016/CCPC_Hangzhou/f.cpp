#include <bits/stdc++.h>
using namespace std;

char str[25];

long long sol()
{
	scanf("%s", str);
	int ls = strlen(str);
	long long ans = 0x8000000000000000;
	for (int i = 0; i < ls - 3; i++) // Pos of '+'
	{
		long long c1 = 0;
		for (int tj = 0; tj <= i; tj++)
			c1 = c1 * 10 + (str[tj] - '0');
		for (int j = i + 1; j < ls - 3; j++) // Pos of '-'
		{
			long long c2 = 0;
			for (int tj = i + 1; tj <= j; tj++)
				c2 = c2 * 10 + (str[tj] - '0');
			long long c3 = (str[j + 1] - '0');
			long long c4 = (str[j + 2] - '0');
			long long c5 = 0;
			for (int tj = j + 3; tj < ls; tj++)
				c5 = c5 * 10 + (str[tj] - '0');
//			cerr << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4 << ' ' << c5 << endl;
			ans = max(ans, c1 + c2 - c3 * c4 / c5);
		}
	}
	return ans;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
		printf("Case #%d: %lld\n", i, sol());
	return 0;
}
