#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000;
struct edge{
    int u , v , n , c;
    edge(){}
    edge(const int &_u , const int &_v , const int &_n , const int &_c):
        u(_u) , v(_v) , n(_n) , c(_c){}
}e[50000];
int h[maxn] , vis[maxn] , lay[maxn] , te;
char str[50][50];
int tn;
int m  , n;
void addedge(int u , int v)
{
    e[te] = edge(u,v,h[u],1);h[u] = te++;
    e[te] = edge(v,u,h[v],0);h[v] = te++;
}
int getnode(int x , int y)
{
    return (x - 1) * m + y;
}
bool build()
{
    memset(lay , -1 , sizeof(lay));
    queue<int>Q;
    Q.push(0);lay[0] = 0;
    while (!Q.empty())
    {
        int u = Q.front();Q.pop();
        for (int c = h[u] ; ~c ; c = e[c].n)
        {
            if (e[c].c && lay[e[c].v] == -1)
            {
                lay[e[c].v] = lay[u] + 1;
                Q.push(e[c].v);
            }
        }
    }
    return lay[maxn - 1] != -1;
}
int find(int u , int low)
{
    if (u == maxn - 1)
        return low;
    int ans = 0;
    for (int c = h[u] ; (~c) && low ; c = e[c].n)
    {
        int tans;
        if (lay[e[c].v] == lay[u] + 1 && (tans = find(e[c].v , min(low , e[c].c))))
        {
            e[c].c -= tans;
            e[c^1].c += tans;
            ans+=tans;
            low-=tans;
        }
    }
    return ans;
}
int dinic()
{
    int ans = 0;
    while (build())
    {
        int tans;
//        cerr << tans << endl;
        while ((tans = find(0 , 0x3f3f3f3f)))
            ans += tans;
    }
    return ans;
}
int main()
{
    memset(h , -1 , sizeof(h));
    int ans = 0;
    scanf("%d%d" , &n , &m);
    for (int i = 1 ; i <= n ; i++)
        scanf("%s" , &str[i][1]);
    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j <= m ; j++)
        {
            if (str[i][j] == 'W')
            {
                addedge(0 , getnode(i,j));
                if (str[i][j + 1] == 'I')
                    addedge(getnode(i,j) , getnode(i,j + 1));
                if (str[i][j - 1] == 'I')
                    addedge(getnode(i,j) , getnode(i,j - 1));
                if (str[i + 1][j] == 'I')
                    addedge(getnode(i,j) , getnode(i + 1,j));
                if (str[i - 1][j] == 'I')
                    addedge(getnode(i,j) , getnode(i - 1,j));
            } else if (str[i][j] == 'I')
            {
                addedge(getnode(i,j) , getnode(i,j) + 500);
                if (str[i][j + 1] == 'N')
                    addedge(getnode(i,j) + 500 , getnode(i,j + 1));
                if (str[i][j - 1] == 'N')
                    addedge(getnode(i,j) + 500 , getnode(i,j - 1));
                if (str[i + 1][j] == 'N')
                    addedge(getnode(i,j) + 500 , getnode(i + 1,j));
                if (str[i - 1][j] == 'N')
                    addedge(getnode(i,j) + 500 , getnode(i - 1,j));
            } else if (str[i][j] == 'N')
            {
                addedge(getnode(i,j) , maxn - 1);
            }
        }
    printf("%d\n" , dinic());
    return 0;
}
