#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int maxq = 2000 + 5, maxop = 1000000 + 5;

struct op{
	int o, x1;
}oper[maxop];

long long colorsum[maxq][maxq];
long long bit[maxq];
int state[maxq];
vector<pair<pii, int> > query;

vector<pair<pii, int> > chain[maxq];

inline int lb(int x) {return x & -x;}

long long get(int x)
{
	long long ret = 0;
	for (; x; x -= lb(x)) ret += bit[x];
	return ret;
}

void upd(int x, int v) {for (; x < maxq; x += lb(x)) bit[x] += v;}

int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++)
	{
		int len;
		scanf("%d", &len);
		for (int j = 0; j < len; j++)
		{
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			chain[i].push_back(make_pair(pii(x, y), w));
		}
		sort(chain[i].begin(), chain[i].end());
	}
	int q;
	char operat[15];
	scanf("%d", &q);
	int qid = 0;
	for (int i = 0; i < q; i++)
	{
		scanf("%s", operat);
		if (operat[0] == 'A')
		{
			oper[i].o = 0;
			oper[i].x1 = ++qid;
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			query.push_back(make_pair(pii(x2, y2), qid));
			query.push_back(make_pair(pii(x1 - 1, y1 - 1), qid));
			query.push_back(make_pair(pii(x2, y1 - 1), -qid));
			query.push_back(make_pair(pii(x1 - 1, y2), -qid));
		} else
		{
			oper[i].o = 1;
			scanf("%d", &oper[i].x1);
		}
	}
	sort(query.begin(), query.end());
	int qrys = query.size();
	for (int i = 1; i <= k; i++)
	{
		int qh1 = 0, qh2 = 0;
		int len = chain[i].size();
		memset(bit, 0, sizeof bit);
//		cerr << "COLOR " << i << endl;
		while (qh1 < len || qh2 < qrys)
		{
			if (qh2 == qrys) break;
			if (qh1 < len && chain[i][qh1].first.first <= query[qh2].first.first)
			{
//				fprintf(stderr, "POS (%d,%d) WEIGHT %d\n", chain[i][qh1].first.first, chain[i][qh1].first.second, chain[i][qh1].second);
				upd(chain[i][qh1].first.second, chain[i][qh1].second);
				qh1++;
			} else
			{
				long long res = get(query[qh2].first.second);
				int pos = abs(query[qh2].second);
				int sgn = (pos == query[qh2].second ? 1 : -1);
//				fprintf(stderr, "QRY (%d,%d) sgn %c res %lld qry %d\n", query[qh2].first.first, query[qh2].first.second, sgn == 1 ? '+' : '-', res, pos);
				colorsum[pos][i] += sgn * res;
				qh2++;
			}
		}
	}
	for (int i = 0; i < q; i++)
	{
		if (oper[i].o == 0)
		{
			long long ans = 0;
			int qry = oper[i].x1;
//			cerr << "QID = " << qry << endl;
			for (int j = 1; j <= k; j++)
				if (!state[j])
					ans += colorsum[qry][j];
			printf("%lld\n", ans);
		} else
			state[oper[i].x1] ^= 1;
	}
	return 0;
}
