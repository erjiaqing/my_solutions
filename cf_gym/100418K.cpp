#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
double p[maxn][maxn];
double f[maxn];
double calc(int k , int n)
{
    double ret = 0;
    for (int m = k ; m < n ; m++)
        for (int x = 0 ; k + x <= m ; x++)
            ret += p[m - 1][k + x - 1] * f[k + x - 1] * k * f[n - (k + x + 1)];
    return ret;
}
int main()
{
    p[0][0] = 1;
    for (int i = 1 ; i < maxn ; i++)
    {
        p[i][0] = 1;
        for (int j = 1 ; j < maxn ; j++)
            p[i][j] = p[i - 1][j] + p[i - 1][j - 1];
    }
    f[0] = 1;
    for (int i = 1 ; i < maxn ; i++)
    {
        f[i] = f[i - 1] * i;
    }
    int n , x;
    cin >> n;
    double ans = 0;
    for (int i = 1 ; i <= n ; i++)
    {
        double tans = calc(i , n);
//        printf("k = %d , p = %.6f\n" , i , tans);
        if (tans > ans)
        {
            x = i;
            ans = tans;
        }
    }
    cout << x << endl;
    return 0;
}
