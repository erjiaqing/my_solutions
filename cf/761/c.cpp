#include <bits/stdc++.h>
using namespace std;
int n, m;
char str[55][55];
long long a[55], b[55], c[55];
long long ans = 0x7fffffff;
int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> str[i];
	for (int i = 0; i < n; i++)
		a[i] = b[i] = c[i] = ans;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if ('0' <= str[i][j] && str[i][j] <= '9') a[i] = min((int)a[i], min(j, m - j));
			else if ('a' <= str[i][j] && str[i][j] <= 'z') b[i] = min((int)b[i], min(j, m - j));
			else c[i] = min((int)c[i], min(j, m - j));
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
			{
				if (i == j || j == k || i == k) continue;
				ans = min(ans, a[i] + b[j] + c[k]);
			}
	cout << ans << endl;
	return 0;
}
