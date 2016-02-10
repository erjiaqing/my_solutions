typedef pair<long long, pair<int, bool> > pii;
#define x first
#define y second
const int mod = 1000000007;
class LimitedMemorySeries2 {
public:
	inline long long getNext(long long x, long long a, long long b) {
		return ((x ^ a) + b) & ((1ll << 50) - 1);
	}
	inline long long getPrev(long long x, long long a, long long b) {
		return (((x - b) + (1ll << 50)) ^ a) & ((1ll << 50) - 1);
	}
	int getSum(int n, long long x0, long long a, long long b) {
		long long ret = 0;
		for (int i = 0; i < n; i++) {
			long long pre = getPrev(x0, a, b), nxt = getNext(x0, a, b);
			int j = 1;
			for (j = 1; i - j >= 0 && i + j < n; j++) {
				if (pre >= x0 || nxt >= x0) break;
				pre = getPrev(pre, a, b), nxt = getNext(nxt, a, b);
			}
			(ret += j - 1) %= mod;
			x0 = getNext(x0, a, b);
		}
		return ret;
	}
};

