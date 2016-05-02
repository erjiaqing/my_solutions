#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n;
char buf[111];
char ans[111], tans[111];
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", buf);
		int yr = strlen(buf), tl = 0;
		for (int i = 4; i < yr; i++)
			tans[tl++] = buf[i];
		tans[tl] = 0;
		long long beg = 0, end = 0, e10 = 1;
		yr -= 4;
		while (yr--)
		{
			beg += e10;
			e10 *= 10;
			end += e10;
		}
		beg--;
		beg += 1989;end += 1989;
		//cerr << beg << ' ' << end << endl;
		for (int i = 0; i < 1000; i++) {
			sprintf(buf, "%d%s", i, tans);
			long long ttans = 0;
			sscanf(buf, "%lld", &ttans);
			//int tans = atoi(buf);
			//cerr << tans << endl;
			if (beg <= ttans && ttans < end) {
				printf("%lld\n", ttans);
				break;
			}
		}
	}
	return 0;
}
