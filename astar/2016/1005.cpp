#include <iostream>
using namespace std;
long long get_cnt(long long num)
{
	int cnt = 0;
	long long tnum = 0;
	//bool rol[64] = 0;
	int cur = 0;
	long long ans = 0;
	int last = 0;
	if (num == 0) return 0;
	for (int i = 60; i >= 0; i--)
	{
		long long tp = (tnum | (1ll << i));
		//if (i < 10)
		//	cerr << tp << endl;
		if (num < tp)
		{
			last = 1;
		} else if (num > tp)
		{
			ans += (1ll << i) / 2 + last;
			//cerr << "add " << (1ll << i) / 2 << endl;
			tnum |= (1ll << i);
			last = 0;
		} else {
			ans += (1ll << i) / 2;
			break;
		}
	}
	ans += last;
	return ans;
}
int main()
{
	int t;
	long long l, r;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lld%lld", &l, &r);
		printf("%lld\n", get_cnt(r) - get_cnt(l - 1));
	}
	return 0;
}
