#include <bits/stdc++.h>
using namespace std;

char buf[1025][35];
bool flg = 0;

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", buf[i]);
		if (!flg)
		{
			if (buf[i][0] == buf[i][1] && buf[i][1] == 'O')
			{
				buf[i][0] = buf[i][1] = '+';
				flg = 1;
			}
		}
		if (!flg)
		{
			if (buf[i][3] == buf[i][4] && buf[i][4] == 'O')
			{
				buf[i][3] = buf[i][4] = '+';
				flg = 1;
			}
		}
	}
	if (flg){
		puts("YES");
		for (int i = 0; i < n; i++)
			puts(buf[i]);
	}
	else puts("NO");
	return 0;
}
