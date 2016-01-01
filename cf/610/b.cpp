// Happy new year!
//
// Why "good bye 2015" at Dec. 30 ? 
// I have classes at 8 am the next day!
// Sad story!
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


int main() // The true main()
{
	ios::sync_with_stdio(0);
	long long bg = 0, ed = 0, n;
	long long m = 1000000001;
	vector<long long> v;
	cin >> n;
	for (int j = 0; j < n; j++)
	{
		long long x;
		cin >> x;
		v.pb(x);
		if (x <= m)
		{
			m = x;
		}
	}
	for (int j = 0; j < n; j++)
	{
		v[j] -= m;
		v.pb(v[j]);
	}
	int ml = 0, cl = 0;
	for (int j = 0; j < v.size(); j++)
	{
		if (v[j])
		{
			cl++;
			ml = max(ml, cl);
		} else {
			cl = 0;
		}
	}
	cout << m * n + ml << endl;
	return 0;
}


// END OF NORMAL PROGRAM

}

int main() // The fake main()
{
	return sol::main();
}
