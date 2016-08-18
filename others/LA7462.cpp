#include <bits/stdc++.h>
using namespace std;

char buf[50000], op[50000];
int num[100000], sz[50000];
int nms, ops, n;

void sol()
{
	nms = ops = 0;
	scanf("%d", &n);
	scanf("%s", buf + 1);
	int len = strlen(buf + 1);
	buf[0] = '(';
	buf[len + 1] = ')';
	buf[len + 2] = 0;
	for (int i = 0; buf[i]; i++)
	{
		if (buf[i] == '(')
		{
			if (buf[i + 1] == '(')
				op[++ops] = '(';
		} else if (buf[i] == ')' && buf[i - 1] == ')')
		{
		//	printf(") @ %d\n", i);
			while (ops && op[ops] != '(')
			{
				char tp = op[ops--];
				int n1 = num[nms], s1 = sz[nms];nms--;
				int n2 = num[nms], s2 = sz[nms];nms--;
				nms++;
				if (tp == 'J')
				{
					num[nms] = min(n1 + s2, n2 + s1);
					sz[nms] = s1 + s2;
//					printf("Join %d(sz = %d) & %d(sz = %d)\n", n1, s1, n2, s2);
				}
				else if (tp == 'U')
				{
					num[nms] = max(n1, n2);
					sz[nms] = s1 + s2;
//					printf("Unio %d(sz = %d) & %d(sz = %d)\n", n1, s1, n2, s2);
				}
			}
			ops--;
		} else if (buf[i] == 'J' || buf[i] == 'U')
			op[++ops] = buf[i];
		else if ('0' <= buf[i] && buf[i] <= '9' && buf[i + 1] == ')')
		{
			num[++nms] = 1;
			sz[nms] = 1;
		}
	}
	printf("%d\n", num[1]);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
