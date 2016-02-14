#include <bits/stdc++.h>
using namespace std;
const int maxn = 5000 + 5, maxc = 2000 * 2000 + 5;
int a[maxn], n;
long long rn[maxn * 2 + 1], prn[maxn * 2 + 1];
long long ans = 0;
double r = 0;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	sort(&a[0], &a[n]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			rn[a[i] - a[j]]++;
	for (int i = 1; i <= maxn * 2; i++)
		prn[i] = prn[i - 1] + rn[i];
	r = prn[maxn * 2] * prn[maxn * 2] * prn[maxn * 2];
	for (int i = 0; i < maxn; i++)
		for (int j = 0; j < maxn; j++)
			ans += (prn[maxn * 2] - prn[i + j]) * rn[i] * rn[j];
	printf("%.10f\n", ans / r);
	return 0;
}
