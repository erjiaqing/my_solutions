#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
	{
		int a, w, ans = 0;
		cin >> a;
		ans += a;
		while (a--)
		{
			cin >> w;
			ans += w;
		}
		cout << ans << "\n";
	}
	return 0;
}
