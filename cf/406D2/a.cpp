#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	int ans = 0x7fffffff;
	for (int i = 0; i <= 1000; i++)
	{
		for (int j = 0; j <= 1000; j++)
		{
			if (b + i * a == d + j * c)
				ans = min(ans, b + i * a);
		}
	}
	cout << (ans == 0x7fffffff ? -1 : ans) << endl;
	return 0;
}
