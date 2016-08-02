#include <bits/stdc++.h>
using namespace std;
typedef unsigned int in;
in m;
int n;
in seg_ans[100 + 5];
in pow_[100 + 5];
in calc(int tn)
{
	int tp = 1;
	in ans = 0;
	for (; tp * 2 <= tn; tp++)
		ans += seg_ans[tp] * pow_[tn - tp * 2];
	return ans;
}
int main()
{
	scanf("%d%u", &n, &m);
	pow_[0] = 1;
	for (int i = 1; i <= n; i++)
		pow_[i] = pow_[i - 1] * m;
	seg_ans[1] = m;
	for (int i = 2; i <= n; i++)
		if (i & 1)
			seg_ans[i] = seg_ans[i - 1] * m;
		else if (i >= 10 && (i / 2) % 2 == 1)
		{
			int ti = i / 2;
			int ca = 0;
			seg_ans[i] = seg_ans[i - 1] * m - seg_ans[i / 2] + seg_ans[(i / 2 - 1) / 2];
		} else {
			seg_ans[i] = seg_ans[i - 1] * m - seg_ans[i / 2];
		}
	in ans = 0;
	for (int i = 1; i <= n; i++)
	{
		cerr << i << ' ' << seg_ans[i] << endl;
		ans += seg_ans[i];
	}
	printf("%u\n", ans);
	return 0;
}
