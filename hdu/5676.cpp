#include <bits/stdc++.h>
using namespace std;

set<unsigned long long> s;
void gen(unsigned long long curr, int l4, int l7)
{
	if (l4)
		gen(curr * 10 + 4, l4 - 1, l7);
	if (l7)
		gen(curr * 10 + 7, l4, l7 - 1);
	if (l4 + l7 == 0)
		s.insert(curr);
}

int main()
{
	for (int i = 1; i <= 9; i++)
		gen(0, i, i);
	unsigned long long res;
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%llu", &res);
		if (res >= 1000000000000000000 || s.lower_bound(res) == s.end())
			puts("44444444447777777777");
		else
			printf("%llu\n", *s.lower_bound(res));
	}
	return 0;
}
