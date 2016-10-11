#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a[3];
	int x, y;
	cin >> y >> x;
	a[0] = a[1] = a[2] = x;
	int ans = 0;
	while (a[0] != y || a[1] != y || a[2] != y)
	{
		sort(a, a + 3);
		a[0] = min(y, a[1] + a[2] - 1);
		ans++;
	}
	cout << ans << endl;
	return 0;
}
