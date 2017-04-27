#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;
typedef pair<double, double> pdd;
#define x first
#define y second
pdd a[maxn];
int n, p;

int main()
{
	cin >> n >> p;
	for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
	sort(&a[1], &a[n + 1], [](const pdd &a, const pdd &b){
			return a.y / a.x < b.y / b.x;
			});
	double cursuma = a[1].x, cursumb = a[1].y;
	for (int i = 2; i <= n; i++)
	{
		double curt = a[i].y / a[i].x;
		if (curt * cursuma - cursumb > curt * p)
		{
			printf("%.20f\n", cursumb / (cursuma - p));
			return 0;
		}
		cursuma += a[i].x;
		cursumb += a[i].y;
	}
	if (cursuma > p) printf("%.20f\n", cursumb / (cursuma - p));
	else puts("-1");
	return 0;
}
