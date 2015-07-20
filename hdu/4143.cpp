#include <bits/stdc++.h>
using namespace std;
int work(int n)
{
	int k = sqrt(n);
	for (int i = k ; i >= 1 ; i--)
		if ( n % i == 0)
			if ( ( ( i & 1 ) ^ ( ( n / i ) & 1 ) ) == 0 )
				if (n / i != i)
				return ( n / i - i ) / 2;
	return -1;
}
int main()
{
	int t , n;
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--)
	{
		cin >> n;
		cout << work(n) << endl;
	}
	return 0;
}
