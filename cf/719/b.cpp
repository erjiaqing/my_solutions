#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;
int n;

char in[maxn];
int b[2], r[2];
int ans = 0x3f3f3f3f;

int main()
{
	scanf("%d", &n);
	scanf("%s", in);
	for (int i = 0; i < n; i++)
		if (in[i] == 'b')
			b[i & 1]++;
		else
			r[i & 1]++;
	// rbrbr...
	{
		int swp = min(b[0], r[1]);
		ans = min(ans, b[0] + r[1] - swp);
	}
	// brbrb...
	{
		int swp = min(b[1], r[0]);
		ans = min(ans, b[1] + r[0] - swp);
	}
	printf("%d\n", ans);
	return 0;
}
