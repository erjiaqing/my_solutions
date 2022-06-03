#include <iostream>
using namespace std;
namespace sol{
const int maxn = 100000 + 5;
long long c[maxn];
long long c0[maxn], c1[maxn];
long long ans = 0;
long long sqr(long long x)
{
	return x * x;
}
int main()
{
	int t, n;
	long long a, b;
	long long round = 0;
	char buf[256];
	cin >> t;
	for (int i = 1; i <= t; i++) {
		ans = 0;
		cin >> n >> a >> b;
		for (int j = 1; j <= n; j++)
			cin >> c[j];
		c[n + 1] = 0;
		for (int j = 1; j <= n; j++)
		{
			c0[j] = c0[j - 1] + c[j];
			c1[j] = c0[j] + c[j + 1];
		}
		c1[0] = c0[1];
		round = c0[n];
		long long ra = round - a % round;
		long long la = a % round;
		long long rb = b % round;
		long long cn = (b - a - ra - rb) / round;
		long long total = b - a;
		//cerr << ra << " " << la << " " << rb << endl;
		//cerr << "CN=" << cn << endl;
		for (int j = 1; j <= n; j++) {
			ans += cn * c[j] * c[j];
			//cerr << 1.0 * cn * c[j] * c[j] / (total * 2) << endl;
		}
		//cerr << "CURANS=" << ans << endl;
		for (int j = 0; j < n; j++) {
			if (c1[j] >= la) {
				ans += ((c1[j] - max(la, c0[j])) + 2 * (max(la, c0[j]) - c0[j])) * (c1[j] - max(la, c0[j]));
				//cerr << 'a' << j + 1 << " " << 1.0 * ((c1[j] - max(la, c0[j])) / 2.0 + (max(la, c0[j]) - c0[j])) * (c1[j] - max(la, c0[j])) / total << endl;
			}
			if (c0[j] <= rb) {
				ans += sqr(min(c1[j], rb) - c0[j]);
				//cerr << 'b' << j + 1 << 1.0 * sqr(min(c1[j], rb) - c0[j]) / (total * 2) << endl;
			}
		}
		sprintf(buf, "Case #%d: %.9f\n", i, ans / (total * (double)(2.0)));
		cout << buf;
	}
	return 0;
}
}
int main()
{
	ios::sync_with_stdio(0);
	return sol::main();
}
