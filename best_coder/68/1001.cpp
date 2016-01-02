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

const int maxn = 100000 + 10;
int f[maxn];
int te = 0;
int sz[maxn];
int find(int u)
{
	if (f[u] != u)
		return f[u] = find(f[u]);
	return f[u];
}
void uni(int u, int v)
{
	int fu = find(u), fv = find(v);
	if (fu != fv)
	{
		sz[fv] += sz[fu];
		f[fu] = f[fv];
	}
}
int main() // The true main()
{
	int t;
	int u, v, w;
	cin >> t;
	while (t--)
	{
		int nd;
		te = 0;
		cin >> nd;
		for (int i = 1; i <= nd; i++)
		{
			f[i] = i;
			sz[i] = 1;
		}
		int tn = nd;
		int ans = 0;
		for (int i = 1; i < tn; i++)
		{
			cin >> u >> v >> w;
			if (!w)
				uni(u, v);
		}
		for (int i = 1; i <= tn; i++)
			ans ^= sz[i];
		cout << ans << endl;
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

