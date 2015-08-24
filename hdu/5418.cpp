#include <algorithm>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 16 + 1;
typedef pair<int , int> pii;
int len[maxn][maxn];
int d[maxn][1 << maxn];
bool inq[maxn][1 << maxn];
vector<pii> e[maxn];
int n , m;
void work()
{
    memset(len , 0x7f , sizeof(len));
    memset(d , 0x3f , sizeof(d));
    memset(inq , 0 , sizeof(inq));
    scanf("%d%d" , &n , &m);
    int tu , tv , tc;
    for (int i = 1 ; i <= n ; i++) e[i].clear();
    for (int i = 0 ; i < m ; i++)
    {
        scanf("%d%d%d" , &tu , &tv , &tc);
        len[tv][tu] = len[tu][tv] = min(len[tu][tv] , tc);
    }
    for (int i = 1 ; i <= n ; i++)
        for (int j = i + 1 ; j <= n ; j++)
            if (len[i][j] < 0x7f7f7f7f)
            {
                e[i].push_back(pii(j , len[i][j]));
                e[j].push_back(pii(i , len[i][j]));
            }
    queue<pii> q;
    q.push(pii(1 , 1));
    d[1][1] = 0;
    while (!q.empty())
    {
        pii tq = q.front();
        q.pop();
        inq[tq.first][tq.second] = false;
        int td = d[tq.first][tq.second];
        for (vector<pii>::iterator i = e[tq.first].begin() ; i != e[tq.first].end() ; i++)
        {
            if (d[i->first][tq.second | (1 << (i->first - 1))] > (td + i -> second))
            {
                d[i->first][tq.second | (1 << (i->first - 1))] = (td + i -> second);
                if (!inq[i->first][tq.second | (1 << (i->first - 1))])
                {
                    q.push(pii(i->first , tq.second | (1 << (i->first - 1))));
                    inq[i->first][tq.second | (1 << (i->first - 1))] = true;
                }
            }
        }
    }
    printf("%d\n" , d[1][(1 << n) - 1]);
}
int main()
{
    int t;
    scanf("%d" , &t);
    while (t--)
        work();
    return 0;
}
