#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

typedef long long ll;
set<ll> b;

ll b_evensum[maxn], b_oddsum[maxn];

ll find_closest(ll val)
{
	auto rr = b.lower_bound(val);
	auto ll = rr;
	if (rr != b.begin())
	{
		ll--;
		return min(val - *ll, *rr - val);
	}
	return *rr - val;
}

int main()
{
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	ll sum = 0;
	b.insert(0x3f3f3f3f3f3f3f3f);
	for (int i = 1; i <= n; i++)
	{
		int t;
		scanf("%d", &t);
		if (i & 1) sum += t;
		else sum -= t;
	}
	for (int i = 1; i <= m; i++)
	{
		int tb;
		scanf("%d", &tb);
		b_oddsum[i] = b_oddsum[i - 1];
		b_evensum[i] = b_evensum[i - 1];
		if (i & 1)
			b_oddsum[i] += tb;
		else
			b_evensum[i] += tb;
		if (i >= n)
		{
			int flg = (i - n + 1) % 2;
			if (flg)
				b.insert(b_oddsum[i] - b_oddsum[i - n] - (b_evensum[i] - b_evensum[i - n]));
			else
				b.insert(b_evensum[i] - b_evensum[i - n] - (b_oddsum[i] - b_oddsum[i - n]));
		}
	}
	printf("%lld\n", find_closest(sum));
	while (q--)
	{
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		if (l % 2 == r % 2)
		{
			if (l % 2 == 1)
				sum += x;
			else
				sum -= x;
		}
		printf("%lld\n", find_closest(sum));
	}
	return 0;
}

