#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>
#include <iostream>
using namespace std;
const int lenc = 500 + 5 , lenab = 10000 + 5;
const int mod = 1000000007;
struct TrieNode{
    int flag , fail , next[10];
}T[lenc];
int f[lenab][lenc][2];
int c[lenab][lenc][2];
char sa[lenab] , sb[lenab] , sc[lenc];
//int kmps[lenc];
int root = 1;
int tT = 1;
void trieInsert(char *numc)
{
    int len = strlen(numc);
    int p = root;
    for (int i = 0 ; i < len ; i++)
    {
        if (T[p].next[numc[i] - '0'] == 0)
            T[p].next[numc[i] - '0'] = ++tT;
        p = T[p].next[numc[i] - '0'];
    }
    T[p].flag = 1;
}
void trieBuild()
{
    int u , v;
    queue<int>Q;
    T[root].fail = 0;
    Q.push(root);
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();
        for (int i = 0 ; i < 10 ; i++)
        {
            if (T[u].next[i])
            {
                if (u == root)
                {
                    T[T[u].next[i]].fail = root;
                }else
                {
                    v = T[u].fail;
                    while(v)
                    {
                        if (T[v].next[i])
                        {
                            T[T[u].next[i]].fail = T[v].next[i];
                            break;
                        }
                        v = T[v].fail;
                    }
                    if (!v)
                        T[T[u].next[i]].fail = root;
                }
                Q.push(T[u].next[i]);
            }
        }
    }
}
int matchAndDp(char *N , bool flag)
{
    int len = strlen(N)  , v;
    memset(f , 0 , sizeof(f));
    memset(c , 0 , sizeof(c));
    f[0][tT][1] = 1;
    for (int i = 0 ; i < len ; i++)
    {
        for (int j = 1 ; j <= tT ; j++)
        {
            for (int k = 0 ; k < 10 ; k++)
            {
                v = j;
                while (v != root && T[v].next[k] == 0)
                    v = T[v].fail;
                v = T[v].next[k];
                if (v == 0)
                    v = root;
                if (k < N[i] - '0')
                {
                    (f[i + 1][v][0] += (f[i][j][0] + f[i][j][1])%mod)%=mod;
                    (c[i + 1][v][0] += (c[i][j][0] + c[i][j][1])%mod)%=mod;
                    if (T[v].flag)
                        (c[i + 1][v][0] += (f[i][j][0] + f[i][j][1]) % mod) %= mod;
                }
                else if (k == N[i] - '0')
                {
                    (f[i + 1][v][0] += f[i][j][0]) %= mod;
                    (f[i + 1][v][1] += f[i][j][1]) %= mod;
                    (c[i + 1][v][0] += c[i][j][0]) %= mod;
                    (c[i + 1][v][1] += c[i][j][1]) %= mod;
                    if (T[v].flag)
                    {
                        (c[i + 1][v][0] += f[i][j][0]) %= mod;
                        (c[i + 1][v][1] += f[i][j][1]) %= mod;
                    }
                }else if (k > N[i] - '0')
                {
                    (f[i + 1][v][0] += f[i][j][0]) %= mod;
                    (c[i + 1][v][0] += c[i][j][0]) %= mod;
                    if (T[v].flag)
                    {
                        (c[i + 1][v][0] += f[i][j][0]) %= mod;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1 ; i <= tT ; i++)
        (ans += (c[len][i][0] + c[len][i][1]) % mod) %= mod;
    return ans;
}
int matchs1(char *N , char *mask)
{
    string s1(N);
    string s2(mask);
    int ans = 0;
    int lastfind = s1.find(s2 , 0);
    while (lastfind != string::npos)
    {
//      cerr << lastfind << endl;
        ans++;
        lastfind = s1.find(s2 , lastfind + 1);
    }
    return ans;
}
int main()
{
    scanf("%s%s%s" , sa , sb , sc);
    trieInsert(sc);
    trieBuild();
    tT++;
    T[tT].next[0] = tT;
    T[tT].fail = root;
    for (int i = 1 ; i <= 9 ; i++)
        T[tT].next[i] = T[root].next[i];
    int ans1(0) , ans2(0);
    ans1 = matchAndDp(sa , 1) - matchs1(sa , sc);
    ans2 = matchAndDp(sb , 1);
//  printf("%lld %lld\n" , ans1 , ans2);
    printf("%d\n" , ((ans2 - ans1) % mod + mod) % mod);
    return 0;
}
