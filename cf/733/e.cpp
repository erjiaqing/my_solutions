#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000 + 5;
int cntd[maxn], cntu[maxn];
int rcntd[maxn], rcntu[maxn];
long long sumd[maxn], sumu[maxn];
char s[maxn];
int n;

int main()
{
	scanf("%d", &n);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; i++)
	{
		sumd[i] = sumd[i - 1] + (s[i] == 'D' ? i : 0);
		cntd[i] = cntd[i - 1] + (s[i] == 'D' ? 1 : 0);
		sumu[i] = sumu[i - 1] + (s[i] == 'U' ? i : 0);
		cntu[i] = cntu[i - 1] + (s[i] == 'U' ? 1 : 0);
	}
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == 'D') rcntd[cntd[i]] = i;
		else rcntu[cntu[i]] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		if (i > 1) putchar(' ');
		if (s[i] == 'D')
		{
			int cul = cntu[i];
			int cdr = cntd[n] - cntd[i];
			if (cul <= cdr) // fall from left
			{
				int findd = cntd[i] + cul;
				int pos = rcntd[findd];
				long long ans1 = sumd[pos] - sumd[i] - ((long long)i) * cul;
				ans1 = ans1 * 2 - cul;
				long long ans2 = ((long long)i) * cul - sumu[i];
				ans2 = ans2 * 2 - cul;
				printf("%lld", ans1 + ans2 + cul * 2 + i);
			} else // fall from right
			{
				int findu = cntu[i] - cdr;
				int pos = rcntu[findu];
				long long ans1 = sumd[n] - sumd[i] - ((long long)i) * cdr;
				ans1 = ans1 * 2 - cdr;
				long long ans2 = ((long long)i) * (cdr + 1) - (sumu[i] - sumu[pos - 1]);
				ans2 = ans2 * 2 - cdr - 1;
				printf("%lld", ans1 + ans2 + (cdr + 1) * 2 + n - i);
			}
		} else
		{
			int cul = cntu[i - 1];
			int cdr = cntd[n] - cntd[i];
			if (cul < cdr) // fall from left
			{
				int findd = cntd[i] + cul + 1;
				int pos = rcntd[findd];
				long long ans1 = sumd[pos] - sumd[i] - ((long long)i) * (cul + 1);
				ans1 = ans1 * 2 - (cul + 1);
				long long ans2 = ((long long) i) * (cul + 1) - sumu[i];
				ans2 = ans2 * 2 - (cul);
				printf("%lld", ans1 + ans2 + (cul + 1) * 2 - 1 + i);
			} else // fall from right
			{
				int findu = cntu[i] - cdr;
				int pos = rcntu[findu];
				long long ans1 = sumd[n] - sumd[i] - ((long long)i) * cdr;
				ans1 = ans1 * 2 - cdr;
				long long ans2 = ((long long)i) * cdr - (sumu[i - 1] - sumu[pos - 1]);
				ans2 = ans2 * 2 - cdr;
				printf("%lld", ans1 + ans2 + cdr * 2 + n - i + 1);
			}
		}
	}
	return 0;
}
