#include <bits/stdc++.h>
using namespace std;

int cnt[26][1505];
int ans[26][1505];
char str[1505];
int len;

void process()
{
	for (int chr = 0; chr < 26; chr++)
	for (int i = 0; i <= len; i++)
		for (int j = i + 1; j <= len; j++)
			ans[chr][j - i - cnt[chr][j] + cnt[chr][i]] = 
			max(
				ans[chr][j - i - cnt[chr][j] + cnt[chr][i]],
				j - i);
	for (int j = 0; j < 26; j++)
	for (int i = 1; i <= len; i++)
		ans[j][i] = max(ans[j][i], ans[j][i - 1]);
}

int main()
{/*
	ios::sync_with_stdio(0);
	cin >> len;
	cin >> (str + 1);
	*/
	scanf("%d", &len);
	scanf("%s", str + 1);
	for (int i = 1; i <= len; i++)
	{
		for (int j = 0; j < 26; j++) cnt[j][i] = cnt[j][i - 1];
		cnt[str[i] - 'a'][i]++;
	}
	process();
	int q;
	scanf("%d", &q);
//	cin >> q;
	while (q--)
	{
		int a; char b[5];
		scanf("%d%s", &a, b);
		printf("%d\n", ans[b[0] - 'a'][a]);
//		cin >> a >> b;
//		cout << ans[b[0] - 'a'][a] << '\n';
	}
	return 0;
}
