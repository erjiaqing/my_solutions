#include <bits/stdc++.h>
using namespace std;

const int maxn = 55;

int flg[maxn], res[maxn];

string getname(int x)
{
	string ret = "S";
	while (x)
	{
		ret += char(x % 26 + 'a');
		x /= 26;
	}
	return ret;
}

void sol(int n, int k)
{
	int cnt = 0, lastyes = -1;
	res[0] = 0;
	for (int ti = 1; ti <= n - k; ti++)
		if (flg[ti] == 1) {cnt = ti;break;}
	for (int i = cnt; i <= n - k + 1; i++)
	{
//		cerr << i << ' ' << flg[i] << endl;
		if (flg[i] == 0)
		{
			res[i + k - 1] = res[i + k - 2];
			continue;
		}
		if (lastyes == -1 || lastyes + k <= i)
		{
			res[i] = res[i - 1];
			for (int j = 1; j < k; j++) res[i + j] = res[i + j - 1] + 1;
		}
		else
		{
			int diff = i - lastyes;
			int tr = lastyes + 1;
			for (int j = k - diff; j < k - 1; j++)
				res[i + j] = res[tr++];
			res[i + k - 1] = i + k - 1;
		}
		lastyes = i;
	}
}

int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n - k + 1; i++)
	{
		string buf;
		cin >> buf;
		flg[i] = (buf == "YES");
	}
	sol(n, k);
	for (int i = 1; i <= n; i++) cout << getname(res[i] + 1) << " \n"[i == n];
	return 0;
}
