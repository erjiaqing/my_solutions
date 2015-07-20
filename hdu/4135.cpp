#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 100000 + 5;
int pr[maxn] , pt[maxn] , ifp[maxn] , tp;
long long get(long long x)
{
	if (x == 0) return x;
	long long ret = 0;
	int tot = (1 << tp);
	for (int i = 1 ; i < tot ; i++)
	{
		long long ta = 1;
		int fl = -1;
		for (int j = 0 ; j < tp ; j++)
		{
			if (i & (1 << j))
			{
				fl = -fl;
				ta *= pr[j];
			}
		}
		ret += fl * (x / ta);
	}
	return x - ret;
}
void work(int c)
{
	long long a , b , n;
	tp = 0;
	cin >> a >> b >> n;
	for (int i = 2 ; i * i <= n ; i++)
	{
		if (n % i == 0)
		{
			while (n % i == 0)
				n /= i;
			pr[tp++] = i;
		}
	}
	if (n != 1)
		pr[tp++] = n;
	cout << "Case #" << c << ": "<< get(b) - get(a - 1) << endl;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	for (int i = 1 ; i <= t ; i++)
		work(i);
	return 0;
}
