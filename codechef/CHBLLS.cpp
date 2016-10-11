#include <iostream>
using namespace std;
int main()
{
	cout << "1\n3 1 2 2\n3 3 4 4\n";
	cout.flush();
	int t;
	cin >> t;
	switch(t)
	{
		case 1:
			cout << "2\n1\n";
			break;
		case 2:
			cout << "2\n2\n";
			break;
		case -1:
			cout << "2\n3\n";
			break;
		case -2:
			cout << "2\n4\n";
			break;
		case 0:
		default:
			cout << "2\n5\n"; 
	}
	cout.flush();
	return 0;
}
