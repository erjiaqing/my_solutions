#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long n;
	cin >> n;
	long long nn = n * n;
	long long a, b;
	if (nn % 2 == 0)
	{
		a = 2;
		b = nn / 2;
	} else
	{
		a = 1;
		b = nn;
	}
	if (nn == 1 || nn == 4)
		cout << -1 << endl;
	else
		cout << (b - a) / 2 << ' ' << (b + a) / 2 << endl;
	return 0;
}
