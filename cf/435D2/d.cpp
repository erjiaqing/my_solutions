#include <bits/stdc++.h>
using namespace std;

char buf[1024];

int n;

int finddigit(char c)
{
	int l = 1, r = n;
	int sumofc;
	memset(buf, c ^ 1, sizeof(char) * (n));
	cout << "? " << buf << endl;
	cout.flush();
	cin >> sumofc;
	int rr = n - sumofc;
	while (l < r)
	{
		int mid = (l + r) / 2;
		memset(buf, c ^ 1, sizeof(char) * (n));
		memset(buf, c, sizeof(char) * (mid));
		cout << "? " << buf << endl;
		cout.flush();
		int curr;
		cin >> curr;
		int p = n - mid;
		int tdiff = curr - rr + p;
		assert(tdiff % 2 == 0);
		tdiff /= 2;
		if (tdiff == sumofc)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}

int main()
{
	int t0, t1;
	cin >> n;
	memset(buf, '1', sizeof(char) * (n));
	cout << "? " << buf << endl;
	cout.flush();
	cin >> t0;
	buf[0] = '0';
	cout << "? " << buf << endl;
	cout.flush();
	cin >> t1;
	int ans0, ans1;
	ans0 = ans1 = 1;
	if (t0 > t1) ans1 = finddigit('1');
	else ans0 = finddigit('0');
	cout << "! " << ans0 << ' ' << ans1 << endl;
	cout.flush();
	return 0;
}
