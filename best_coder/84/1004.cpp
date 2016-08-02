#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 100000;
vector<int> prime;
bool pri[100000 + 5];

void init()
{
	for (int i = 2; i <= 100000; i++)
	{
		if (pri[i] == 0)
			prime.push_back(i);
		for (int j = 0; j < prime.size(); j++)
		{
			if (i * prime[j] > maxn) break;
			pri[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

void sol()
{
	int n, d, ans = 0;
	scanf("%d%d", &n, &d);
	for (int i = 0; i < prime.size(); i++)
	{
		if (d * prime[i] >= n) break;
		ans++;
		if (d % prime[i] == 0) break;
	}
	printf("%d\n", ans);
}

int main()
{
	init();
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
