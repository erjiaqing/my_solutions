#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, k;
char s[2][10] = {"ABC", "ABAABB"};
char l[2] = {3, 6};
void print(int id, int len)
{
	for (int i = 0; i < len; i++) printf("%c", s[id][i % l[id]]);
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		scanf("%d%d%d", &n, &m, &k);
		printf("Case #%d:\n", i);
		if (n < m) {printf("Impossible");}
		else if (n == m)
			for (int i = 0; i < n; i++)
				printf("A");
		else
		{
			if (k == 1) printf("Impossible");
			else if (k == 2)
			{
				if (n == 8 && m == 7) printf("AABABBAA");
				else if (m < 8) printf("Impossible");
				else
				{
					for (int i = 0; i < m - 8; i++) printf("A");
					print(1, n - m + 8);
				}
			}else
			{
				if (m < 3) printf("Impossible");
				else
				{
					for (int i = 0; i < m - 3; i++) printf("A");
					print(0, n - m + 3);
				}
			}
		}
		puts("");
	}
	return 0;
}
