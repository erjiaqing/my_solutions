#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

#define LS( _x ) ( ( _x ) << 1 )
#define RS( _x ) ( ( _x ) << 1 | 1 )
#define LOWBIT( _x ) ( ( _x ) & ( - ( _x ) ) )
#define pb push_back
#define x first
#define y second
#define mp make_pair

namespace sol {

// BEBIN OF NORMAL PROGRAM
char s1[1200], s2[1200];
int p[1200], q[1200];
int s[1200][2][2];
int ps = 0;
int sz[3600];
int ans = 0;

void proc(char *s, int *m, int n)
{
	int cnt = 0;
	for (int i = 0; i <= n; i++)
	{
		if (s[i] == 'X')
		{
			ans += (cnt != 0);
			cerr << ps + 1;
			int j = i - 1;
			ps++;
			while (j >= 0 && s[j] == '.')
				m[j--] = ps;
			sz[ps] = cnt;
			cnt = 0;
		}
		else
		{
			cerr << " ";
			cnt++;
		}
	}
	cerr << endl;
}

int main() // The true main()
{
	int t;
	char buf[256];
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		int n;
		ans = ps = 0;
		cin >> n;
		cin >> s1 >> s2;
		s1[n] = s2[n] = 'X';
		memset(p, 0, sizeof(p));
		memset(q, 0, sizeof(q));
		memset(s, 0, sizeof(s));
		memset(sz, 0, sizeof(sz));
		proc(s1, p, n);
		proc(s2, q, n);
		cerr << ans << endl;
		for (int j = 0; j <= n; j++)
		{
			if (sz[p[j]] == 1 && sz[q[j]] != 0)
			{
				cerr << "&" << q[j] << " " << p[j] << "\n";
				sz[p[j]] = sz[q[j]] = 0;
				ans--;
			} else if (sz[p[j]] != 0 && sz[q[j]] == 1)
			{
				cerr << " " << q[j] << " " << p[j] << "&\n";
				sz[p[j]] = sz[q[j]] = 0;
				ans--;
			}else
			cerr << " " << q[j] << " " << p[j] << "\n";
		}
		cerr << endl;
		sprintf(buf, "Case #%d: %d\n", i, ans);
		cout << buf;
	}
	return 0;
}


// END OF NORMAL PROGRAM

}

int main() // The fake main()
{
	ios::sync_with_stdio(0);
	return sol::main();
}

