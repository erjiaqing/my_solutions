#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int k, a[10];
int mk[10][10];

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		bool flg = true;
		scanf("%d", &k);
		memset(mk, 0, sizeof(mk));
		for (int i = 0; i < k; i++) scanf("%d", &a[i]);
		if (k < 4) {puts("invalid");continue;}
		for (int i = 1; i < k; i++) {
			if (a[i] > 9 || a[i - 1] > 9 || a[i] == 0 || a[i - 1] == 0) {flg = false; break;}
			int r1 = (a[i - 1] - 1) / 3 + 1;
			int c1 = (a[i - 1] - 1) % 3 + 1;
			mk[r1][c1] = true;
			int r2 = (a[i] - 1) / 3 + 1;
			int c2 = (a[i] - 1) % 3 + 1;
			if ((r2 - r1 == 2 || r2 - r1 == -2) && (c2 - c1 == 2 || c2 - c1 == -2)) {
				flg = flg && mk[(r2 + r1) / 2][(c2 + c1) / 2];
			} else
			if ((r2 - r1 == 2 || r2 - r1 == -2) && (c2 - c1 == 0)) {
				flg = flg && mk[(r2 + r1) / 2][c2];
			} else
			if ((r2 - r1 == 0) && (c2 - c1 == 2 || c2 - c1 == -2)) {
				flg = flg && mk[r2][(c2 + c1) / 2];
			} else {
				if (mk[r2][c2]) flg = false;
				mk[r2][c2] = true;
			}
		}
		puts(flg ? "valid" : "invalid");
	}
	return 0;
}
