#include <bits/stdc++.h>
using namespace std;
const int N=55;
const int mod = 2015;

struct mat{
    int v[55][55];
    mat(int flg = false)
    {
        memset(v , 0 , sizeof(v));
        if (flg)
            for (int i = 0 ; i < 55 ; i++)
                v[i][i] = 1;
    }
    mat operator * (const mat &b)
    {
        mat ret;
        for (int i = 0 ; i < 55 ; i++)
            for (int j = 0 ; j < 55 ; j++)
            {
                for (int k = 0 ; k < 55 ; k++)
                    (ret.v[i][j] += v[i][k] * b.v[k][j]);
                ret.v[i][j] %= mod;
            }
        return ret;
    }
};

int f[N][N],g[N][N];
int t,m,n,p;

mat pow(mat a , int v)
{
    mat ret(true);
    while (v)
    {
        if (v & 1)
            ret = ret * a;
        v >>= 1;
        a = a * a;
    }
    return ret;
}

void work()
{
    int x;
    mat f(false);
    mat r(false);
    for(int i=0;i<=n;++i)
        f.v[i][0]=1;
    for(int j=1;j<=n;++j)
    {
        scanf("%d",&p);
        for(int k=0;k<p;++k)
        {
            scanf("%d",&x);
            f.v[j][x]=1;
        }
    }
    f = pow(f , m - 1);
    for (int i = 1 ; i <= n ; i++)
        r.v[0][i] = 1;
    r = r * f;
    int ans = 0;
    for (int i = 0 ; i <= n ; i++)
        ans = ans + r.v[0][i];
    printf("%d\n" , (ans + 1) % 2015);
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        work();
    }
    return 0;
}
