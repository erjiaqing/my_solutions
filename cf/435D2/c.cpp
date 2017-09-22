#include <bits/stdc++.h>
using namespace std;
int arr[100000 + 5];
int main()
{
	int n, x;
	cin >> n >> x;
	if (n == 2 && x == 0)
	{
		cout << "NO\n";
		return 0;
	} else {
		cout << "YES\n";
	}
	if (n == 1) cout << x << endl;
	else
	{
		int cur = x;
		for (int i = 1; i < n - 1; i++)
		{
			cur ^= i;
			arr[i] = i;
		}
		arr[n - 1] = 131072;
		cur ^= 131072;
		for (int j = n - 2; j < 131072; j++)
		{
			cur ^= arr[n - 2];
			cur ^= j;
			arr[n - 2] = j;
			if (cur != 131072)
				break;
		}
		for (int i = 1; i < n; i++)
			cout << arr[i] << ' ';
		cout << cur << endl;
	}
	return 0;
}
