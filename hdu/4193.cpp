#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

#define ls( _x ) ( (_x) << 1 )
#define rs( _x ) ( (_x) << 1 | 1 )

const int maxn = (1000000 + 5) * 2;
int pref[maxn] , queu[maxn] , hd , tl , n;
void work()
{
	int ans = 0;
	pref[0] = 0;
	for (int i = 1 ; i <= n ; i++)
	{
		cin >> pref[i];
		pref[i + n] = pref[i];
	}
	for (int i = 1 ; i <= n + n ; i++)
		pref[i] += pref[i - 1];
	hd = 0;tl = -1;
	for (int i = 1 ; i < n ; i++)
	{
		while (tl >= hd && pref[i] <= pref[queu[tl]]) tl--;
		queu[++tl] = i;
	}
	for (int i = n ; i < n + n ; i++)
	{
		while (tl >= hd && pref[i] <= pref[queu[tl]]) tl--;
		queu[++tl] = i;
		while (queu[hd] < i - n + 1) hd++;
		if (pref[queu[hd]] - pref[i - n] >= 0)
			ans++;
	}
	printf("%d\n" , ans);
}
int main()
{
	while ((~scanf("%d" , &n)) && n)
		work();
	return 0;
}
