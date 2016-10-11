#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
int n;
int lft, rit, dir;
typedef pair<int, int> pii;
vector<pii> p;
#define x first
#define y second
int d(pii a, pii b, pii c)
{
	int r = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return r < 0 ? -1 : 1;
}
int main()
{
	int x, y;
	ios::sync_with_stdio(0);
	cin >> n;
	cin >> x >> y;
	p.push_back(pii(x, y));
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		p.push_back(pii(x, y));
	}
	p.push_back(p[1]);
	for (int i = 1; i <= n; i++)
		if (d(p[i - 1], p[i], p[i + 1]) == 1)
		{
			lft++;
			dir++;
		} else {
			rit++;
			dir--;
		}
	if (dir == 4)
		cout << rit << endl;
	else if (dir == -4)
		cout << lft << endl;
	return 0;
}
