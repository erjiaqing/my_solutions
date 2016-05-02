#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
vector<string> vec;
const int maxn = 1001;
int sgn[maxn], num[maxn];
int cur = 0;
int n;
int main()
{
	string buf;
	while (cin >> buf)
		vec.push_back(buf);
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == "?")
		{
			if (i == 0 || vec[i - 1] == "+") sgn[i] = 1;
			else sgn[i] = -1;
		}
	}
	n = atoi(vec[vec.size() - 1].c_str());
	for (int i = 0; i < vec.size(); i++)
	{
		if (sgn[i] == 1) {
			num[i] = 1;
			cur++;
		} else if (sgn[i] == -1) {
			num[i] = 1;
			cur--;
		}
	}
	for (int i = 0; i < vec.size(); i++)
	{
		if (sgn[i] == -1) {
			if (cur > n) {
				cur++;
				num[i] = min(n, cur - n);
				cur -= num[i];
			}
		} else if (sgn[i] == 1) {
			if (cur < n) {
				cur--;
				num[i] = min(n, n - cur);
				cur += num[i];
			}
		}
	}
	if (cur != n) {
		printf("Impossible\n");
	} else {
		printf("Possible\n");
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i] == "?")
			{
				if (i != 0) {
					printf(" %d", num[i]);
				} else {
					printf("%d", num[i]);
				}
			} else {
				printf(" %s", vec[i].c_str());
			}
		}
		printf("\n");
	}
	return 0;
}
