#include <iostream>
using namespace std;
const int maxn = 100000 + 5;
int cal[maxn * 300];
int maxans = 0;
int ans[maxn];
int main()
{
	ios::sync_with_stdio(0);
	for (int i = 1 ; i <= 1586413 ; i++)
		for (int j = i ; j <= 1586413 ; j += i)
			cal[j]++;
	int curr = 1586413;
	for (int i = 100000 ; ~i ; i--)
	{
		ans[i] = cal[curr];
		curr -= cal[curr];
	}
	int n;
	cin >> n;
	for (int i = 0 ; i < n ; i++)
		cout << (i == 0 ? "" : " ") << ans[i];
	cout << "\n";
	return 0;
}
