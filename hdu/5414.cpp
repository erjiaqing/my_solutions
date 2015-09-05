#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
char s[maxn], t[maxn];
int main()
{
    int ct;
    scanf("%d", &ct);
    while (ct--)
    {
        int hs, ht, ls, lt;
        bool flg = true;
        hs = ht = 0;
        scanf("%s%s", s, t);
        ls = strlen(s);
        lt = strlen(t);
        if (ls > lt)
        {
            printf("No\n");
            continue;
        }
        for (ht = 1; ht < lt; ht++)
            if (t[ht] != t[0]) break;
        for (hs = 0; hs < ht; hs++)
            if (s[hs] != t[hs])
            {
                flg = false;
                break;
            }
        if (flg)
            for (; hs < ls;)
            {
                for (; ht < lt; ht++)
                    if (s[hs] == t[ht])
                        break;
                if (ht == lt)
                {
                    flg = false;
                    break;
                }
                hs++;
                ht++;
            }
        printf("%s", flg ? "Yes\n" : "No\n");
    }
    return 0;
}
