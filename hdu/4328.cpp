#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;

#define Map Map_asdjhw
#define Map2 Map2_fksalh
#define len len_asfjkh
#define left left_dajkss
#define right right_qwrkhj
#define sol sol_ajdlwr
#define sta sta_salkjw
#define top top_sklaw4

char Map[maxn][maxn], Map2[maxn][maxn];
int len[maxn][maxn];
int left[maxn][maxn], right[maxn][maxn];
int sta[maxn], top;
int sol(int n, int m) {
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (Map[i][j] == Map2[i][j]) len[i][j] = len[i - 1][j] + 1;
			else len[i][j] = 0;
	for (int i = 1; i <= n; i++) {
		sta[top = 1] = 0;
		for (int j = 1; j <= m; j++) {
			while (top && len[i][sta[top]] >= len[i][j]) top--;
			left[i][j] = top ? sta[top] + 1 : 1;
			sta[++top] = j;
		}
	}
	for (int i = 1; i <= n; i++) {
		sta[top = 1] = m + 1;
		for (int j = m; j >= 1; j--) {
			while (top && len[i][sta[top]] >= len[i][j]) top--;
			right[i][j] = top ? sta[top] - 1 : m;
			sta[++top] = j;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (len[i][j])
				ans = max(ans, (right[i][j] - left[i][j] + 1) + len[i][j]);
	return ans;
}
int main() {
	int t, m, n, ans = 0;
	scanf("%d", &t);
	for (int c = 0; c < t;) {
		ans = 0;
		memset(left, 0, sizeof(left));
		memset(right, 0, sizeof(right));
		memset(len, 0, sizeof(len));
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%s", &Map[i][1]);
		memset(Map2, 'B', sizeof(Map2));
		ans = max(ans, sol(n, m));
		memset(Map2, 'R', sizeof(Map2));
		ans = max(ans, sol(n, m));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				Map2[i][j] = (((i + j) % 2) ? 'B' : 'R');
		ans = max(ans, sol(n, m));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				Map2[i][j] = (((i + j) % 2) ? 'R' : 'B');
		ans = max(ans, sol(n, m));
		printf("Case #%d: %d\n", ++c, ans * 2);
	}
	return 0;
}
