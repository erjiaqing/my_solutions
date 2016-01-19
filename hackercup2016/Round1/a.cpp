#include <iostream> // In MAC OS iostream ~= /bits/stdc++.h
using namespace std;
namespace sol {
const int maxn = 100000 +10;
int ar[maxn];
int main()
{
	int t, n, lst = 0;
	int ans = 0;
	char buf[256];
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		ans = 0;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> ar[j];
		lst = 1;
		ar[n] = 0;
		for (int j = 1; j <= n; j++)
		{
			//cerr << lst << endl;
			if (ar[j] <= ar[j - 1]) {
				ans += (4 - (lst % 4)) % 4;
				lst = 0;
			} else {
				int tp = (ar[j] - ar[j - 1] - 1) / 10;
				if (tp > ((4 - (lst % 4)) % 4)) {
					ans += (4 - (lst % 4)) % 4;
				    lst = 0;
				} else {
					ans += tp;
					lst += tp;
				}
			}
			lst++;
		}
		sprintf(buf, "Case #%d: %d\n", i, ans);
		cout << buf;
	}
	return 0;
}
}
int main()
{
	ios::sync_with_stdio(0);
	return sol::main();
}
