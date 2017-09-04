#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

struct DistinctGrid{
	int n, k;
	int getid(int x, int y)
	{
		return (x - 1) * n + y - 1;
	}
	vector<int> findGrid(int n, int k){
		int used = 1;
		this->n = n;
		vector<int> ret;
		for (int i = 0; i < n * n; i++) ret.push_back(0);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j < k; j++)
			{
				int yy = (i + j - 1) % n + 1;
				ret[getid(i, yy)] = ++used;
			}
		}
		return ret;
	}
};

int main()
{
	int n, k;
	while (~scanf("%d%d", &n, &k))
	{
		DistinctGrid sol;
		auto res = sol.findGrid(n, k);
		for (int i = 0; i < n * n; i += n)
		{
			for (int j = i; j < i + n; j++)
			{
				cout << res[j] << ' ';
			}
			cout << endl;
		}
	}
}
