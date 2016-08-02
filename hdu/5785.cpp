#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000 + 5;
const int mod = 1000000007;
char ma[maxn * 2], s[maxn];
int mp[maxn * 2];
long long bit1[maxn * 2], cnt1[maxn * 2], tl;
long long bit2[maxn * 2], cnt2[maxn * 2];
long long ans1[maxn], ans2[maxn];

#define lowbit(x) ( ( x ) & ( - ( x ) ) )
void add(int *bit, int l, int v)
{
	for (; l < tl; l += lowbit(l))
		(bit[l] += (v + mod) % mod) %= mod;
}

int sum(int *bit, int l)
{
	int ret = 0;
	for (; l; l -= lowbit(l))
		(ret += bit[l]) %= mod;
	return ret;
}

void prep(int len)
{
	int l = 0;
	ma[l++] = '$';
	ma[l++] = '#';
	for (int i = 0; i < len; i++)
	{
		ma[l++] = s[i];
		ma[l++] = '#';
	}
	ma[l] = 0;
	int mx = 0, id = 0;
	for (int i = 0; i < l; i++)
	{
		mp[i] = mx > i ? min(mp[2 *id - i], mx - i) : 1;
		while (ma[i + mp[i]] == ma[i - mp[i]])
			mp[i]++;
		if (i + mp[i] > mx)
		{
			mx = i + mp[i];
			id = i;
		}
	}
	tl = l;
}

void sol()
{
	int len = strlen(s);
	prep(len);
	memset(bit1, 0, sizeof(long long) * tl);
	memset(bit2, 0, sizeof(long long) * tl);
	memset(cnt1, 0, sizeof(long long) * tl);
	memset(cnt2, 0, sizeof(long long) * tl);
	for (int i = 1; i < tl; i++)
	{
		bit1[i] += i;
		bit1[i + mp[i]] -= i;
		cnt1[i] += 1;
		cnt1[i + mp[i]] -= 1;
		bit2[i + 1] -= i;
		bit2[i - mp[i] + 1] += i;
		cnt2[i + 1] -= 1;
		cnt2[i - mp[i] + 1] += 1;
	}
	for (int i = 1; i < tl; i++)
		bit1[i] += bit1[i - 1];
	for (int i = 1; i < tl; i++)
		bit2[i] += bit2[i - 1];
	for (int i = 1; i < tl; i++)
		cnt1[i] += cnt1[i - 1];
	for (int i = 1; i < tl; i++)
		cnt2[i] += cnt2[i - 1];
	for (int i = 2; i < tl; i += 2)
	{
		long long tans1 = bit1[i];
		long long tans2 = bit2[i];
		long long tcnt1 = cnt1[i];
		long long tcnt2 = cnt2[i];
		tans1 = (2 * tans1 - tcnt1 * i) / 2;
		tans2 = (2 * tans2 - tcnt2 * i) / 2;
		ans1[i / 2] = (tans1 % mod + mod) % mod;
		ans2[i / 2] = (tans2 % mod + mod) % mod;
	}
	long long ans = 0;
	for (int i = 1; i < len; i++)
		ans += ans1[i] * ans2[i + 1] % mod;
	ans %= mod;
	printf("%lld\n", ans);
}

int main()
{
	while (~scanf("%s", s))
		sol();
	return 0;
}

