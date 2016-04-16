#include <bits/stdc++.h>
using namespace std;
string sol(string p)
{
	string ret = "";
	ret = ret + p[0];
	for (int i = 1; i < p.size(); i++)
		if (p[i] < ret[0])
			ret = ret + p[i];
		else
			ret = p[i] + ret;
	return ret;
}
int main()
{
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		string str;
		cin >> str;
		cout << "Case #" << i << ": " << sol(str) << endl;
	}
	return 0;
}
