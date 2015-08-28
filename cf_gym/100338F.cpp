#include <algorithm>
#include <iostream>
#include <string>
#include <cstdio>
#include <utility>
#include <cstring>
#include <cmath>
#include <cassert>
using namespace std;
const int maxn = 3000 * 100 + 5;
typedef pair<int ,int> pii;
struct trie_node{
    trie_node *next[26];
    int flg;
    int c[2] , lastappear;
}*root;
trie_node tn[maxn];
int rn = 0;
int tspam = 0, tgood = 0;
trie_node* getnode()
{
    return &tn[rn++];
}
int normalize(char a)
{
    if ('a' <= a && a <= 'z') return a - 'a';
    if ('A' <= a && a <= 'Z') return a - 'A';
    return -1;
}
void insert_word(string &buf, int beg, int end, int type, int uid)
{
    trie_node *nd = root;
#ifdef LOCAL
    cerr << beg << " " << end << endl;
#endif
    for (int i = beg; i < end; i++)
    {
        int ni = normalize(buf[i]);
#ifdef LOCAL
        cerr << buf[i];
#endif
        assert((-1 < ni) && (ni < 26));
        if (nd->next[ni] == nullptr)
            nd->next[ni] = getnode();
        nd = nd->next[ni];
    }
#ifdef LOCAL
    cerr << endl;
#endif
    if (nd->lastappear != uid)
    {
        nd->flg = true;
        nd->c[type]++;
        nd->lastappear = uid;
    }
}
pii query_word(string &buf, int beg, int end, int uid)
{
    trie_node *nd = root;
    for (int i = beg; i < end; i++)
    {
        int ni = normalize(buf[i]);
        assert((-1 < ni) && (ni < 26));
        if (nd->next[ni] == nullptr)
            nd->next[ni] = getnode();
        nd = nd->next[ni];
    }
    if (nd->lastappear != uid)
    {
        nd->flg = true;
        nd->lastappear = uid;
        return pii(nd->c[0], nd->c[1]);
    }
    return pii(-1 ,-1);
}
void process_study(int type, int uid)
{
    string buf;
    getline(cin, buf);
    buf = buf + "#";
    int len = buf.size();
    int beg = 0, end = 0;
    for (int i = 0; i < len; i++)
    {
        if (normalize(buf[i]) != -1)
            end++;
        else
        {
            if (end != beg)
                insert_word(buf, beg, end, type, uid);
            beg = end = i + 1;
        }
    }
}
bool process_check(int uid, int t)
{
    string buf;
    getline(cin, buf);
    buf = buf + "#";
    int len = buf.size();
    int beg = 0, end = 0;
    int badword = 0, totword = 0;
    for (int i = 0; i < len; i++)
    {
        if (normalize(buf[i]) != -1)
            end++;
        else
        {
            if (end != beg)
            {
                pii result = query_word(buf, beg, end, uid);
                if (result.first != -1 && result.second != -1)
                {
                    totword++;
                    if (result.first + result.second > 0 && result.first >= result.second)
                    {
#ifdef LOCAL
                        cerr << buf.substr(beg, end - beg) << "#badword\n";
#endif
                        badword++;
                    }
                }
            }
            end = beg = i + 1;
        }
    }
    return badword * 100 / totword >= t;
}
int main()
{
#ifndef LOCAL
    freopen("spam.in", "r", stdin);
    freopen("spam.out", "w", stdout);
#endif
    root = getnode();
    string buf;
    getline(cin, buf);
    int s, g, n, t;
    int uid = 1;
    sscanf(buf.c_str(), "%d%d%d%d", &s, &g, &n, &t);
    for (int i = 0; i < s; i++)
        process_study(0, uid++);
    for (int i = 0; i < g; i++)
        process_study(1, uid++);
    for (int i = 0; i < n; i++)
        printf(process_check(uid++, t)?"spam\n":"good\n");
    return 0;
}
