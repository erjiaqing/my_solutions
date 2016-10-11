#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
long long beauty[maxn];
bool cap[maxn];
long long sumbeauty, sumcap, ans;
int n, m;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> beauty[i];
		sumbeauty += beauty[i];
		ans += beauty[i] * beauty[i - 1];
	}
	ans += beauty[1] * beauty[n];
	for (int i = 1; i <= m; i++)
	{
		int tp = 0;
		cin >> tp;
		cap[tp] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		long long tsum = 0;
		if (!cap[(i - 2 + n) % n + 1]) tsum += beauty[(i - 2 + n) % n + 1];
		tsum += beauty[i % n + 1];
		if (cap[i])
		{
			sumcap += beauty[i];
			ans += beauty[i] * (sumbeauty - sumcap - tsum);
		}
	}
	cout << ans << endl;
	return 0;
}
