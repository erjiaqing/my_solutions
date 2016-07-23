#include <bits/stdc++.h>
using namespace std;
int outnum[100 + 5];
string output(int n)
{
	string ret = "";
	for (int i = 0; i < n; i++)
		ret = char(outnum[i] + '0') + ret;
	return ret;
}
int main()
{
	int n, m;
	cin >> n >> m;
//	scanf("%d%d", &n, &m);
	if (m == 0 && n != 1)
	{
		puts("-1 -1");
		return 0;
	}
	if (m > n * 9)
	{
		puts("-1 -1");
		return 0;
	}
	//if (n == 1) cout << m << ' ' << m << endl;
	int m1, m2;
	m1 = m2 = m;
	for (int i = 0; i < n; i++)
	{
		outnum[i] = min(m1, 9);
		m1 -= outnum[i];
	}
	if (n > 1 && outnum[n - 1] == 0)
	{
		outnum[n - 1] = 1;
		for (int j = n - 2; j >= 0; j--)
			if (outnum[j])
			{
				outnum[j]--;
				break;
			}
	}
	string r1 = output(n);
	for (int i = n - 1; i >= 0; i--)
	{
		outnum[i] = min(m2, 9);
		m2 -= outnum[i];
	}
	string r2 = output(n);
	cout << r1 << ' ' << r2 << endl;
	return 0;
}
