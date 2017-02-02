#include <bits/stdc++.h>
using namespace std;
long long mp[100000 + 5][3];
long long dp[2][64];
int n;
vector<int> nxt[64];

#define S(_a, _b, _c) (((_a) << 4) | ((_b) << 2) | ((_c)))

long long get_stat(int mask, int pos)
{
	switch (mask){
		case S(0,0,1):
			return mp[pos][2];
		case S(0,1,0):
			return mp[pos][1];
		case S(1,0,0):
			return mp[pos][0];
		case S(1,1,0):
			return mp[pos][0] + mp[pos][1];
		case S(0,1,1):
			return mp[pos][1] + mp[pos][2];
		default:
			return mp[pos][0] + mp[pos][1] + mp[pos][2];
	};
}

long long count(int s1, int s2)
{
	int mi = min(s1, s2);
	int mx = max(s1, s2);
	if (mi == S(0,0,3) && mx == S(0,0,3)) return S(0,0,1);
	if (mi == S(0,0,3) && mx == S(0,3,0)) return S(0,1,1);
	if (mi == S(0,3,0) && mx == S(0,3,0)) return S(0,1,0);
	if (mi == S(0,3,0) && mx == S(3,0,0)) return S(1,1,0);
	if (mi == S(3,0,0) && mx == S(3,0,0)) return S(1,0,0);
	return S(1,1,1);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < 3; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lld", &mp[j][i]);
	memset(dp, 0x80, sizeof dp);
	dp[0][S(3,0,0)] = 0;
	nxt[S(1,2,3)].insert(nxt[S(1,2,3)].begin(), {S(1,2,3), S(3,2,1), S(3,0,0), S(0,0,3)});
	nxt[S(2,1,3)].insert(nxt[S(2,1,3)].begin(), {S(2,1,3), S(0,0,3)});
	nxt[S(3,1,2)].insert(nxt[S(3,1,2)].begin(), {S(3,1,2), S(3,0,0)});
	nxt[S(3,2,1)].insert(nxt[S(3,2,1)].begin(), {S(3,2,1), S(1,2,3), S(3,0,0), S(0,0,3)});
	nxt[S(3,0,0)].insert(nxt[S(3,0,0)].begin(), {S(3,1,2), S(3,2,1), S(3,0,0), S(0,3,0), S(0,0,3)});
	nxt[S(0,3,0)].insert(nxt[S(0,3,0)].begin(), {S(3,0,0), S(0,3,0), S(0,0,3)});
	nxt[S(0,0,3)].insert(nxt[S(0,0,3)].begin(), {S(1,2,3), S(2,1,3), S(3,0,0), S(0,3,0), S(0,0,3)});
	for (int i = 1; i <= n; i++)
	{
		memset(dp[i & 1], 0x80, (sizeof(long long)) * 64);
		for (int j = 0; j < 64; j++)
			for (int nx : nxt[j])
				dp[i & 1][nx] = max(dp[i & 1][nx], dp[(i & 1) ^ 1][j] + get_stat(count(j, nx), i));
	}
	cout << dp[n & 1][S(0,0,3)] << endl;
	return 0;
}
