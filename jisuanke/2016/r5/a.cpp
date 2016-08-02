#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
double l, rat, ans;
int n, k;
int main()
{
	scanf("%d%d%lf", &n, &k, &l);
	double deg = pi - 2 * pi / n;
	double deg2 = pi / n;
	rat = sin(deg) / (2 * sin(deg2));
	for (int i = 0; i < k; i++)
	{
		ans += (n - 1 + 0.5) * l;
		l *= rat;
	}
	ans += (n - 1) * l;
	printf("%.12f\n", ans);
	return 0;
}
