#include <iostream>
#include <cassert>
using namespace std;
int x0 = 0;
int cnt[1 << 20];
int win_seq[1 << 22];
int num[1 << 22];
int nxt[1 << 22];
int current_seq[205];

int rand()
{
	return x0 = ((487237ll * x0 + 1011807) & ((1 << 20) - 1));
}

void kmp_pre(int x[], int m, int next[])
{
	int i, j;
	j = next[0] = -1;
	i = 0;
	while (i < m)
	{
		while (j != -1 && x[i] != x[j]) j = next[j];
		next[++i] = ++j;
	}
}

int kmp_count(int x[], int m, int y[], int n)
{
	int i, j;
	int ans = 0;
	int kans[5];
	kmp_pre(x, m, nxt);
	i = j = 0;
	while (i < n)
	{
		while (-1 != j && y[i] != x[j]) j = nxt[j];
		i++;j++;
		if (j >= m)
		{
			kans[ans++] = i;
			if (ans > 2) return -1;
			j = nxt[j];
		}
	}
	if (ans == 1)
	{
		return (kans[0] < (1 << 20) ? kans[0] : kans[0] - (1 << 20));
	} else if (ans == 2)
	{
		return ((kans[1] - kans[0] == (1 << 20)) ? kans[0] : -1);
	}
	return -1;
}

int main()
{
	for (int i = 0; i < (1 << 20); i++)
	{
		rand();
		num[i] = num[i + (1 << 20)] = x0;
		win_seq[i] = win_seq[i + (1 << 20)] = (__builtin_popcount(x0) & 1);
	}
	int current_seq_len = 0;
	int token, new_token = 0;
	int k = -1;
	int curpos = -1;
	cin >> token;
	cout << 1 << endl;
	while (cin >> new_token)
	{
		int match = -1;
		if (new_token == -1) return 0;
		if (curpos == -1) {
			bool flg = new_token > token;
			current_seq[current_seq_len++] = flg;
			match = kmp_count(current_seq, current_seq_len, win_seq, (1 << 21));
			if (flg)
				k = new_token - token - 1;
			if (match != -1 && k != -1)
				curpos = match - 1;
			token = new_token;
		}
		if (~curpos)
		{
			curpos++;
			if (new_token > 200) {
				if (win_seq[curpos] == 1)
					cout << 1 << endl;
				else
					cout << (new_token - 200) << endl;
			} else if (win_seq[curpos] == 1) {
				cout << min(200 - new_token - k, new_token - 1) << endl;
			} else {
				cout << 1 << endl;
			}
		} else {
			cout << 1 << endl;
		}
		cout.flush();
	}
	return 0;
}
