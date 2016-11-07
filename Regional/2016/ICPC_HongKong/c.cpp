#include <bits/stdc++.h>
using namespace std;

const int maxn = 50000 + 5;
typedef pair<int, int> pii;

long double lg2 = log((long double)(2.));
long double lg3 = log((long double)(3.));

int n;
int mx2, mx3, mi2, mi3;
int mx2id, mx3id, mi2id, mi3id;
int flg_mx2_is_mx3;
int flg_mi2_is_mi3;
int ogcd_a, ogcd_b, olcm_a, olcm_b;
int allgcda, allgcdb, alllcma, alllcmb;
pii nd[maxn];

int prefmaxa[maxn], suffmaxb[maxn];
int prefmaxb[maxn], suffmaxa[maxn];
int prefmina[maxn], suffminb[maxn];
int prefminb[maxn], suffmina[maxn];

int ans1lcma, ans1lcmb;
int ans1gcda, ans1gcdb;

#define x first
#define y second

void getans(int cnt_lcm, int cnt_gcd)
{
	int a0, b0, a1, b1;
	if (cnt_lcm > 1 || (cnt_lcm == 1 && flg_mx2_is_mx3))
		a0 = mx2, b0 = mx3;
	else if (cnt_lcm)
		a0 = ans1lcma, b0 = ans1lcmb;
	else
		a0 = allgcda, b0 = allgcdb;
	if (cnt_gcd > 1 || (cnt_gcd == 1 && flg_mi2_is_mi3))
		a1 = mi2, b1 = mi3;
	else if (cnt_gcd)
		a1 = ans1gcda, b1 = ans1gcdb;
	else
		a1 = alllcma, b1 = alllcmb;
	printf("%d %d %d %d\n", a0, b0, a1, b1);
}

int main()
{
	mx2 = mx3 = -1;
	mi2 = mi3 = 1001;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &nd[i].x, &nd[i].y);
		mx2 = max(mx2, nd[i].x);
		mi2 = min(mi2, nd[i].x);
		mx3 = max(mx3, nd[i].y);
		mi3 = min(mi3, nd[i].y);
	}
	for (int i = 0; i < n; i++)
	{
		if (nd[i].x == mx2 && nd[i].y == mx3) flg_mx2_is_mx3 = 1;
		if (nd[i].x == mi2 && nd[i].y == mi3) flg_mi2_is_mi3 = 1;
	}
	prefmaxa[0] = prefmina[0] = nd[0].x;
	prefmaxb[0] = prefminb[0] = nd[0].y;
	suffmaxa[n] = suffmaxb[n] = -1;
	suffmina[n] = suffminb[n] = 1001;
	allgcda = allgcdb = ogcd_a = ogcd_b = 1001;
	alllcma = alllcmb = olcm_a = olcm_b = -1;
	if (n == 1)
	{
		printf("%d %d %d %d\n", nd[0].x, nd[0].y, nd[0].x, nd[0].y);
		return 0;
	}

	for (int i = 1; i < n; i++)
	{
		prefmaxa[i] = max(prefmaxa[i - 1], nd[i].x);
		prefmina[i] = min(prefmina[i - 1], nd[i].x);
		prefmaxb[i] = max(prefmaxb[i - 1], nd[i].y);
		prefminb[i] = min(prefminb[i - 1], nd[i].y);
	}

	for (int i = n - 1; i >= 0; i--)
	{
		suffmaxa[i] = max(suffmaxa[i + 1], nd[i].x);
		suffmina[i] = min(suffmina[i + 1], nd[i].x);
		suffmaxb[i] = max(suffmaxb[i + 1], nd[i].y);
		suffminb[i] = min(suffminb[i + 1], nd[i].y);
	}

	for (int i = 0; i < n; i++)
	{
		allgcda = min(allgcda, nd[i].x);
		allgcdb = min(allgcdb, nd[i].y);
		alllcma = max(alllcma, nd[i].x);
		alllcmb = max(alllcmb, nd[i].y);
	}

	ans1gcda = min(suffmaxa[1], nd[0].x);
	ans1gcdb = min(suffmaxb[1], nd[0].y);
	ans1lcma = max(suffmina[1], nd[0].x);
	ans1lcmb = max(suffminb[1], nd[0].y);
	for (int i = 1; i < n; i++)
	{
		int tansa = min(max(suffmaxa[i + 1], prefmaxa[i - 1]), nd[i].x);
		int tansb = min(max(suffmaxb[i + 1], prefmaxb[i - 1]), nd[i].y);
		int diffa = ans1gcda - tansa;
		int diffb = tansb - ans1gcdb;
		if (diffa * lg2 > diffb * lg3)
		{
			ans1gcda = tansa;
			ans1gcdb = tansb;
		}
	}

	for (int i = 1; i < n; i++)
	{
		int tansa = max(min(suffmina[i + 1], prefmina[i - 1]), nd[i].x);
		int tansb = max(min(suffminb[i + 1], prefminb[i - 1]), nd[i].y);
		int diffa = ans1lcma - tansa;
		int diffb = tansb - ans1lcmb;
		if (diffa * lg2 < diffb * lg3)
		{
			ans1lcma = tansa;
			ans1lcmb = tansb;
		}
	}

	for (int i = 1; i <= n; i++)
		getans(n - i, i - 1);
	return 0;
}
