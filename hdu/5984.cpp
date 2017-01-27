#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	while (n--)
	{
		double L, d;
		scanf("%lf%lf", &L, &d);
		if (L < d + 1e-8) puts("0.000000");
		else
			printf("%.6lf\n", 1 + log(L / d));
	}
	return 0;
}
