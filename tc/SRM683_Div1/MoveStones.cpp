class MoveStones {
public:
	long long get(vector<int> a, vector<int> b) {
		int n = a.size();
		for (int i = 0; i < n; i++)
			a[i] -= b[i];
		long long sum = 0;
		long long ans = 0x7fffffffffffffffll;
		for (int i = 0; i < n; i++) sum += a[i];
		if (sum != 0) return -1;
		for (int i = 0; i < n; i++) {
			long long tans = 0;
			long long tlst = 0;
			for (int j = 0; j < n; j++) {
				int ti = (i + j) % n;
				tlst += a[ti];
				tans += max(tlst, -tlst);
			}
			ans = min(ans, tans);
		}
		return ans;
	}
};
