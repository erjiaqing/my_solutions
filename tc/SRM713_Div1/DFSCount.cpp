#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

typedef pair<int, long long> pll;

struct DFSCount{
	long long ans[1 << 14][15];
	int mat[1 << 14][15];
	int n;
	bool vis[1 << 14][15];
	vector<string> gg;
	pll dfs(int v, int c)
	{
		if (vis[v][c]) return pll(mat[v][c], ans[v][c]);
		vis[v][c] = 1;
		long long tans = 0;
		int tmatch = v;
		for (int i = 0; i < n; i++)
			if ((v & (1 << i)) == 0 && gg[c][i] == 'Y')
			{
				auto res = dfs(v | (1 << i), i);
				auto re2 = dfs(res.first, c);
				tans += res.second * re2.second;
				tmatch |= res.first | re2.first;
			}
//		cerr << v << ' ' << c << ' ' << tans << endl;
		return pll(mat[v][c] = tmatch, ans[v][c] = ((tans == 0) ? 1 : tans));
	}
	long long count(vector<string> G)
	{
		n = G.size();
		gg = G;
		memset(mat, 0, sizeof mat);
		memset(ans, 0, sizeof ans);
		memset(vis, 0, sizeof vis);
		long long ret = 0;
		for (int i = 0; i < n; i++)
			ret += dfs(1 << i, i).second;
		return ret;
	}
};

int main()
{
	DFSCount sol;/*
					{
					vector<string> G = 	
					{"NYY",
					"YNY",
					"YYN"};
					cout << sol.count(G) << endl;
					}*/
	{
		vector<string> G = {"NYNN",
			"YNYN",
			"NYNY",
			"NNYN"};
		cout << sol.count(G) << endl;
	}
}
