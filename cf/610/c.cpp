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

int ans[1024][1024];

void check(int lim)
{
	for (int i = 0; i < lim; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int an = 0;
			for (int k = 0; k < lim; k++)
			{
				an += ans[i][k] * ans[j][k];
			}
			if (an != 0)
				cerr << "X\n";
		}
	}
}

int main() // The true main()
{
	ios::sync_with_stdio(0);
	ans[0][0] = 1;
	int cur = 1;
	for (int i = 1; i <= 9; i++)
	{
		int ncur = cur * 2;
		for (int j = 0; j < cur; j++)
			for (int k = cur; k < ncur; k++)
				ans[j][k] = -ans[j][ncur - k - 1];
		for (int j = cur; j < ncur; j++)
		{
			for (int k = 0; k < cur; k++)
				ans[j][k] = ans[j - cur][k];
			for (int k = cur; k < ncur; k++)
				ans[j][k] = ans[j][ncur - k - 1];
		}
		cur = ncur;
	}
	int n;
	cin >> n;
	int lim = (1 << n);
	for (int i = 0; i < lim; i++)
	{
		for (int j = 0; j < lim; j++)
			cout << ((ans[i][j] == -1) ? '*' : '+');
		cout << "\n";
	}
	check(lim);
	return 0;
}


// END OF NORMAL PROGRAM

}

int main() // The fake main()
{
	return sol::main();
}
