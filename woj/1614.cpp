#include <iostream>
using namespace std;
int main()
{
	int t;
	long long m;
	cin >> t;
	while (t--)
	{
		cin >> m;
		if (m <= 0)
			cout << "Fzz\n";
		else
		{
			long long mm = m;
			if ((mm & (0x5555555555555555ll)) == 0)
				cout << "Cyy\n";
			else
				cout << "Fzz\n";
		}
	}
	return 0;
}
