#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, b, d;
	scanf("%d%d%d", &n, &b, &d);
	int total_size = 0, ans = 0;
	for (int i = 0; i < n; i++)
	{
		int ai;
		scanf("%d", &ai);
		if (ai > b) continue;
		total_size += ai;
		if (total_size > d) ans++, total_size = 0;
	}
	cout << ans << endl;
	return 0;
}
