#include <bits/stdc++.h>
using namespace std;
int RoyalStraightFlush(int *card)
{
	int app[52];
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i]]++;
	for (int i = 0; i < 4; i++)
	{
		bool flg = 1;
		for (int j = 0; j < 5; j++)
			if (!app[i * 13 + j + 8])
				flg = 0;
		if (flg)
			return 99999999;
	}
	return -99999;
}

int StraightFlush(int *card)
{
	int app[52];
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i]]++;
	for (int i = 0; i < 4; i++)
	{
		for (int j = -1; j <= 8; j++)
		{
			bool flg = 1;
			for (int k = 0; k < 5; k++)
				if (app[i * 13 + (j + k + 13) % 13] == 0)
					flg = false;
			if (flg)
				return 90000000 + j + 5;
		}
	}
	return -99999;
}

int FourOfAKind(int *card)
{
	int app[13];
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i] % 13]++;
	for (int i = 0; i < 13; i++)
		if (app[i] == 4)
			for (int j = 0; j < 13; j++)
				if (app[j] == 1)
					return 89000000 + 2000 * i + j;
	return -99999;
}

int FullHouse(int *card)
{
	int app[13];
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i] % 13]++;
	for (int i = 0; i < 13; i++)
		if (app[i] == 3)
			for (int j = 0; j < 13; j++)
				if (app[j] == 2)
					return 85000000 + 2000 * i + j;
	return -99999;
}

int Flush(int *card)
{
	int app[4], app2[13], app3 = 0;
	memset(app, 0, sizeof(app));
	memset(app2, 0, sizeof(app2));
	for (int i = 0; i < 5; i++)
	{
		app[card[i] / 13]++;
		app2[card[i] % 13]++;
	}
	for (int i = 12; i >= 0; i--)
		while (app2[i]--)
			app3 = app3 * 13 + i;
	for (int i = 0; i < 4; i++)
		if (app[i] == 5)
			return 82000000 + app3;
	return -99999;
}

int Straight(int *card)
{
	int app[13];
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i] % 13]++;
	for (int j = 8; j >= -1; j--)
	{
		bool flg = 1;
		for (int k = 0; k < 5; k++)
			if (!app[(j + k + 13) % 13])
				flg = false;
		if (flg)
			return 79000000 + j + 5;
	}
	return -99999;
}

int ThreeOfAKind(int *card)
{
	int app[13], app2 = 0;
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i] % 13]++;
	for (int i = 0; i < 13; i++)
		if (app[i] == 3)
		{
			for (int j = 0; j < 13; j++)
				if (app[j] == 1)
					app2 |= (1 << j);
			return 76000000 + i * 50000 + app2;
		}
	return -99999;
}

int TwoPairs(int *card)
{
	int app[13], app2 = 0, app3 = 0, cnt = 0;
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i] % 13]++;
	for (int i = 12; i >= 0; i--)
		if (app[i] == 2)
		{
			cnt++;
			app2 = app2 * 13 + i;
		} else if (app[i] == 1) {
			app3 = i;
		}
	if (cnt == 2)
		return 73000000 + app2 * 13 + app3;
	return -99999;
}

int OnePair(int *card)
{
	int app[13], app2 = 0;
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i] % 13]++;
	for (int i = 0; i < 13; i++)
		if (app[i] == 2)
		{
			app2 = 0;
			for (int j = 0; j < 13; j++)
				if (app[j] == 1)
					app2 |= (1 << j);
			return 70000000 + i * 50000 + app2;
		}
	return -99999;
}

int HighCard(int *card)
{
	int app[13], app2 = 0;
	memset(app, 0, sizeof(app));
	for (int i = 0; i < 5; i++)
		app[card[i] % 13]++;
	for (int i = 12; i >= 0; i--)
		while (app[i]--)
			app2 = app2 * 13 + i;
	return 10000000 + app2;
}

int calc_score(int *card)
{
	int ans = 0;
	ans = max(ans, RoyalStraightFlush(card));
	ans = max(ans, StraightFlush(card));
	ans = max(ans, FourOfAKind(card));
	ans = max(ans, FullHouse(card));
	ans = max(ans, Flush(card));
	ans = max(ans, Straight(card));
	ans = max(ans, ThreeOfAKind(card));
	ans = max(ans, TwoPairs(card));
	ans = max(ans, OnePair(card));
	ans = max(ans, HighCard(card));
	assert(ans > 0);
	return ans;
}

int KIND[128];
int RANK[128];

int mxscore = 0;
int card[18], card2[18], avail[18];
char s1[5][5], s2[5][5], s3[5][5];
int use[52];

void dfsmxscore(int dep, int sel)
{
	if (dep == 7)
	{
		if (sel == 5)
		{
			for (int i = 0; i < 5; i++)
				card2[i] = card[i];
			mxscore = max(mxscore, calc_score(card2));
		}
		return;
	}
	dfsmxscore(dep + 1, sel);
	card[sel] = avail[dep];
	dfsmxscore(dep + 1, sel + 1);
}

int check()
{
	int score1 = 0, score2 = 0;
	for (int i = 0; i < 2; i++)
		avail[i] = KIND[s1[i][0]] * 13 + RANK[s1[i][1]];
	mxscore = 0;
	dfsmxscore(0, 0);
	score1 = mxscore;
	for (int i = 0; i < 2; i++)
		avail[i] = KIND[s2[i][0]] * 13 + RANK[s2[i][1]];
	mxscore = 0;
	dfsmxscore(0, 0);
	score2 = mxscore;
	return score1 > score2;
}

bool sol()
{
	memset(use, 0, sizeof(use));
	for (int i = 0; i < 2; i++) {
		scanf("%s", s1[i]);
		if (s1[i][0] == '#')
			return false;
	}
	for (int i = 0; i < 2; i++) 
		scanf("%s", s2[i]);
	for (int i = 0; i < 3; i++) 
		scanf("%s", s3[i]);
	for (int i = 0; i < 2; i++)
		use[KIND[s1[i][0]] * 13 + RANK[s1[i][1]]] = 1;
	for (int i = 0; i < 2; i++)
		use[KIND[s2[i][0]] * 13 + RANK[s2[i][1]]] = 1;
	for (int i = 0; i < 3; i++)
		use[avail[i + 2] = KIND[s3[i][0]] * 13 + RANK[s3[i][1]]] = 1;
	int res1 = 0, res2 = 0;
	check();

	for (int i = 0; i < 52; i++)
	{
		avail[5] = i;
		for (int j = i + 1; j < 52; j++)
		{
			avail[6] = j;
			if (use[i] == 0 && use[j] == 0)
			{
				res1++;
				res2 += check();
			}
		}
	}
	printf("%.20f\n", 1. * res2 / res1);
	return true;
}

int main()
{
	KIND['S'] = 0;KIND['H'] = 1;KIND['C'] = 2;KIND['D'] = 3;
	RANK['2'] = 0;RANK['3'] = 1;RANK['4'] = 2;RANK['5'] = 3;
	RANK['6'] = 4;RANK['7'] = 5;RANK['8'] = 6;RANK['9'] = 7;
	RANK['T'] = 8;RANK['J'] = 9;RANK['Q'] = 10;RANK['K'] = 11;
	RANK['A'] = 12;
	while (sol());
	return 0;
}
