#include <bits/stdc++.h>
using namespace std;

#define hash asjkfahklfhdklf

char str[4005];
vector<long long> hs[4005];

int id[26];
long long hash[4005][4005];

const long long mod = 1284901411419061ll;
const int tt = 31;

int main()
{
//	freopen("pattern.in", "r", stdin);
//	freopen("pattern.out", "w", stdout);
	scanf("%s", str);
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		memset(id, 0, sizeof id);
		long long cur = 0;
		int cr = 0;
		for (int j = 0; i + j < len; j++)
		{
			int &tr = id[str[i + j] - 'a'];
			if (tr == 0) tr = ++cr;
			cur = (cur * tt + tr) % mod;
			hs[j].push_back(cur);
			hash[i][j] = cur;
		}
	}
	for (int j = 0; j < len; j++)
		sort(hs[j].begin(), hs[j].end());
	int ans = 0;
	int cnt = 1, tlen = 0;
	long long target = 0;
	for (int j = 0; j < len; j++)
	{
	hs[j].push_back(-1);
//	for (int i = 0; i < (int)hs.size(); i++) 
//		cerr << hs[i].first << ' ' << hs[i].second << endl;
	for (int i = 1; i < (int)hs[j].size(); i++)
	{
		if (hs[j][i] == hs[j][i - 1])
			cnt++;
		else
		{
			if (cnt * (j + 1) > ans)
			{
				tlen = j;
				ans = cnt * (j + 1);
				target = hs[j][i - 1];
			}
			cnt = 1;
		}
//		cerr << hs[i].first << ' ' << hs[i].second << ' ' << cnt << ' ' << ans << endl;
	}
	}
/*	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cerr << hash[i][j] << ' ';
		}
		cerr << endl;
	}
	cerr << ans << ' ' << target << ' ' << tlen << endl;*/
	for (int i = 0; i < len; i++)
		if (hash[i][tlen] == target)
		{
			str[i + tlen + 1] = 0;
			puts(&str[i]);
			return 0;
		}
	return 0;
}
