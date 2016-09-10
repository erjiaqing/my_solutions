#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int ca[6][2] = {{1, 3},{0, 5},{1, 3},{0, 5},{1, 3},{1, 3}};
int no[6][2] = {{2, 4},{2, 4},{0, 5},{2, 4},{0, 5},{2, 4}};
int ovo[6] = {5, 3, 4, 1, 2, 0};
char cur[15], tar[15], tmp[7];
int main()
{
	scanf("%s", cur);
	scanf("%s", tar);
	int len = strlen(cur);
	double ans = 1;
	for (int i = 0; i < len; i++)
	{
		scanf("%s", tmp);
		if (cur[i] == tar[i]) continue;
		double total = 0;
		int t2 = 0;
		for (int j = 0; j < 6; j++)
		{
			if (cur[i] == tmp[j])
			{
				int flg1 = 0;
				int flg2 = 0;
				t2++;
				if (tmp[ovo[j]] == tar[i]) flg1 = flg2 = 1;
				for (int k = 0; k < 2; k++) if (tmp[ca[j][k]] == tar[i]) flg1 = 1;
				for (int k = 0; k < 2; k++) if (tmp[no[j][k]] == tar[i]) flg2 = 1;
				total += (flg1 + flg2) / 2.0;
			}
		}
		total /= t2;
		ans *= total;
	}
	printf("%.10f\n", ans);
	return 0;
}
