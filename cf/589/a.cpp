#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <set>
using namespace std;
const int maxn = 20000 + 1;
map<string, int> M;
string s[maxn];
int gupc[maxn];
set<int> gupn[maxn];
int totg = 0;
int main()
{
	ios::sync_with_stdio(0);
	string rea, rea2;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
		int suffix = s[i].find('@');
		unsigned long long hash = 0;
		unsigned long long hash0 = 0;
		int ifat = false;
		rea = "";
		rea2 = "";
		for (int j = 0; j < s[i].size(); j++)
		{
			if (s[i][j] == '@') break;
			if (s[i][j] == '+') ifat = true;
			if (s[i][j] >= 'A' && s[i][j] <= 'Z')
			{
			//	hash = hash * 131 + s[i][j] - 'A' + 'a';
				rea = rea + char(s[i][j] - 'A' + 'a');
				if (!ifat)
					rea2 = rea2 + char(s[i][j] - 'A' + 'a');
			}
			else
			{
			//	hash = hash * 131 + s[i][j];
				rea = rea + char(s[i][j]);
				if (!ifat && s[i][j] != '.')
					rea2 = rea2 + char(s[i][j]);
			}
		}
		unsigned long long suffixhash = 0;
		unsigned long long sss = 1;
		for (int j = suffix; j < s[i].size(); j++)
		{
			sss = sss * 131;
			if (s[i][j] >= 'A' && s[i][j] <= 'Z')
			{
				suffixhash = suffixhash * 131 + s[i][j] - 'A' + 'a';
				rea = rea + char(s[i][j] - 'A' + 'a');
				rea2 = rea2 + char(s[i][j] - 'A' + 'a');
			}
			else
			{
				suffixhash = suffixhash * 131 + s[i][j];
				rea = rea + char(s[i][j]);
				rea2 = rea2 + char(s[i][j]);
			}
		}
		if (suffixhash == 16295226087558137392ull)
			rea = rea2;
		//cerr << rea << endl;
		if ((ifat = M[rea]) == 0) M[rea] = ifat = ++totg;
		gupn[ifat].insert(i);
		gupc[ifat]++;
		//cerr << "{{{" << s[i] << endl;
	}
	cout << totg << endl;
	for (int i = 1; i <= totg; i++)
	{
		cout << gupc[i];
		for (set<int>::iterator si = gupn[i].begin(); si != gupn[i].end(); si++)
			cout << " " << s[*si];
		cout << endl;
	}
	return 0;
}
