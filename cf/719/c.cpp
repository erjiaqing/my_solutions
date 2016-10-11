#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;

char res[maxn];
int bede[maxn], afde[maxn], belen, aflen, oucur;
char output[maxn];
int n, t;

int main()
{
	scanf("%d%d", &n, &t);
	scanf("%s", res + 1);
	res[0] = '0';
	int pointpos = -1;
	for (int i = 1; i <= n; i++)
		if (res[i] == '.')
		{
			pointpos = i;
			break;
		}
	if (pointpos == -1)
	{
		puts(res + 1);
		return 0;
	}
	belen++;
	for (int i = 1; i < pointpos; i++)
		bede[belen++] = res[i] - '0';
	for (int i = pointpos + 1; i <= n; i++)
		afde[aflen++] = res[i] - '0';
	for (int i = 0; i < aflen; i++)
		if (afde[i] >= 5)
			aflen = i + 1;
	while (aflen > 0 && t)
	{
		if (afde[aflen - 1] >= 5)
		{
			aflen--;
			if (aflen)
				afde[aflen - 1]++;
			else
				bede[belen - 1]++;
			t--;
		} else break;
	}
	for (int i = belen - 1; i > 0; i--)
	{
		bede[i - 1] += bede[i] / 10;
		bede[i] %= 10;
	}
	for (int i = (bede[0] == 0 ? 1 : 0); i < belen; i++)
		output[oucur++] = '0' + bede[i];
	if (aflen)
	{
		output[oucur++] = '.';
		for (int i = 0; i < aflen; i++)
			output[oucur++] = '0' + afde[i];
	}
	puts(output);
	return 0;
}
