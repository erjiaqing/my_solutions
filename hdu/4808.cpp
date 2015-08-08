#include <bits/stdc++.h>
using namespace std;
const double PI = 3.1415926535897932;
const int maxn = 200000 + 5;
double p[maxn];
int main()
{
	p[0] = 0;
	p[1] = 0.5;
	p[2] = 4.0 / (PI * 3.0);
	for (int i = 3 ; i < maxn ; i++)
		p[i] = p[i - 2] * i / (i + 1);
	int n;
	double r;
	while (~scanf("%d%lf" , &n , &r))
		printf("%.12f\n" , p[n] * r);
	return 0;
}
