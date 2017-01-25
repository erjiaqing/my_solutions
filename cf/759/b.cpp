#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

int n;
int t[maxn];
int c[maxn];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &t[i]);
//		t[i] += t[i - 1];
		int tans = c[i - 1] + 20;
		int last_opt = lower_bound(&t[1], &t[i], t[i] - 89) - t;
		tans = min(tans, c[last_opt - 1] + 50);
//		cerr << last_opt << ' ' << c[last_opt - 1] + 50 << ":";
		last_opt = lower_bound(&t[1], &t[i], t[i] - 1439) - t;
		tans = min(tans, c[last_opt - 1] + 120);
//		cerr << last_opt << ' ' << c[last_opt - 1] + 120 << "\n";
		c[i] = tans;
		printf("%d\n", c[i] - c[i - 1]);
	}
	return 0;
}
