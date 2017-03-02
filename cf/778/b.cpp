#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5, maxm = 1000 + 5;

int n, m;

map<string, int> id;
struct o{
	int a, b, c, d;
	string s0;
}ops[maxn];

char buf1[20], buf2[maxm], buf3[maxm], buf4[maxm];

char ans0[maxm], ans1[maxm];

int totid = 0;

int bit_at[maxn];

int get_bit_count(int pos, int _)
{
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		if (ops[i].c == -1)
			bit_at[ops[i].a] = ops[i].s0[pos] - '0';
		else
		{
			int val1 = (ops[i].b == -1) ? _ : bit_at[ops[i].b];
			int val2 = (ops[i].d == -1) ? _ : bit_at[ops[i].d];
			switch(ops[i].c)
			{
				case 0:
					bit_at[ops[i].a] = (val1 ^ val2);
					break;
				case 1:
					bit_at[ops[i].a] = (val1 & val2);
					break;
				case 2:
					bit_at[ops[i].a] = (val1 | val2);
					break;
			}
		}
		ans += bit_at[ops[i].a];
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%s%*s%s", buf1, buf2);
		int id1 = id[buf1], id2 = 0, id3 = 0, op = -1;
		if (id1 == 0) id[buf1] = id1 = i + 1;
		if (buf2[0] == '?') id2 = -1;
		else if ('a' <= buf2[0] && buf2[0] <= 'z') id2 = id[buf2];
		if (id2)
		{
			scanf("%s%s", buf3, buf4);
			if (buf3[0] == 'X') op = 0;
			else if (buf3[0] == 'A') op = 1;
			else if (buf3[0] == 'O') op = 2;
			if (buf4[0] == '?') id3 = -1;
			else id3 = id[buf4];
		}
		ops[i].a = id1;
		ops[i].b = id2;
		ops[i].d = id3;
		ops[i].c = op;
		if (op == -1) ops[i].s0 = buf2;
	}
	for (int i = 0; i < m; i++)
	{
		int gbc0 = get_bit_count(i, 0);
		int gbc1 = get_bit_count(i, 1);
		if (gbc0 <= gbc1)
			ans0[i] = '0';
		else
			ans0[i] = '1';
		if (gbc0 >= gbc1)
			ans1[i] = '0';
		else
			ans1[i] = '1';
//		for (int j = 1; j <= n; j++) cerr << bit_at[j];
//		cerr << endl;
//		cerr << i << ' ' << gbc0 << ' ' << gbc1 << endl;
	}
	puts(ans0);
	puts(ans1);
	return 0;
}
