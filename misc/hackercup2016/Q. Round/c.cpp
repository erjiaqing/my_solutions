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
long long pts[1000000 + 2];
long long pre[1000000 + 2];

int main() // The true main()
{
	int t;
	char buf[256];
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		int n;
		long long ans = 0;
		long long p;
		cin >> n >> p;
		for (int j = 1; j <= n; j++)
		{
			cin >> pts[j];
			pre[j] = pre[j - 1] + pts[j];
		}
		int cur = 0;
		for (int j = 1; j <= n; j++)
		{
			if (cur < j) cur = j;
			while (cur <= n && pre[cur] - pre[j - 1] <= p)
				cur++;
			ans += cur - j;
		}
		sprintf(buf, "Case #%d: %lld\n", i, ans);
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

