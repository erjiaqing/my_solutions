#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
int n, m, t;
set<int> used;
vector<int> ans;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> t;
		used.insert(t);
	}
	int cur = 0;
	for (int i = 1; cur + i <= m; i++)
	{
		if (used.find(i) == used.end())
		{
			ans.push_back(i);
			used.insert(i);
			cur += i;
		}
	}
	cout << ans.size() << endl;
	for (int a : ans)
		cout << a << ' ';
	cout << endl;
	return 0;
}
