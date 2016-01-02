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

const int mod = 1000000007;
int n;
vector<int> e[55];
// BEBIN OF NORMAL PROGRAM

long long getinv(long long y)
{
	long long r = 1;
	int b = mod - 2;
	while (b)
	{
		if (b & 1) r = r * y % mod;
		y = y * y % mod;
		b >>= 1;
	}
	return r;
}

long long getfrac(long long x, long long y)
{
	return (x * getinv(y)) % mod;
}

struct mat {
	long long a[55][55];
	mat(){memset(a, 0, sizeof(a));}
friend mat operator * (const mat &a, const mat &b)
{
	mat r;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				(r.a[i][j] += (a.a[i][k] * b.a[k][j]) % mod) %= mod;
	return r;
}
};

int main() // The true main()
{
	int m;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		e[x].pb(y);//e[y].pb(x);
	}
	mat mt;
	for (int i = 1; i <= n; i++)
		for (vector<int>::iterator v = e[i].begin(); v != e[i].end(); v++)
			(mt.a[i][*v] += (getfrac(1, e[i].size()))) %= mod;
	int q;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		int u, k;
		cin >> u >> k;
		mat tm = mt;
		mat tr;
		for (int j = 1; j <= n; j++) tr.a[j][j] = 1;
		while (k)
		{
			if (k & 1) tr = tr * tm;
			tm = tm * tm;
			k >>= 1;
		}
		for (int i = 1; i <= n; i++)
			cout << tr.a[u][i] << " ";
		cout << endl;
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

