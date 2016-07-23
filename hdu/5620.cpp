#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
unsigned long long fibo[maxn];
int main()
{
	int last = 0;
	fibo[0] = 1;fibo[1] = 2;
	for (int i = 2; fibo[i - 1] < (1000000000000000000ull); i++)
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	//for (int i = 0; fibo[i]; i++)
	//	cerr << fibo[i] << endl;
	for (last = 1; fibo[last] + fibo[last - 1] < 1000000000000000000ull; last++)
		fibo[last] += fibo[last - 1];
	int t;
	scanf("%d", &t);
	unsigned long long ret;
	while (t--)
	{
		scanf("%lld", &ret);
		printf("%d\n", int(upper_bound(&fibo[0], &fibo[last], ret) - fibo));
	}
	return 0;
}
