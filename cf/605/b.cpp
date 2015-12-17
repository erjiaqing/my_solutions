#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 5;
const int maxm = 100000 + 5;
struct edge{
	int id, w, sel;
	int u, v;
}e[maxm];
int n, m;
int maxconn = 1;
int curru = 2, currv = 2;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		e[i].id = i;
		cin >> e[i].w >> e[i].sel;
	}
	sort(&e[0], &e[m],
			[](const edge &a, const edge &b)
			{return a.w < b.w || (a.w == b.w && a.sel > b.sel);});
	for (int i = 0; i < m; i++)
	{
		if (e[i].sel)
		{
			maxconn++;
			e[i].u = maxconn;
			e[i].v = 1;
		} else {
			if (curru == currv)
			{
				currv ++;
				curru = 2;
			}
			if (currv > maxconn) {cout << "-1\n";return 0;}
			e[i].u = currv;
			e[i].v = curru;
			curru++;
		}
	}
	sort(&e[0], &e[m],
			[](const edge &a, const edge &b)
			{return a.id < b.id;});
	for (int i = 0; i < m; i++)
		cout << e[i].u << " " << e[i].v << "\n";
	return 0;
}
