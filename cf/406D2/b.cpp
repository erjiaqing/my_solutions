#include <bits/stdc++.h>
using namespace std;

int chk[20000 + 5];

int main()
{
	ios::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	bool rdes = false;
	memset(chk, -1, sizeof chk);
	for (int i = 0; i < m; i++)
	{
		int k;
		cin >> k;
		bool des = true;
		for (int j = 0; j < k; j++)
		{
			int t;
			cin >> t;
			if (t < 0)
				if (chk[-t] == i) des = false;
			if (t > 0)
				if (chk[t + 10000] == i) des = false;
			chk[t < 0 ? -t + 10000 : t] = i;
		}
		rdes = rdes || des;
	}
	if (rdes)
		cout << "YES\n";
	else
		cout << "NO\n";
	return 0;
}
