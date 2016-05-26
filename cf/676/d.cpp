#include <bits/stdc++.h>
using namespace std;

#define __EJQ_BEGIN namespace ejq{
#define __EJQ_END };
__EJQ_BEGIN

const int maxn = 1000 + 2;

struct nd{
	int x, y, l;
	nd(){}
	nd(int _x, int _y, int _l):
		x(_x), y(_y), l(_l){}
}que[maxn * maxn * 4];

char mp[maxn][maxn][4];
int ans[maxn][maxn][4];
int n, m;

char nxt[128];

bool can_go_down(char c)
{
	return (c == '+' || c == '|' || c == 'v' || c == 'L' || c == 'U' || c == 'R');
}

bool can_go_right(char c)
{
	return (c == '+' || c == '-' || c == '>' || c == 'L' || c == 'U' || c == 'D');
}

bool can_go_left(char n)
{
	return (n == '+' || n == '-' || n == '<' || n == 'R' || n == 'U' || n == 'D');
}

bool can_go_up(char n)
{
	return (n == '+' || n == '|' || n == '^' || n == 'L' || n == 'D' || n == 'R');
}

const int dx[] = {0, 1, 0, -1}; // - D - U
const int dy[] = {1, 0, -1, 0}; // R - L -

bool check_conn(char c, char n, int dir)
{
	if (dir == 0) // L -> R
		return can_go_right(c) && can_go_left(n);
	else if (dir == 1) // U -> D
		return can_go_down(c) && can_go_up(n);
	else if (dir == 2) // R -> L
		return can_go_left(c) && can_go_right(n);
	else if (dir == 3)
		return can_go_up(c) && can_go_down(n);
	return 0;
}

int main()
{
	ios::sync_with_stdio(0);
	nxt['+'] = '+';
	nxt['-'] = '|';
	nxt['|'] = '-';
	nxt['^'] = '>';
	nxt['>'] = 'v';
	nxt['v'] = '<';
	nxt['<'] = '^';
	nxt['L'] = 'U';
	nxt['R'] = 'D';
	nxt['U'] = 'R';
	nxt['D'] = 'L';
	nxt['*'] = '*';

	memset(ans, 0x3f, sizeof(ans));
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> mp[i][j][0];
			assert(mp[i][j][0] != '\n');
		}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 1; k < 4; k++)
				mp[i][j][k] = nxt[mp[i][j][k - 1]];

	int sx, sy;
	cin >> sx >> sy;
	ans[sx][sy][0] = 0;
	int qh, qt;
	que[qh = qt = 0] = nd(sx, sy, 0);
	while (qh <= qt)
	{
		nd cur = que[qh++];
		if (ans[cur.x][cur.y][(cur.l + 1) & 3] > ans[cur.x][cur.y][cur.l] + 1)
		{
			ans[cur.x][cur.y][(cur.l + 1) & 3] = ans[cur.x][cur.y][cur.l] + 1;
			que[++qt] = nd(cur.x, cur.y, (cur.l + 1) & 3);
		}
		for (int d = 0; d < 4; d++)
		{
			if (ans[cur.x + dx[d]][cur.y + dy[d]][cur.l] > ans[cur.x][cur.y][cur.l] + 1)
			{
				if (check_conn(mp[cur.x][cur.y][cur.l], 
							mp[cur.x + dx[d]][cur.y + dy[d]][cur.l],
							d))
				{
					ans[cur.x + dx[d]][cur.y + dy[d]][cur.l] = ans[cur.x][cur.y][cur.l] + 1;
					que[++qt] = nd(cur.x + dx[d], cur.y + dy[d], cur.l);
				}
			}
		}
	}
	cin >> sx >> sy;
	int an = 0x3f3f3f3f;
	for (int i = 0; i < 4; i++)
		an = min(an, ans[sx][sy][i]);
	cout << (an == 0x3f3f3f3f ? -1 : an) << endl;
	return 0;
}

__EJQ_END
int main()
{
	return ejq::main();
}

