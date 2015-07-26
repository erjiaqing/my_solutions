#include <bits/stdc++.h>
using namespace std;
const int maxk = 25 + 5;
long long c[maxk][maxk];
long long ans[maxk][maxk];
long long frac(long long x)
{
	long long ret = 1;
	for (int i = 1 ; i <= x ; i++)
		ret *= i;
	return ret;
}
long long getans(int n , int k)
{
	long long ret = 0;
	if (k == 1)
		return frac(n - 1);
	for (int i = 2 ; i <= k ; i++)
		ret += c[k - 2][i - 2] * frac(i - 1) * frac(n - i);
	return ret;
}
int main()
{
	ios::sync_with_stdio(0);
	c[0][0] = 1;
	for (int i = 1 ; i < maxk ; i++)
	{
		c[i][0] = 1;
		for (int j = 1 ; j < maxk ; j++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	int a , b;
	for (int i = 1 ; i <= 20 ; i++)
		for (int j = 1 ; j <= i ; j++)
			ans[i][j] = getans(i , j);
	int n , c;
	cin >> n;
	while (n--)
	{
		cin >> c >> a >> b;
		cout << c << " " << ans[a][b] << endl;
	}
}

