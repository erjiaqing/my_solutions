#include <cstdio>
#include <cstring>
const int maxn = 100000 + 1;
char s1[maxn], s2[maxn], s3[maxn];
int same12 = 0;
int n, t, t1, t2, ts, td;
int df, sg, sm;
int max(const int &a, const int &b) {return a < b ? b : a;}
int min(const int &a, const int &b) {return a < b ? a : b;}
int main()
{
	scanf("%d%d%s%s", &n, &t, s1, s2);
	t1 = t2 = 0;
	for (int i = 0; i < n; i++)
		if (s1[i] == s2[i]) ts++;
	td = n - ts;
	df = sg = sm = -1;
	memset(s3, '#', n * sizeof(char));
	for (int i = max(0, t - td); i <= min(ts, (2 * t - td) / 2); i++)
	{
		sg = td - t + i;
		df = td - 2 * sg;
		sm = i;
		break;
	}
#ifdef LOCAL
	printf("sg%d df%d sm%d\n", sg, df, sm);
#endif
	if (df == -1)
	{
		puts("-1");
		return 0;
	}
	sg = sg * 2;
	for (int i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			if (sg)
			{
				if (sg & 1)
					s3[i] = s2[i];
				else
					s3[i] = s1[i];
				sg--;
			} else
			{
				for (int j = 'a'; j < 'd'; j++)
					if (j != s1[i] && j != s2[i])
					{
						s3[i] = j;
						break;
					}
			}
		}else
		{
			if (sm)
			{
				for (int j = 'a'; j < 'c'; j++)
					if (j != s1[i] && j != s2[i])
					{
						s3[i] = j;
						break;
					}
				sm--;
			}else
			{
				s3[i] = s1[i];
			}
		}
	}
	puts(s3);
	return 0;
}
