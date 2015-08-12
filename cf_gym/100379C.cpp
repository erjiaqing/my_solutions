/*
 * CF GYM 100379 C
 * Author: EJQ
 */
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
const double eps = 1e-8;
int a , b , g0 , g1;
//--
double ea , eb , ec;
double edelta;
double e0 , e1 , p0 , p1;
int work()
{
	if (scanf("%d%d%d%d" , &a , &b , &g0 , &g1) != 4)
		return -1;
	ea = 1;
	eb = -a;
	ec = -b;
	if ((g0 == g1 && g0 == 0) || (a == 0 && b == 0))
		return 0 & printf("NO\n");
	if (b == 0 && a)
	{
		if (g1)
			return 0 & printf("YES\n%.12f\n" , a * 1.0);
		else
			return 0 & printf("NO\n");
	}
	if (a == 0 && b)
	{
		if (fabs(g1 * g1 - b * g0 * g0) < eps)
			return 0 & printf("YES\n%.12f\n" , sqrt(1.0 * b));
		else
			return 0 & printf("NO\n");
	}
	edelta = eb * eb - 4 * ea * ec; // b^2 - 4ac
	if (edelta < 0)
		return 0 & printf("NO\n");
	edelta = sqrt(edelta);
	e0 = (-eb + edelta) / 2;
	e1 = (-eb - edelta) / 2;
	p0 = (g1 - e1 * g0) / (e0 - e1);
	p1 = (e0 * g0 - g1) / (e0 - e1);

	double ratio = e0 / e1;
//	printf("%f %f\n" , e0 , e1);
	if (fabs(p0) < eps)
		return 0 & printf("YES\n%.12f\n" , e1);
	if (fabs(p1) < eps)
		return 0 & printf("YES\n%.12f\n" , e0);
	if (fabs(ratio) > 1)
		return 0 & printf("YES\n%.12f\n" , e0);
	else
		return 0 & printf("YES\n%.12f\n" , e1);
	return 0;
}
int main()
{
	while (~work());
	return 0;
}
