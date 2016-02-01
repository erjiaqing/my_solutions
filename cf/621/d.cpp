#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;
double eps = 1e-10;
int main() {
	string ans = "";
	double a = -9999999;
	double x, y, z;
	cin >> x >> y >> z;
	if (x > 1 + eps && y > 1 + eps && z > 1 + eps) {
		if (z * log(y) + log(log(x)) > a + eps)
			a = z * log(y) + log(log(x)), ans = "x^y^z", cerr <<__LINE__ << endl;
		if (y * log(z) + log(log(x)) > a + eps)
			a = y * log(z) + log(log(x)), ans = "x^z^y", cerr <<__LINE__ << endl;
		//--
		if (z * log(x) + log(log(y)) > a + eps)
			a = z * log(x) + log(log(y)), ans = "y^x^z", cerr <<__LINE__ << endl;
		if (x * log(z) + log(log(y)) > a + eps)
			a = x * log(z) + log(log(y)), ans = "y^z^x", cerr <<__LINE__ << endl;
		//--
		if (y * log(x) + log(log(z)) > a + eps)
			a = y * log(x) + log(log(z)), ans = "z^x^y", cerr <<__LINE__ << endl;
		if (x * log(y) + log(log(z)) > a + eps)
			a = x * log(y) + log(log(z)), ans = "z^y^x", cerr <<__LINE__ << endl;
		if (log(log(x)) + log(y) + log(z) > a + eps)
			a = log(log(x)) + log(y) + log(z), ans = "(x^y)^z", cerr <<__LINE__ << endl;
		if (log(log(y)) + log(x) + log(z) > a + eps)
			a = log(log(y)) + log(x) + log(z), ans = "(y^x)^z", cerr <<__LINE__ << endl;
		if (log(log(z)) + log(y) + log(x) > a + eps)
			a = log(log(z)) + log(y) + log(x), ans = "(z^x)^y", cerr <<__LINE__ << endl;
	} else if (x <= 1 && y <= 1 && z <= 1) {
		if (pow(x, pow(y, z)) > a + eps) {a = pow(x, pow(y, z)), ans = "x^y^z";}
		if (pow(x, pow(z, y)) > a + eps) {a = pow(x, pow(z, y)), ans = "x^z^y";}
		if (pow(y, pow(x, z)) > a + eps) {a = pow(y, pow(x, z)), ans = "y^x^z";}
		if (pow(y, pow(z, x)) > a + eps) {a = pow(y, pow(z, x)), ans = "x^z^x";}
		if (pow(z, pow(x, y)) > a + eps) {a = pow(z, pow(x, y)), ans = "z^x^y";}
		if (pow(z, pow(y, x)) > a + eps) {a = pow(z, pow(y, x)), ans = "z^y^x";}
		if (pow(pow(x, y), z) > a + eps) {a = pow(pow(x, y), z), ans = "(x^y)^z";}
		if (pow(pow(y, x), z) > a + eps) {a = pow(pow(y, x), z), ans = "(y^x)^z";}
		if (pow(pow(z, x), y) > a + eps) {a = pow(pow(z, x), y), ans = "(z^x)^y";}
	} else if (x <= 1) {
		if (pow(x, z) * log(y) > a + eps) a = pow(x, z) * log(y), ans = "y^x^z";
		if (pow(z, x) * log(y) > a + eps) a = pow(z, x) * log(y), ans = "y^z^x";
		if (pow(x, y) * log(z) > a + eps) a = pow(x, y) * log(z), ans = "z^x^y";
		if (pow(y, x) * log(z) > a + eps) a = pow(y, x) * log(z), ans = "z^y^x";
		if (x * z * log(y) > a + eps) a = x * z * log(y), ans = "(y^x)^z";
		if (x * y * log(z) > a + eps) a = x * y * log(z), ans = "(z^x)^y";
	} else if (y <= 1) {
		if (pow(y, z) * log(x) > a + eps) a = pow(y, z) * log(x), ans = "x^y^z";
		if (pow(z, y) * log(x) > a + eps) a = pow(z, y) * log(x), ans = "x^z^y";
		if (pow(x, y) * log(z) > a + eps) a = pow(x, y) * log(z), ans = "z^x^y";
		if (pow(y, x) * log(z) > a + eps) a = pow(y, x) * log(z), ans = "z^y^x";
		if (y * z * log(x) > a + eps) a = y * z * log(x), ans = "(x^y)^z";
		if (x * y * log(z) > a + eps) a = x * y * log(z), ans = "(z^x)^y";
	} else if (z <= 1) {
		if (pow(y, z) * log(x) > a + eps) a = pow(y, z) * log(x), ans = "x^y^z";
		if (pow(z, y) * log(x) > a + eps) a = pow(z, y) * log(x), ans = "x^z^y";
		if (pow(x, z) * log(y) > a + eps) a = pow(x, z) * log(y), ans = "y^x^z";
		if (pow(z, x) * log(y) > a + eps) a = pow(z, x) * log(y), ans = "y^z^x";
		if (z * y * log(x) > a + eps) a = z * y * log(x), ans = "(x^y)^z";
		if (x * z * log(y) > a + eps) a = x * z * log(y), ans = "(y^x)^z";
	}
	cout << ans << endl;
	return 0;
}
