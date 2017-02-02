#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
set<int> appear[26];
char a[maxn], b[maxn], ans[maxn];
int pos[maxn];
int main()
{
	scanf("%s", a);
	scanf("%s", b);
	for (int i = 0; a[i]; i++) appear[a[i] - 'a'].insert(i);
	int pa = 0, pb = strlen(b), lst = strlen(a);
	int ransa = -1, ransb = pb;
	int lenb = pb;
	while (pb > 0)
	{
		int tb = pb - 1;
		auto prev = appear[b[tb] - 'a'].lower_bound(lst);
		if (prev == appear[b[tb] - 'a'].begin()) break;
		prev--;
		lst = *prev;
		pos[tb] = lst;
		pb--;
	}
	int cur = -1;
	ransa = -1, ransb = pb;
	for (pa = -1; pa < lenb - 1; pa++)
	{
		int tpa = pa + 1;
		auto nxt = appear[b[tpa] - 'a'].upper_bound(cur);
		if (nxt == appear[b[tpa] - 'a'].end()) break;
		cur = *nxt;
		while ((pos[pb] <= cur || pb <= tpa) && pb < lenb) pb++;
		if (ransa + 1 + (lenb - ransb) < tpa + 1 + (lenb - pb))
		{
			ransa = tpa;
			ransb = pb;
		}
	}
	if (ransa + 1 + (lenb - ransb) == 0)
		puts("-");
	else
	{
		int tt = 0;
		for (int i = 0; i <= ransa; i++) ans[tt++] = b[i];
		for (int i = ransb; i < lenb; i++) ans[tt++] = b[i];
		puts(ans);
	}
	return 0;
}
