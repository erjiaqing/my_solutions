#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

long long res[maxn];

bool outputnum(int lvl, long long cur)
{
//	cerr << lvl << ' ' << cur << endl;
	if (lvl == 1)
	{
		if (cur < 2) return false;
		res[lvl] = cur - 2;
		return true;
	}
	long long last = cur * cur;
	if (last % (lvl - 1)) return false;
	for (int i = 1; i < 10000; i++)
	{
		if ((lvl - 1) * i > last) return false;
		res[lvl] = (last - (lvl - 1) * i) / (lvl - 1);
		if (outputnum(lvl - 1, (lvl - 1) * i))
			return true;
	}
	return false;
}

int main()
{
	int n, lvl = 1;
	long long cur = 2;
	cin >> n;
	for (int i = 10000; i > 1; i--)
		if (outputnum(n + 1, (n + 1) * i))
			break;
	for (int i = 2; i <= n + 1; i++) cout << res[i] << endl;
	return 0;
}
