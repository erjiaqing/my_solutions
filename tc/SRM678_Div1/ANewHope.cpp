class ANewHope {
public:
	int count(vector<int> firstWeek, vector<int> lastWeek, int D) {
		int n = firstWeek.size();
		int maxDelta = n - D, ans = 1;
		for (int x = 0; x < n; x++)
			for (int y = 0; y < x; y++)
				if (firstWeek[x] == lastWeek[y])
					ans = max(ans, (x - y + maxDelta - 1) / maxDelta + 1);
		return ans;
	}
};
