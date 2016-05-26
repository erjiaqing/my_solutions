#include <bits/stdc++.h>
using namespace std;

#define __EJQ_BEGIN namespace ejq{
#define __EJQ_END };
__EJQ_BEGIN

int contain[12][12];

int main()
{
	int n, t;
	cin >> n >> t;
	for (int i = 0; i < t; i++)
	{
		contain[0][0] += 4096;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				if (contain[i][j] >= 4096)
				{
					int tr = contain[i][j] - 4096;
//					assert(tr % 2 == 0);
					contain[i][j] = 4096;
					contain[i + 1][j] += tr / 2;
					contain[i + 1][j + 1] += tr / 2;
				}
			}
		}
	}
	int ta = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i; j++)
			if (contain[i][j] >= 4096)
				ta++;
	cout << ta << endl;
	return 0;
}

__EJQ_END
int main()
{
	return ejq::main();
}

