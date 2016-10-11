#include <bits/stdc++.h>
using namespace std;

const int maxn = 95;

int a[maxn];
bool up, dn;
int main()
{
	up = dn = false;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	if (a[n] == 15) {
		puts("DOWN");
		return 0;
	} else if (a[n] == 0) {
		puts("UP");
		return 0;
	} else if (n == 1) {
		puts("-1");
		return 0;
	} else {
		puts(a[n] > a[n - 1] ? "UP" : "DOWN");
		return 0;
	}
	return 0;
}
