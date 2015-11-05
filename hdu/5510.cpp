#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
char s[500 + 1][2000 + 1];
int nxt[500 + 1][2000 + 1];
int n, t;
vector<int> v, tmp;
void kmp_prep(int k)
{
	int *next = nxt[k];
	char *str = s[k];
	int len = strlen(str);
	for (int i = 1; i < len; i++)
	{
		int j = i;
		while (j > 0)
		{
			j = next[j];
			if (str[j] == str[i])
			{
				next[i + 1] = j + 1;
				break;
			}
		}
	}
}
bool kmp_doit(int x, int y) // find *y* in *x*
{
	char *xx = s[x];
	char *yy = s[y];
	int lenx = strlen(xx);
	int leny = strlen(yy);
	int *next = nxt[y];
	for (int i = 0, j = 0; i < lenx; i++)
	{
		if (j < leny && xx[i] == yy[j])
			j++;
		else
			while (j > 0)
			{
				j = next[j];
				if (xx[i] == yy[j])
				{
					j++;
					break;
				}
			}
		if (j == leny)
			return true;
	}
	return false;
}
bool check_it(int x)
{
	bool ret = false;
	tmp.clear();
	for (int i = 0; i < v.size(); i++)
	{
		if (!kmp_doit(x, v[i]))
		{
			tmp.push_back(v[i]);
			ret = true;
		}
	}
	tmp.push_back(x);
	v = tmp;
	return ret;
}
int work()
{
	memset(s, 0, sizeof(s));
	memset(nxt, 0, sizeof(nxt));
	scanf("%d", &n);
	int ans = -1;
	v.clear();
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s[i]);
		kmp_prep(i);
		if (check_it(i))
			ans = i + 1;
	}
	return ans;
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		printf("Case #%d: %d\n", i, work());
	}
	return 0;
}
