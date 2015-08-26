#include <iostream>
#include <cstdio>
using namespace std;
double d[400 + 5][400 + 5];
bool f[400 + 5];
int main()
{
    int n;
    cin >> n;
    n -= 2;
    d[0][0] = 1;
    for (int i = 1 ; i <= n ; i++)
    {
        for (int j = 0 ; j < i ; j++)
        {
            double sl = 0;
            double sr = 0;
            int cl = j;
            int cr = (i - j - 1);
            for (int k = 0 ; k <= i ; k++)
            {
                sl += d[cl][k] ;
                sr += d[cr][k] ;
                d[i][k + 1] += (sr * d[cl][k] ) / i;
                d[i][k + 1] += (sl * d[cr][k] ) / i;
                d[i][k + 1] -= d[cl][k]  * d[cr][k]  / i;
            }
        }
    }
    for (int i = n ; i <= n ; i++)
    {
        double ans = 0;
        for (int j = 0 ; j <= n ; j++)
            ans += 10 * j * d[i][j] ;
        printf("%.12f\n" , ans);
    }
    return 0;
} 

