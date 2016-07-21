#include <cstdio>
using namespace std;
long long sol()
{
	int n;
	long long odd, even;
	odd = even = 0;
	scanf("%d", &n);
	while (n--)
	{
		int t;
		scanf("%d", &t);
		if (t & 1) even += (t - 1) / 2;
		else even += t / 2;
		odd += (t & 1);
	}
	if (odd == 0) return even * 2;
	else
		return (even / odd) * 2 + 1;
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		printf("%lld\n", sol());
	return 0;
}
