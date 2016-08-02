#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	int t;
	int d, b1, b2, b3, b4;
	cin >> t;
	int b[5], l[5], rev[5], bb[5];
	while (t--)
	{
		for (int i = 0; i < 5; i++)
		{
			cin >> d >> bb[1] >> bb[2] >> bb[3] >> bb[4];
			rev[bb[1]] = 1;rev[bb[2]] = 2;
			rev[bb[3]] = 3;rev[bb[4]] = 4;
			if (i == 0)
			{
				if (d == 1 || d == 2)
					b[i] = 2, l[i] = bb[2];
				else if (d == 3 || d == 4)
					b[i] = d, l[i] = bb[d];
			} else if (i == 1)
			{
				if (d == 1)
					b[i] = rev[4], l[i] = 4;
				else if (d == 2 || d == 4)
					b[i] = b[0], l[i] = bb[b[0]];
				else if (d == 3)
					b[i] = 1, l[i] = bb[1];
			} else if (i == 2)
			{
				if (d == 1)
					b[i] = rev[l[1]], l[i] = l[1];
				else if (d == 2)
					b[i] = rev[l[0]], l[i] = l[0];
				else if (d == 3)
					b[i] = 3, l[i] = bb[3];
				else if (d == 4)
					b[i] = rev[4], l[i] = 4;
			} else if (i == 3)
			{
				if (d == 1)
					b[i] = b[0], l[i] = bb[b[0]];
				else if (d == 2)
					b[i] = 1, l[i] = bb[1];
				else if (d == 3 || d == 4)
					b[i] = b[1], l[i] = bb[b[1]];
			} else if (i == 4)
			{
				if (d == 1 || d == 2)
					b[i] = rev[l[d - 1]], l[i] = l[d - 1];
				else if (d == 3)
					b[i] = rev[l[3]], l[i] = l[3];
				else if (d == 4)
					b[i] = rev[l[2]], l[i] = l[2];
			}
		}
		for (int i = 0; i < 5; i++)
			cout << b[i] << " " << l[i] << "\n";
	}
	return 0;
}

