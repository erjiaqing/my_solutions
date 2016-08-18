#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

double l;

const double f1(const double x)
{
	return l - sqrt(l * l - x * x);
}

const double f2(const double x)
{
	return l / 2 - sqrt(l * l / 4 - (x - l / 2) * (x - l / 2));
}

const double f(double x)
{
	return min(f1(x), f2(x));
}

double romberg(double a, double b, double eps = 1e-10)
{
	vector<double> t;
	double h = b - a, last, curr;
	int k = 1, i = 1;
	t.push_back(h * (f(a) + f(b)) / 2);
	do{
		last = t.back();
		curr = 0;
		double x = a + h / 2;
		for (int j = 0; j < k; j++) {
			curr += f(x);
			x += h;
		}
		curr = (t[0] + h * curr) / 2;
		double k1 = 4.0 / 3.0, k2 = 1.0 / 3.0;
		for (int j = 0; j < i; j++) {
			double temp = k1 * curr - k2 * t[j];
			t[j] = curr;
			curr = temp;
			k2 /= 4 * k1 - k2;
			k1 = k2 + 1;
		}
		t.push_back(curr);
		k *= 2;
		h /= 2;
		i++;
	}while (fabs(last - curr) > eps);
	return t.back();
}

double sol()
{
	scanf("%lf", &l);
	double A = romberg(0, l / 2, 1e-8) * 4;
	double B = PI * l * l / 2 - l * l;
	double C = (l * l - PI * l * l / 4) / 2;
	return l * l - A - B - C;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		printf("%.2f\n", sol());
	return 0;
}
