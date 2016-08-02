#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	int t, a, b, c, d;
	cin >> t;
	while (t--)
	{
		cin >> a >> b >> c >> d;
		cout << c << " " << b + d << "\n";
		cout << a << " " << b + d << "\n";
	}
	return 0;
}
