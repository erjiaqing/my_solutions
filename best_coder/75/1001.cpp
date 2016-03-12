#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int main() {
	int t, n, m;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		int ans = 0;
		while (n && m) {
			if (n > m) {
				ans += n / m;
				n %= m;
			} else {
				ans += m / n;
				m %= n;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
