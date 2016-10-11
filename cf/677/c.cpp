#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

char buf[100000 + 1];

char str[] = "0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"-_";
int num[128];
int pow3[7];

int main()
{
	pow3[0] = 1;
	for (int i = 1; i <= 6; i++) pow3[i] = pow3[i - 1] * 3;
	for (int i = 0; i < 64; i++)
	{
		int cbit = 0;
		for (int j = 0; j < 6; j++)
			if (i & (1 << j))
				cbit++;
		num[str[i]] = pow3[6 - cbit];
	}
	long long ans = 1;
	scanf("%s", buf);
	for (int i = 0; buf[i]; i++)
		(ans *= num[buf[i]]) %= mod;
	printf("%lld\n", ans);
	return 0;
}
