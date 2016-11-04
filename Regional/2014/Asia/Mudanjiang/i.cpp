#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int main()
{
	int t, n, v;
	char s[5];
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		double ans = 0, b = 2;
		scanf("%d%s", &n, s);
		if (s[0] == 'b') b = 2;
		else if (s[0] == 'n') b = exp(1);
		else if (s[0] == 'd') b = 10;
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &v);
			if (v)
				ans += v * log(v / 100.0) / (log(b) * 100);
		}
		printf("%.15f\n", -ans);
	}
}
