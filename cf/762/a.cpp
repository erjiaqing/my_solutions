#include <bits/stdc++.h>
using namespace std;
vector<long long> factor;
long long n;
int k;
int main()
{
	cin >> n >> k;
	for (long long i = 1; i * i <= n; i++)
		if (n % i == 0) factor.push_back(i);
	long long en = factor[factor.size() - 1];
	if (en * en == n)
	{
		if (k > 2 * factor.size() - 1)
		{
			puts("-1");
			return 0;
		}
		if (k > factor.size())
		{
			cout << n / factor[2 * factor.size() - 1 - k] << endl;
		} else {
			cout << factor[k - 1] << endl;
		}
	} else {
		if (k > 2 * factor.size())
		{
			puts("-1");
			return 0;
		}
		if (k > factor.size())
		{
			cout << n / factor[2 * factor.size() - k] << endl;
		} else {
			cout << factor[k - 1] << endl;
		}
	}
	return 0;
}
