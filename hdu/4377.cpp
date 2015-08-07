#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 1000000 + 5;
int n , sn , ln , ans[maxn];
void work()
{
	int up , dn , ts;
	sn = sqrt(n);
	if (sn * sn < n) sn++;
	ln = n % sn;
	if (ln == 0)
		ln = sn;
	ts = ln;
	for (int i = ln , j = sn ; i < n ; i++ , j--)
	{
		ans[i] = ts + j;
//		fprintf(stderr , "%d %d\n" , ts , j);
		if (j == 1)
		{
			j = sn + 1;
			ts += sn;
		}
	}
	for (int i = 0 ; i < ln ; i++)
		ans[i] = ln - i;
	up = (n - ln) / sn + 1;
	dn = sn;
	fprintf(stderr , "%d %d\n" , up , dn);
	while (up < dn)
	{
		int t = ans[ln - 1];
		for (int i = ln - 1 ; i > 0 ; i--)
			ans[i] = ans[i - 1];
		ans[0] = t;
		up++;
	}
	for (int i = 0 ; i < n ; i++)
		printf("%d%c" , ans[i] , (i == n - 1) ? '\n' : ' ');
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
	{
		scanf("%d" , &n);
		work();
	}
	return 0;
}
