#include <bits/stdc++.h>
using namespace std;
int main()
{
	string ans = "#Black&White";
	int n, m;
	char s[5], c;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int i = 1; i <= m; i++)
		{
			cin >> s;
			c = s[0];
			if (c == 'C' || c == 'M' || c == 'Y') ans = "#Color";
		}
	}
	cout << ans << endl;
	return 0;
}
