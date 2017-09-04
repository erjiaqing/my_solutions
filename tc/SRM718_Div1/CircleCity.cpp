#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 2000 + 5;
typedef pair<int, int> pii;
struct CircleCity{
	int pos[maxn * 2], n;
	int check(int beg, int len)
	{
		int used = 0;
		for (int i = beg; i < beg + n;)
		{
			int j = i;
			while (pos[j] - pos[i] <= len && j <= beg + n)
				j++;
			i = j;
			used++;
		}
		return used;
	}
	int check(int len)
	{
		int ans = maxn;
		for (int i = 0; i < n; i++) ans = min(ans, check(i, len));
		return ans;
	}
	int findMin(vector<int> dist, int k)
	{
		n = dist.size();
		pos[0] = 0;
		for (int i = 0; i < (int)dist.size(); i++) {
			pos[i + 1] = pos[i] + dist[i];
		}
		for (int i = 0; i < (int)dist.size(); i++) {
			pos[i + 1 + n] = pos[i + n] + dist[i];
		}
		int mxlen = pos[n];
		for (int i = (1ll << 30); i; i >>= 1)
			if (i <= mxlen && check(mxlen - i) <= k)
				mxlen -= i;
		return mxlen;
	}
};


int main()
{
	int n, k;
	while (~scanf("%d%d", &n, &k))
	{
		CircleCity sol;
		vector<int> dist;
		for (int i = 0; i < n; i++)
		{
			int d;
			scanf("%d", &d);
			dist.push_back(d);
		}
		cout << sol.findMin(dist, k) << endl;
	}
}
