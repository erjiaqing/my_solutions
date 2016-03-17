#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <cassert>
using namespace std;
const int maxn = 200000 + 5;
#define x first
#define y second
typedef pair<int, int> pib;
int arr[maxn];
int arb[maxn];
pib v[maxn];
int main()
{
	int n, m, sz = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
	for (int i = 0; i < m; i++) {
		int t, r;
		scanf("%d%d", &t, &r);
		while (sz && v[sz - 1].x <= r) {sz--;}
		v[sz++] = pib(r, t);
	}
	sort(&v[0], &v[sz], greater<pib>());
	if (v[0].y == 1) sort(&arr[1], &arr[v[0].x + 1]);
	else sort(&arr[1], &arr[v[0].x + 1], greater<int>());
	for (int i = 1; i <= n; i++) arb[i] = arr[i];
	int beg = 1, end = v[1].x;
	v[sz] = pib(0, 0);
	for (int i = 1; i < sz; i++)
		if (v[i].y == v[0].y)
			for (int j = v[i].x; j > v[i + 1].x; j--)
				arr[j] = arb[end--];
		else
			for (int j = v[i].x; j > v[i + 1].x; j--)
				arr[j] = arb[beg++];
	for (int i = 1; i <= n; i++) printf("%s%d", i == 1 ? "" : " ", arr[i]);
	printf("\n");
	return 0;
}
