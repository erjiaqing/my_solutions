#ifndef __APPLE__
#include <bits/stdc++.h>
#else
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <map>
#endif
using namespace std;
const int maxn = 20000 + 5;
long long d[maxn] , d2[maxn];
int vis[maxn];
bool bridge[100000 + 5];
typedef pair<int , int> pii;
map<pii , int> mm;
map<pii , int> md;
vector<int> e[maxn];
int n , m;
struct Pri{
    int v,c;
    Pri(){}
    Pri(int _v , int _c):v(_v) , c(_c){}
    bool operator <(Pri o)const{
        return d[v]+c > d[o.v]+o.c;
    }
};
typedef vector<Pri>::iterator iter;
vector<Pri>p[maxn];
void dijkstra(int scr){
    priority_queue<Pri>q;
    memset(d , 0x3f , sizeof(d));
    d[scr]=0;
    q.push( Pri(scr,0) );
    while(!q.empty() ){
        Pri t=q.top();
        vis[t.v]=1;
        for(iter it=p[t.v].begin();it!=p[t.v].end();it++){
            if(d[it->v] > d[t.v] + it->c){
                d[it->v] = d[t.v] + it->c;
                if(!vis[it->v])
                    q.push( Pri( it->v,0) );
            }
        }
        while(!q.empty())
            if(vis[q.top().v])q.pop();
            else break;
    }
}
void spfa(int beg)
{
    memset(d , 0x3f , sizeof(d));
    d[beg] = 0;
    queue<int> q;
    q.push(beg);
    while (!q.empty())
    {
        int u = q.front();q.pop();
        vis[u] = false;
        for (iter it = p[u].begin();it!=p[u].end() ; it++)
        {
            if (d[it->v] > d[u] + it->c)
            {
                d[it->v] = d[u] + it->c;
                if (!vis[it->v])
                {
                    q.push(it->v);
                    vis[it->v] = true;
                }
            }
        }
    }
}
int dfn[maxn] , low[maxn];
void cbridge(int cur , int father , int dep)
{
    vis[cur] = 1;dfn[cur] = low[cur] = dep;
    int children = 0;
    int v;
    for (int i = 0 ; i < e[cur].size() ; i++)
    {
        v = e[cur][i];
        if (v != father && vis[v] == 1)
        {
            if (dfn[v] < low[cur])
                low[cur] = dfn[v];
        }
        if (0 == vis[v])
        {
            cbridge(v , cur , dep + 1);
            if (low[v] < low[cur]) low[cur] = low[v];
            if (low[v] > dfn[cur])
                bridge[mm[pii(cur , v)]] = true;
        }
    }
    vis[cur] = 2;
}
int main()
{
#ifdef ONLINE_JUDGE
    freopen("important.in" , "r" , stdin);
    freopen("important.out" , "w" , stdout);
#endif
    scanf("%d%d" , &n , &m);
    int u , v , w;
    for (int i = 1 ; i <= m ; i++)
    {
        scanf("%d%d%d" , &u , &v , &w);
        p[u].push_back(Pri(v , w));
        p[v].push_back(Pri(u , w));
        if (mm[pii(u , v)] == 0 || md[pii(u , v)] > w)
        {
            md[pii(u , v)] = md[pii(v , u)] = w;
            mm[pii(u , v)] = mm[pii(v , u)] = i;
        }else if (md[pii(u , v)] == w)
        {
            mm[pii(u , v)] = mm[pii(v , u)] = m + 1;
        }
    }
//#define djikstra spfa
    dijkstra(1);
    memset(vis , 0 , sizeof(vis));
    memcpy(d2 , d , sizeof(d));
    dijkstra(n);
    for (int i = 1 ; i <= n ; i++)
    {
        for (int j = 0 ; j < p[i].size() ; j++)
        {
            v = p[i][j].v;
            w = p[i][j].c;
            if (d2[i] + d[v] + w == d2[n])
            {
                e[i].push_back(v);
                e[v].push_back(i);
            }
        }
    }
    memset(vis , 0 , sizeof(vis));
    cbridge(1 , -1 , 0);
    int cnt = 0;
/*
    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j < e[i].size() ; j++)
            if (e[i][j].first == e[i][j - 1].first)
                bridge[e[i][j].second] = bridge[e[i][j - 1].second] = false;
*/
    for (int i = 1 ; i <= m ; i++)
        if (bridge[i])
            cnt++;
    printf("%d\n" , cnt);
    for (int i = 1 ; i <= m ; i++)
        if (bridge[i])
            printf("%d%c" , i , (--cnt)?' ':'\n');
#ifndef ONLINE_JUDGE
    printf("<EOF>\n");
#endif
    return 0;
}
