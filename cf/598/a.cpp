#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
	int t;
	long long a;
	long long ans;
	long long k;
	scanf("%d", &t);
	while (t--)
	{
		cin >> a;
		ans = a * (a + 1) / 2;
		k = 1;
		while (k <= a)
			k <<= 1;
		k = k - 1;
		k = k * 2;
		ans -= k;
		cout << ans << endl;
	}
}
