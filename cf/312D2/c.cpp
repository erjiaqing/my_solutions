#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long h , n , ans = 0 , tmp = 0;
	bool flag = 1;
	scanf("%lld%lld" , &h , &n);
	n--;
	for (int i = (h - 1) ; i >= 0 ; i--)
	{
		if (tmp + (1ll << i) > n)
		{
			if (flag)
				ans += 1;
			else
				ans += (1ll << (i + 1));
			flag = 0;
		}
		else
		{
			if (flag)
				ans += (1ll << (i + 1));
			else
				ans += 1;
			tmp += (1ll << i);
			flag = 1;
		}
	}
	printf("%lld\n" , ans);
	return 0;
}
