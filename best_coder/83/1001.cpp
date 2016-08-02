#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
vector<long long> v;
int n, t, tv;
int mx;
void sol()
{
	mx = 0;
	cin >> n;
	while (n--)
	{
		cin >> tv;
		mx = max(mx, tv);
	}
	cout << mx << "\n";
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
		sol();
	return 0;
}
