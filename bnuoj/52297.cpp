#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long a1, a2, a3;
	cin >> a1 >> a2 >> a3;
	if (a1 == 0)
	{
		long long res = a2;
		if (a2 && a2 < 2 && a3) {
			cout << 2 * a3 + 1 << endl;
		} else if (a2 && a3) {
			cout << a2 * 2 + 1 + (a3 - 1) * 3 << endl;
		} else {
			cout << max(a2, a3) << endl;
		}
	} else {
		if (a1 >= 2 || (a1 > 0 && a2 > 0))
			cout << a1 + a2 * 2 + a3 * 3 << endl;
		else
			cout << 2 * a3 + 1 << endl;
	}
	return 0;
}
