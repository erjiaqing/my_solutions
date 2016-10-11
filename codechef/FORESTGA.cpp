#include <iostream>
using namespace std;
const int maxn = 100000;
int h[maxn], r[maxn], w, l, n;
bool check(long long m)
{
	long long tot = 0;
	for (int i = 0; i < n; i++)
		if (h[i] + r[i] * m >= l)
		{
			tot += h[i] + r[i] * m;
			if (h[i] + r[i] * m >= w)
				return true;
			if (tot >= w)
				return true;
		}
	return tot >= w;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> w >> l;
	for (int i = 0; i < n; i++)
		cin >> h[i] >> r[i];
	int ans = 0;
	for (long long i = 1ll << 31; i; i >>= 1)
		if (!check(ans | i))
			ans |= i;
	if (check(ans))
		cout << ans << endl;
	else
		cout << ans + 1 << endl;
	return 0;
}

