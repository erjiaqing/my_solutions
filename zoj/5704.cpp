#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char map[125][125];
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		memset(map, 0, sizeof(map));
		for (int i = 4; i < n + 4; i++)
			cin >> (&map[i][4]);
		for (int i = 4; i < n + 4; i++)
			for (int j = 4; j < m + 4; j++)
			{
				if (map[i][j] == '/')
					map[i - 1][j + 1] = 'O';
				else if (map[i][j] == '|')
					map[i - 1][j] = 'O';
				else if (map[i][j] == '\\')
					map[i - 1][j - 1] = 'O';
				else if (map[i][j] == '(')
					map[i - 2][j + 1] = 'O';
				else if (map[i][j] == ')')
					map[i - 2][j - 1] = 'O';
			}
		int ans = 0;
		for (int i = 0; i < n + 4; i++)
			for (int j = 0; j < m + 10; j++)
				ans += (map[i][j] == 'O');
		cout << ans << "\n";
	}
	return 0;
}
