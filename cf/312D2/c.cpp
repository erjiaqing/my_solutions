#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
int n , ans;
unsigned int a[maxn] , aa[maxn] , avol = 0;
int check(int vol)
{
	int ret = 0;
	for (int i = 0 ; i < n ; i++)
	{
		int tv = vol , ta = a[i] , bmv = 0;
		while (tv > ta)
		{
			tv >>= 1;
			bmv++;
		}
		while (ta >= tv * 2)
		{
			ta >>= 1;
			bmv++;
		}
		while (ta != tv)
		{
			ta >>= 1;
			tv >>= 1;
			bmv += 2;
		}
		ret += bmv;
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 0 ; i < n ; i++)
	{
		cin >> a[i];
		aa[i] = a[i];
		while (aa[i] < (1 << 20)) aa[i] <<= 1;
	}
	avol = (1 << 22) - 1;
	for (int i = 0 ; i < 23 ; i++)
	{
		bool flag = true;
		avol = ((avol >> i) << i);
		for (int j = 1 ; j < n ; j++)
		{
			if ((aa[j] & avol) != (aa[j - 1] & avol))
			{
				flag = false;
				break;
			}
		}
		if (flag)
			break;
	}
	avol = avol & aa[0];
	int tans = 0x7fffffff;
	for (int i = 0 ; i <=20 ; i++)
		tans = min(tans , check(avol >> i));
	cout << tans << endl;
	return 0;
}
