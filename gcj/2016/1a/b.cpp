#include <bits/stdc++.h>
using namespace std;
int app[2501];
void sol(int c)
{
	int n, t;
	memset(app, 0, sizeof(app));
	cin >> n;
	for (int i = 0; i < n * 2 - 1; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> t;
			app[t] ^= 1;
		}
	cout << "Case #" << c << ":";
	for (int i = 1; i < 2501; i++)
		if (app[i])
			cout << " " << i;
	cout << endl;
}
int main()
{
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
		sol(i);
	return 0;
}
