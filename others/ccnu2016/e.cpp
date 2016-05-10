#include <iostream>
using namespace std;
long long a, b, x, y, m;

long long check1(long long t) // Use skill every time possible
{
	if (t <= 1)
		return -1;
	if (t % y == 0)
		return (t / y) * a + (t / y - 1) * ((y - 1) * x + b) + (y - 1) * (x + b);
	else if (t % y != 1)
		return (t / y + 1) * a + (t / y) * ((y - 1) * x + b) + (t % y - 1) * (x + b);
	else
		return (t / y) * a + (t / y - 1) * ((y - 1) * x + b) + y * (x + b);
}

long long check2(long long t) // Use skill at last
{
	if (t > 1)
		return (x + b) * (t - 1) + a;
	return 0;
}

long long check3(long long t) // Never use skill
{
	return x * t;
}

void sol()
{
	long long t = 0;
	cin >> a >> b >> x >> y >> m;
	y++;
	for (long long i = 1ll << 30; i > 0; i >>= 1)
	{
		if (/*check0(t | i) < m && */check1(t | i) < m && check2(t | i) < m && check3(t | i) < m)
		{
			t |= i;
		}
	}
	//aerr << t << endl;
	if (/*check0(t) < m && */check1(t) < m && check2(t) < m && check3(t) < m)
		t++;
	cout << t << endl;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
		sol();
	return 0;
}
