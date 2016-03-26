#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
#include <map>
#include <utility>
#include <vector>
using namespace std;
#define x first
#define y second
typedef pair<int, pair<int, pair<int, int> > > tp1;
typedef pair<int, pair<int, int> > tp2;
vector<string> name;
map<int, int> cnt;
map<int, set<tp2> > dep;
map<long long, int> depa2bt;
set<tp1> off;
int main()
{
	int n;
	char st[15];
	scanf("%d", &n);
	int addq = 0;
	for (int i = 0; i < n; i++)
	{
		int t;
		int depa, k;
		scanf("%d", &t);
		if (t == 1)
		{
			int y, m, d, bt;
			scanf("%d", &depa);
			scanf("%s", st);
			scanf("%d:%d:%d", &d, &m, &y);
			bt = y * 10000 + m * 100 + d;
			k = ++cnt[depa];
			tp2 tr2 = make_pair(bt, make_pair(k, addq));
			tp1 tr1 = make_pair(bt, make_pair(depa, make_pair(k, addq)));
			depa2bt[k * 10000000000ll + depa] = bt;
			name.push_back(st);
			dep[depa].insert(tr2);
			off.insert(tr1);
			addq++;
		} else {
			scanf("%d%d", &depa, &k);
			int bt = depa2bt[k * 10000000000ll + depa];
			auto offleft = off.lower_bound(make_pair(bt, make_pair(depa, make_pair(k, 0))));
			off.erase(offleft);
			auto depaleft = dep[depa].lower_bound(make_pair(bt, make_pair(k, 0)));
			dep[depa].erase(depaleft);
		}
		int ans1 = -1, ans2 = -1;
		if (dep[depa].size())
		{
			auto depa1 = dep[depa].begin();
			ans1 = depa1->y.y;
		}
		if (off.size())
		{
			auto offl = off.begin();
			ans2 = offl->y.y.y;
		}
		printf("%s %s\n", (~ans2) ? name[ans2].c_str() : "Vacant", (~ans1) ? name[ans1].c_str() : "Vacant");
	}
	return 0;
}
