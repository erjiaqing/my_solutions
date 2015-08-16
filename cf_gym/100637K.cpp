#include <cstdio>
const int maxn = 40 + 5;
long long f[maxn][maxn];
int n , k;
int main()
{
	f[0][0] = f[1][0] = f[2][0] = f[2][1] = f[3][0] = 1;
	f[3][1] = 3;
	scanf("%d%d" , &n , &k);
	for (int i = 4 ; i <= n ; i++)
	{
		f[i][0] = 1;
		for (int j = 1 ; j <= k ; j++)
		{
			f[i][j] = f[i - 1][j];
			for (int l = 1 ; l < i ; l++)
				for (int c = 0 ; c < j ; c++)
					f[i][j] += f[l - 1][c] * f[i - l - 1][j - c - 1];
		}
	}
	printf("%lld\n" , f[n][k]);
	return 0;
}
