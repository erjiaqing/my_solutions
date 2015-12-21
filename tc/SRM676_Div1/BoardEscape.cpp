#include <bits/stdc++.h>
using namespace std;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0,-1, 0};
typedef pair<int, int> pii;
#define x first
#define y second

#define able( _x , _y ) ( ( ( _x ) >= 0 ) && ( ( _x ) < ( _y )) )

int gr[55][55][2505];
struct BoardEscape {
	string findWinner(vector <string> s, int k) {
		int r = s.size();
		int c = s[0].size();
		for (int i = 1; i < 2505; i++) {
			for (int x = 0; x < r; x++) {
				for (int y = 0; y < c; y++) {
					if (s[x][y] == 'E') {gr[x][y][i] = 0;continue;}
					if (s[x][y] == '#') continue;
					bool mex[6] = {0, 0, 0, 0, 0, 0};
					for (int d = 0; d < 4; d++) {
						if (able(x + dx[d], r) && able(y + dy[d], c)) {
							if (s[x + dx[d]][y + dy[d]] == '#') continue;
							mex[gr[x + dx[d]][y + dy[d]][i - 1]] = true;
						}
					}
					while (mex[gr[x][y][i]]) gr[x][y][i]++;
				}
			}
		}
		int ans = 0;
		if (k > 2500) k = 2400 + k % 2;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				if (s[i][j] == 'T')
					ans ^= gr[i][j][k];
		return ans ? "Alice" : "Bob";
	}
};
