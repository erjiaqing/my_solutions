#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 300000 + 5;
char str[maxn];
int str2[maxn];
int main()
{
	while (~scanf("%s" , str))
	{
		int l = strlen(str);
		str[l] = str[0];
		for (int i = 0 ; i < l ; i++)
		{
			str2[i] = str[i + 1] - str[i];
			if (str2[i] < 0) str2[i] += 8;
		}
		int i = 0 , j = 1 , a = 0 , t;
		while (i < l && j < l && a < l)
		{
			if ((t = (str2[(i + a) >= l ? i + a - l : i + a] - str2[(j + a) >= l ? j + a - l : j + a])))
			{
				if (t > 0) i = i + a + 1;
				else j = j + a + 1;
				if (i == j) j++;
				a = 0;
			}else
			{
				a++;
			}
		}
		a = min(i , j);
		int rl = 0;
		for (int x = a ; x < l ; x++ , rl++) str[rl] = '0' + str2[x];
		for (int x = 0 ; x < a ; x++ , rl++) str[rl] = '0' + str2[x];
		str[rl] = 0;
		printf("%s\n" , str);
	}
}
