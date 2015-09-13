#include <bits/stdc++.h>
using namespace std;
const int maxn = 1001;
struct edge{
    int l, r;
}e[maxn];
int seq[maxn];
int pos[maxn];
char a[maxn];
int len;
int rt;
void dfs(int &s, int l, int r, int ql, int qr)
{
    if (l > r)
        return;
    int rt = seq[l];
    s = rt;
    int len = rt - ql;
    dfs(e[rt].l, l + 1, l + len, ql, rt - 1);
    dfs(e[rt].r, l + len + 1, r, rt + 1, qr);
}
#ifndef ONLINE_JUDGE
void dfs(int r)
{
    if (~e[r].l)
    {
        cerr << "(";
        dfs(e[r].l);
        cerr << ")";
    }
    cerr << r;
    if (~e[r].r)
    {
        cerr << "(";
        dfs(e[r].r);
        cerr << ")";
    }
}
#endif
void get(int q)
{
    int th = rt;
    len = 0;
    while (th != q)
    {
        if (th < q)
        {
            a[len++] = 'W';
            th = e[th].r;
        }else
        {
            a[len++] = 'E';
            th = e[th].l;
        }
    }
    a[len] = 0;
    printf("%s\n", a);
}
void work()
{
    int n;
    int q = 0;
    memset(e, -1, sizeof(e));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]);
        pos[seq[i]] = i;
    }
    dfs(rt, 1, n, 1, n);
#ifndef ONLINE_JUDGE
    dfs(rt);
    cerr << "\n";
#endif
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int qn;
        scanf("%d", &qn);
        get(qn);
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
        work();
    return 0;
}
