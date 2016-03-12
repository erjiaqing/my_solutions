#include <cstdio>
#include <cstring>
using namespace std;

const int maxl = 28;
char s[maxl];
int r[maxl];
int n;
int len[maxl];

int main() {
	scanf("%d", &n);
	while (n--) {
		scanf("%s", s);
		memset(len, 0, sizeof(len));
		for (int i = 0; i < 26; i++)
			r[i] = s[i] - 'A';
		for (int i = 0; i < 26; i++) {
			if (~r[i]) {
				int ln = 0, lp, p = i;
				while (~r[lp = p]) ln++, p = r[p], r[lp] = -1;
				len[ln]++;
			}
		}
		int cn = 0;
		for (int i = 0; i <= 26; i += 2) cn |= len[i];
		puts((cn & 1) ? "No" : "Yes");
	}
	return 0;
}
