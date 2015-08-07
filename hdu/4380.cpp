#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define x first
#define y second

typedef pair<int , int> pii;
const int maxn = 100 + 5;
const int maxm = 1000 + 5;

int upper[maxn][maxn];
pii gold_mine[maxm];
pii farmer_house[maxn];
int n , m , caseno;

bool above_line(const pii &a , const pii &b , const pii &c)
	// return if c is above the line a-b
{
	long long x1 = b.x - a.x;
	long long x2 = c.x - a.x;
	long long y1 = b.y - a.y;
	long long y2 = c.y - a.y;
	return (x1 * y2) - (x2 * y1) > 0;
}

int eabs(int a)
{
	return (a < 0) ? -a : a;
}

void work()
{
	int tx , ty;
	for (int i = 0 ; i < n ; i++)
	{
		scanf("%d%d" , &tx , &ty);
		farmer_house[i] = pii(tx , ty);
	}
	for (int i = 0 ; i < m ; i++)
	{
		scanf("%d%d" , &tx , &ty);
		gold_mine[i] = pii(tx , ty);
	}
	sort(&farmer_house[0] , &farmer_house[n]);
	sort(&gold_mine[0] , &gold_mine[m]);
	memset(upper , 0 , sizeof(upper));
	int beg = 0;
	for (int i = 0 ; i < n ; i++)
	{
		while (gold_mine[beg].x < farmer_house[i].x)
			beg++;
		for (int j = i + 1 ; j < n ; j++)
		{
			if (farmer_house[j].x == farmer_house[i].x)
				continue;
			for (int k = beg ; k < m && gold_mine[k].x < farmer_house[j].x ; k++)
				upper[i][j] += above_line(farmer_house[i] , farmer_house[j] , gold_mine[k]);
			upper[j][i] = upper[i][j];
			//fprintf(stderr , "%d %d - %d %d (cnt = %d)\n" , farmer_house[i].x , farmer_house[i].y , farmer_house[j].x , farmer_house[j].y , upper[i][j]);
		}
	}

	int ans = 0;

	for (int i = 0 ; i < n ; i++)
		for (int j = i + 1 ; j < n ; j++)
			for (int k = j + 1 ; k < n ; k++)
				ans += abs(upper[i][j] + upper[j][k] - upper[k][i]) % 2;
	printf("Case %d: %d\n" , ++caseno , ans);
}

int main()
{
	while (~scanf("%d%d" , &n , &m))
		work();
}
