#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

int n, p;
double a[maxn], b[maxn];

bool check(double t)
{
	double charge = t * p;
	for (int i = 1; i <= n; i++)
	{
		charge -= max(0., a[i] * t - b[i]);
		if (charge < 0) return false;
	}
	return true;
}

int main()
{
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &a[i], &b[i]);
	double l = 0, r = 1e20;
	while ((r - l) / max(l + 1, 1.) > 1e-5)
	{
		double mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	if (l > 1e15) puts("-1");
	else printf("%.4f\n", l);
	return 0;
}
