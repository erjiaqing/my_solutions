#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;
char s[maxn];

int main()
{
	int ln;
	scanf("%s", s);
	ln = strlen(s);
	bool flg = 0;
	for (int i = 0; i < ln; i++)
	{
		if (s[i] != 'a')
		{
			flg = 1;
			for (int j = i; j < ln && s[j] != 'a'; j++)
				s[j]--;
			break;
		}
	}
	if (!flg) s[ln - 1] = 'z';
	puts(s);
	return 0;
}
