#include <bits/stdc++.h>
using namespace std;

const int maxn = 10;

double p[maxn];
int c[maxn];

int n;

double calc(int i)
{
	double lastprob = 0;
	double ans = 0;
	for (int k = 1; k <= 1000; k++)
	{
		double tprob = 1;
		for (int j = 0; j < n; j++)
		{
			if (j == i) continue;
			tprob *= pow(1 - pow(p[j], k), c[j]);
		}
		ans += (1-pow(1-pow(p[i], k),c[i])) * (tprob - lastprob);
		lastprob = tprob;
	}
	return ans;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d%lf", &c[i], &p[i]);
		if (n == 1) printf("1.000000");
		else for (int i = 0; i < n; i++) printf("%s%.6lf", i ? " " : "", calc(i));
		printf("\n");
	}
	return 0;
}
