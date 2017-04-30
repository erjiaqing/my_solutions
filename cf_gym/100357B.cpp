#include <bits/stdc++.h>
using namespace std;

char ans[505][505];
int a[505], b[505];
int lastplace[505];
typedef pair<int, int> pii;
int main()
{
	int n, m, h;
	freopen("chip.in", "r", stdin);
	freopen("chip.out", "w", stdout);
	cin >> m >> n >> h;
	for (int i = 1; i <= m; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	vector<pii> place;
	memset(ans, '*', sizeof ans);
	memset(lastplace, -1, sizeof lastplace);
	for (int i = 1; i <= m; i++)
	{
		place.clear();
		for (int j = 1; j <= n; j++)
			place.push_back(pii(b[j], j));
		sort(place.begin(), place.end(), greater<pii>());
		vector<int> canplace;
		int need = n - a[i];
		for (int j = 1; j <= n; j++)
			if (lastplace[place[j - 1].second] != -1)
				need--;
		if (need < 0)
		{
			puts("inconsistent");
			return 0;
		}
		for (int j = 1; j <= n && need; j++)
		{
			int _j = place[j - 1].second;
			if (b[_j] && lastplace[_j] == -1)
			{
				need--;
				b[_j]--;
				canplace.push_back(_j);
				lastplace[_j] = i;
			}
		}
		if (need != 0)
		{
			puts("inconsistent");
			return 0;
		}
		for (int j = 1; j <= n; j++)
		{
			if (lastplace[j] != -1 && (lastplace[j] == i || lastplace[j] == i - h + 1))
				ans[i][j] = '+';
			else if (lastplace[j] != -1)
				ans[i][j] = '|';
		}
		for (int j = 1; j <= n; j++)
			if (lastplace[j] == i - h + 1)
				lastplace[j] = -1;
	}
	for (int i = 1; i <= n; i++)
		if (b[i] || lastplace[i] != -1)
		{
			puts("inconsistent");
			return 0;
		}
	for (int i = 1; i <= m; i++)
	{
		ans[i][n + 1] = 0;
		puts(&ans[i][1]);
	}
	return 0;
}
