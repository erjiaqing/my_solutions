#include <bits/stdc++.h>
using namespace std;
int cn[1000000 + 5];
int main()
{
	ios::sync_with_stdio(0);
	int n, h;
	cin >> n;
	for (int i = 0; i < n; i++)
		(cin >> h), cn[h]++;
	for (int i = 0; i < 1000000 + 2; i++)
		cn[i + 1] += cn[i];
	int ans = 0x7fffffff;
	for (int i = 0; i <= 1000000; i++)
		ans = min(ans, i + n - cn[i]);
	cout << ans << endl;
	return 0;
}
