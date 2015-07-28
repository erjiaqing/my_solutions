#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000 + 5;
int f[maxn];
int q[15][maxn];
bool book[maxn];
int p[maxn] , k = 0;
int calc(int x)
{
	int r = 0;
	int q = sqrt(x) + 0.5;
	for (int i = 0 ; i < k && p[i] <= q && p[i] <= x ; i++)
	{
		if (x % p[i] == 0)
			r++;
		while (x % p[i] == 0)
			x /= p[i];
	}
	if (x != 1)
		r++;
	return r;
}
int main()
{
	ios::sync_with_stdio(0);
	int Q = 0 , ql , qr;
	int Max = 0;
    for(int i=2; i < maxn; ++i)
	{
		if(!book[i])
            p[k++] = i;
        for(int j=0; (j < k) && (i * p[j] < maxn); ++j)
        {
            book[i * p[j]] = true;
			if(i % p[j] == 0) break;													}
	}
	for (int i = 2 ; i <= 1000000 ; i++)
	{
		f[i] = calc(i);
		if (f[i] == 6)
			q[1][i] = q[2][i] = q[3][i] = q[6][i] = 1;
		else if (f[i] == 4)
			q[1][i] = q[2][i] = q[4][i] = 1;
		else
			q[1][i] = q[f[i]][i] = 1;
	}
	for (int j = 1 ; j <= 7 ; j++)
		for (int i = 2 ; i <= 1000000 ; i++)
			q[j][i] += q[j][i - 1];
	cin >> Q;
	while (Q--)
	{
		cin >> ql >> qr;
		for (int a = 7 ; a >= 1 ; a--)
			if (q[a][qr] - q[a][ql - 1] > 1)
			{
				cout << a << endl;
				break;
			}
	}
	return 0;
}
