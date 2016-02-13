class DoubleOrOneEasy {
public:
	int minimalSteps(int _a, int _b, int _newA, int _newB) {
		long long a(_a), b(_b), newA(_newA), newB(_newB);
		int ans = 0x7fffffff;
		int cnt = 0;
		while (a <= newA && b <= newB) {
			if (newA - a == newB - b) {
				int tmp = 0;
				long long rem = newA - a;
				for (int i = cnt; i >= 0; i--) {
					tmp += (rem >> i);
					rem &= ((1 << i) - 1);
				}
				ans = min(ans, tmp + cnt);
			}
			a *= 2;
			b *= 2;
			cnt++;
		}
		return ans == 0x7fffffff ? -1 : ans;
	}
};

