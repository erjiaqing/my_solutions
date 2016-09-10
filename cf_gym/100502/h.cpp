#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;

int ca, cb, n;

int a[maxn], b[maxn], da[maxn * 2], db[maxn * 2], nxt[maxn];

void prekmp() {
	int j = nxt[0] = -1;
	for (int i = 0; i < n;) {
		while ((~j) && db[i] != db[j]) j = nxt[j];
		nxt[++i] = ++j;
	}
}

int count()
{
	int ans = 0, j = 0;
	prekmp();
	for (int i = 0; i < n + n;) {
		while ((~j) && da[i] != db[j]) j = nxt[j];
		i++;j++;
		if (j >= n) {
			ans++;
			j = nxt[j];
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];
	sort(a, a + n);
	sort(b, b + n);
	for (int i = 1; i < n; i++)
		da[i] = a[i] - a[i - 1];
	da[0] = a[0] - a[n - 1] + 360000;
	for (int i = n; i < n + n; i++) da[i] = da[i - n];
//	for (int i = 0; i < n + n; i++) cerr << da[i] << ' ';
//	cerr << endl;
	for (int i = 1; i < n; i++)
		db[i] = b[i] - b[i - 1];
	db[0] = b[0] - b[n - 1] + 360000;
//	for (int i = 0; i < n; i++) cerr << db[i] << ' ';
//	cerr << endl;
	puts(count() ? "possible" : "impossible");
	return 0;
}
