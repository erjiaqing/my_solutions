#include <bits/stdc++.h>
using namespace std;

#define __EJQ_BEGIN namespace ejq{
#define __EJQ_END };
__EJQ_BEGIN

const int maxn = 100000 + 2;
char s[maxn];
int n, k;

int check(char tar)
{
	int beg = 0, end = 0, tk = 0;
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		while (end < n && (tk + (s[end] != tar)) <= k)
		{
			tk += (s[end] != tar);
			end++;
		}
		//cerr << i << ' ' << end << endl;
		ans = max(ans, end - i);
		tk -= (s[i] != tar);
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> k;
	cin >> s;
	cout << max(check('a'), check('b')) << endl;
	return 0;
}

__EJQ_END
int main()
{
	return ejq::main();
}

