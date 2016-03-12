#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 1000 + 5;

int p1[maxn], p2[maxn], *p, *_p;
int n, s, a, k;

int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
int pow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1) 
			(r *= a) %= n;
		b >>= 1;
		(a *= a) %= n;
	}
	return r;
}
void sim() {
	for (int i = 1; i < n; i++) _p[i] = p[p[i]];
	_p[n] = p[p[n]];
}

int main() {
	p = p1;
	_p = p2;
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for (a = 1; a < n; a++) if (pow(2, a) == 1) break;
	k = a - s;
	while (k < 0) k += a;
	for (int i = 0; i < k; i++) {
		sim();
		swap(p, _p);
	}
	for (int i = 1; i <= n; i++) printf("%d\n", p[i]);
	return 0;
}
