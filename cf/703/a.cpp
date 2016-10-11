#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, res = 0;
	cin >> n;
	while (n--)
	{
		int a, b;
		cin >> a >> b;
		if (a > b) res++;
		else if (a < b) res--;
	}
	if (res > 0)
		puts("Mishka");
	else if (res < 0)
		puts("Chris");
	else
		puts("Friendship is magic!^^");
	return 0;
}
