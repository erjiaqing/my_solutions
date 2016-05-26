#include <bits/stdc++.h>
using namespace std;
namespace ejq{
const int maxn = 100000 + 5;
int n, k, und, da0;
int a[maxn];
int add[maxn], minus[maxn];
char buf[10];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 0; i <= n; i++)
	{
		cin >> buf;
		if (buf[0] == '?')
			und++;
		else
		{
			if (i == 0)
				da0 = 1;
			sscanf(buf, "%d", &a[i]);
		}
	}
	if (k == 0)
	{
		if (a[0] == 0 && (da0 || (n - und + 1) % 2)) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	} else {
		if (und == 0) {
			if (k == 1 || k == -1)
			{
				long long t = 0;
				long long w = 1;
				for (int i = 0; i <= n; i++)
				{
					t += a[i] * w;
					w *= k;
				}
				if (t) {
					cout << "No\n";
				} else {
					cout << "Yes\n";
				}
			} else {
				int w = k;
				long long ww = 1;
				int sgn = (k > 0 ? 1 : -1);
				for (int i = 0; i <= n; i++)
				{
					if (a[i] * ww > 0)
					{
						add[i] += abs(a[i]);
					} else {
						minus[i] += abs(a[i]);
					}
					ww *= sgn;
				}
				k = abs(k);
				bool flg = 1;
				for (int i = 0; i <= n; i++)
				{
					add[i + 1] += add[i] / k;
					minus[i + 1] += minus[i] / k;
					add[i] %= k;
					minus[i] %= k;
					flg = (flg && (add[i] == minus[i]));
				}
				if (flg) {
					cout << "Yes\n";
				} else {
					cout << "No\n";
				}
			}
		} else if (n % 2) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
	return 0;
}
}

int main()
{
	return ejq::main();
}
