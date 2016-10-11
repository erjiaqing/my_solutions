#include <bits/stdc++.h>
using namespace std;
string r1[2] = {"love", "hate"};
string r2[2] = {"that ", "it\n"};
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n ; i++)
		printf("I %s %s", r1[i % 2].c_str(), r2[i == n].c_str());
	return 0;
}
