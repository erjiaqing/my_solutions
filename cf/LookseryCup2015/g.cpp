#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 5;
int nu[maxn] , n;
int main()
{
	bool flag = true;
	scanf("%d" , &n);
	for (int i = 0 ; i < n ; i++)
	{
		scanf("%d" , &nu[i]);
		nu[i] -= ( n - i );
	}
	sort(&nu[0] , &nu[n]);
	for (int i = 0 ; i < n ; i++)
	{
		nu[i] += ( n - i );
		if ( ( nu[i] < 0 ) || ( ( i > 0 && nu[i - 1] > nu[i]) ) )
		{
			flag = false;
			break;
		}
	}
	if ( flag )
		for (int i = 0 ; i < n ; i++)
			printf("%d%s" , nu[i] , (i == n - 1) ? "\n" : " ");
	else
		printf(":(");
	return 0;
}
