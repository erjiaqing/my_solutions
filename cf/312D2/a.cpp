#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
typedef pair<int , int> pii;
pii apple[maxn];
int n , tx , ta;
int cl , cr;
int applel[maxn] , appler[maxn];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 0 ; i < n ; i++)
	{
		cin >> tx >> ta;
		apple[i] = make_pair(tx , ta);
	}
	sort(&apple[0] , &apple[n]);
	int pos = lower_bound(&apple[0] , &apple[n] , make_pair(0 , 0)) - &apple[0];
	for (int i = pos - 1 , j = 1 ; i >= 0 ; i-- , j++)
		applel[cl = j] = applel[j - 1] + apple[i].second;
	for (int i = pos , j = 1 ; i < n ; i++ , j++)
		appler[cr = j] = appler[j - 1] + apple[i].second;
	applel[cl + 1] = applel[cl];
	appler[cr + 1] = appler[cr];
	int tc = min(cl , cr);
	int ans = max(applel[tc + 1] + appler[tc] , applel[tc] + appler[tc + 1]);
	cout << ans << endl;
	return 0;
}
