#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 4000 + 1;
int n;
long long v[maxn], d[maxn], p[maxn];
int q[maxn];
int a[maxn], t;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		q[i] = 1;
		scanf("%d%d%d", &v[i], &d[i], &p[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		if (q[i])
		{
#ifdef LOCAL
			cerr << "IN " << i << endl;
#endif
			a[t++] = i;
			int decr = v[i];
			long long sdec = 0;
			for (int j = i + 1; j <= n; j++)
				if (q[j])
				{
					p[j] -= decr;
					if (decr == 0) break;
					decr--;
				}
			for (int j = i + 1; j <= n; j++)
			{
				if (q[j])
				{
					p[j] -= sdec;
#ifdef LOCAL
					cerr << "PROC " << j << " P=" << p[j] << endl;
#endif
					if (p[j] < 0)
					{
#ifdef LOCAL
						cerr << "RUN " << j << endl;
#endif
						sdec += d[j];
						q[j] = 0;
					}
				}
			}
		}
	}
	printf("%d", t);
	for (int i = 0; i < t; i++)
		printf("%c%d", i ? ' ' : '\n', a[i]);
	printf("\n");
	return 0;
}
