#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
char str[maxn];
int sss[maxn], ans1[maxn], ans2[maxn];
int len;
int l, r;
bool getAnswer(int _l, int _r) {
	memset(ans1, 0, sizeof(ans1));
	for (int i = 0; i < len; i++) sss[i] = str[i] - '0';
	l = _l;r = _r;
	if (l == 1) {
		if (sss[0] == 1) {
			sss[l] += 10;
			sss[r] += 10;
			sss[r - 1]--;
		} else
			return false;
	}
	for (; l <= r; l++, r--) {
		while (sss[l] < 0) sss[l] += 10;
		while (sss[r] < 0) {sss[r - 1]--;sss[r] += 10;}
		if (sss[l] == sss[r] + 10 || sss[l] == sss[r] + 11) {sss[r - 1]--;sss[r] += 10;}
		if (sss[l] == sss[r]) {
			ans1[r] = sss[l] / 2;
			ans1[l] = sss[l] - ans1[r];
			if (ans1[r] > 9 || ans1[l] > 9) return false;
			if (l == r) {if (sss[l] % 2 != 0) return false;}
		} else if (sss[l] == sss[r] + 1) {
			if (l == r || l == r - 1) return false;
			sss[l]--;
			ans1[r] = sss[r] / 2;
			ans1[l] = sss[r] - ans1[r];
			if (ans1[r] > 9 || ans1[l] > 9) return false;
			sss[l + 1] += 10;
		} else {
			return false;
		}
	}
	return ans1[_l] != 0;
}
int main() {
	ios::sync_with_stdio(0);
	cin >> str;
	len = strlen(str);
	if (getAnswer(0, len - 1)) {
		cerr << "Case1\n";
		for (int i = 0; i < len; i++) cout << ans1[i];
		cout << endl;
	} else if (len > 1 && getAnswer(1, len - 1)) {
		cerr << "Case2\n";
		for (int i = 1; i < len; i++) cout << ans1[i];
		cout << endl;
	} else {
		cerr << "No Ans\n";
		cout << "0\n";
	}
	return 0;
}
