#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 20;
char buf[maxn];
int len;
int calc1()
{
	int cur = buf[0] - '0';
	for (int i = 1; i < len; i += 2)
		if (buf[i] == '+')
			cur += buf[i + 1] - '0';
		else
			cur *= buf[i + 1] - '0';
	return cur;
}
int calc2()
{
	int sta[20], stp = 0;
	int ans = 0;
	sta[stp] = buf[0] - '0';
	for (int i = 1; i < len; i += 2)
		if (buf[i] == '+')
		{
			stp++;
			sta[stp] = buf[i + 1] - '0';
		} else
			sta[stp] *= buf[i + 1] - '0';
	for (int i = 0; i <= stp; i++)
		ans += sta[i];
	return ans;
}
int main()
{
	while (~scanf("%s", buf))
	{
		int ans = 0, a1, a2;
		char res = 'I';
		len = strlen(buf);
		a1 = calc1();
		a2 = calc2();
		scanf("%d", &ans);
		if (a1 == ans)
			res = 'L';
		if (a2 == ans)
			res = ((res == 'I') ? 'M' : 'U');
		printf("%c\n", res);
	}
	return 0;
}
