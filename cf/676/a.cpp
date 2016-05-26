#include <bits/stdc++.h>
using namespace std;

#define __EJQ_BEGIN namespace ejq{
#define __EJQ_END };
__EJQ_BEGIN

const int maxn = 101;

int a[maxn], n;

int check()
{
	int mxpos = 0, mipos = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 1) mipos = i;
		else if (a[i] == n) mxpos = i;
	}
	return max(mipos - mxpos, mxpos - mipos);
}


int main()
{
	int ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			swap(a[i], a[j]);
			ans = max(ans, check());
			swap(a[i], a[j]);
		}
	cout << ans << endl;
	return 0;
}

__EJQ_END
int main()
{
	return ejq::main();
}

