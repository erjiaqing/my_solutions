#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
const int maxa = 1000000 + 5;
int l[maxa] , r[maxa] , app[maxa];
int main()
{
	int n , a , ans = maxn , k = 0;
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1 ; i <= n ; i++)
	{
		cin >> a;
		if (!l[a]) l[a] = i;
		r[a] = i;
		app[a] ++;
	}
	for (int i = 1 ; i < maxa ; i++)
		if (l[i])
			if ((app[i] > app[k]) || ( app[i] == app[k] && r[i] - l[i] < ans) )
				ans = r[k = i] - l[i];
	cout << l[k] << " " << r[k] << endl;
	return 0;
}
