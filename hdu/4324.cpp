#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		long long n;
		long long cnt = 0;
		char a[2002];
		scanf("%lld", &n);
		cnt = n * (n - 1) * (n - 2) / 6;
		for (int j = 0; j < n; j++) {
			scanf("%s", a);
			int rcnt = 0;
			for (int k = 0; k < n; k++)
				if (k != j && a[k] == '0')
					rcnt++;
			cnt -= rcnt * (rcnt - 1) / 2;
		}
		printf("Case #%d: %s", i, cnt ? "Yes\n" : "No\n");
	}
	return 0;
}
