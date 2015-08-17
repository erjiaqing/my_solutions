#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
const long long mod = 3221225473;
const int maxn = 3e6 + 5;
int vis[maxn] , len[maxn] , s[maxn] , n;
int cnt[maxn] , tc[maxn] , vc[maxn];
long long ans = 0;
long long max(long long a , long long b)
{
	return b < a ? a : b;
}
long long pow(long long a , long long b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1)
			ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}
void factor(int v)
{
	int p = (sqrt(v) + 1);
	int tot = 0;
	for (int i = 2 ; i <= p ; i++)
	{
		if (v % i == 0)
		{
			tc[tot] = 0;
			while (v % i == 0)
			{
				tc[tot]++;
				v /= i;
			}
			vc[tot++] = i;
		}
	}
	if (v)
	{
		tc[tot] = 1;
		vc[tot++] = v;
	}
	for (int i = 0 ; i < tot ; i++)
		cnt[vc[i]] = max(cnt[vc[i]] , tc[i]);
}
void work()
{
	scanf("%d" , &n);
	memset(cnt , 0 , sizeof(cnt));
	memset(vis , 0 , sizeof(vis));
	memset(len , 0 , sizeof(len));
	for (int i = 1 ; i <= n ; i++)
		scanf("%d" , &s[i]);
	for (int i = 1 ; i <= n ; i++)
	{
		if (vis[i])
			continue;
		int j = s[i];
		while (!vis[j])
		{
			vis[j] = true;
			len[i]++;
			j = s[j];
		}
	}
	long long lcm = 1;
	for (int i = 1 ; i <= n ; i++)
		if (len[i])
			factor(len[i]);
	for (int i = 1 ; i <= n ; i++)
		lcm = lcm * pow((long long)(i) , (long long)cnt[i]) % mod;
	printf("%lld\n" , lcm);
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		work();
	return 0;
}
