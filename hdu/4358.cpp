#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
struct query{
	int l , r , id;
	query(){}
	query(const int &_l , const int &_r , const int &_id):
		l(_l) , r(_r) , id(_id){}
}q[maxn];
int rans[maxn] , w[maxn] , s[maxn] , l[maxn] , r[maxn] , cnt[maxn] , t , ans;
map<int , int> M;
bool flg[maxn];
int n , k , tq , blk;
vector<int> e[maxn];
void dfs(int u)
{
	//fprintf(stderr , "%d " ,u);
	l[u] = ++t;
	s[t] = w[u];
	for (int i = 0 ; i < e[u].size() ; i++)
		if (l[e[u][i]] == -1)
			dfs(e[u][i]);
	r[u] = t;
}
bool comp(const query &q1 , const query &q2)
{
	return (q1.l / blk) < (q2.l / blk)
		||((q1.l / blk) ==(q2.l / blk)&& q1.r < q2.r);
}
void update(int p)
{
	if (flg[p] == false && cnt[p] == k)
	{
		flg[p] = true;
		//fprintf(stderr , "ans+\n");
		ans++;
	}
	if (flg[p] == true && cnt[p] != k)
	{
		flg[p] = false;
		ans--;
		//fprintf(stderr , "ans-\n");
	}
}
void work(const int caseno)
{
	int tu , tv;
	memset(l , -1 , sizeof(l));
	memset(r , -1 , sizeof(r));
	memset(cnt , 0 , sizeof(cnt));
	memset(flg , 0 , sizeof(flg));
	t = 0;
	for (int i = 1 ; i <= n ; i++)
		e[i].clear();
	M.clear();
	scanf("%d%d" , &n , &k);
	blk = sqrt(n) + 1;
	for (int i = 1 ; i <= n ; i++)
	{
		scanf("%d" , &w[i]);
		if (M[w[i]] == 0)
			M[w[i]] = i;
		w[i] = M[w[i]];
		//cerr << w[i];
	}
	//cerr << endl;
	for (int i = 1 ; i < n ; i++)
	{
		scanf("%d%d" , &tu , &tv);
		e[tu].push_back(tv);
		e[tv].push_back(tu);
	}
	dfs(1);
	scanf("%d" , &tq);
	for (int i = 0 ; i < tq ; i++)
	{
		scanf("%d" , &tu);
		q[i] = query(l[tu] , r[tu] , i);
	}
	sort(&q[0] , &q[tq] , comp);
	int nl , nr;
	nl = nr = 0;
	ans = 0;
	for (int i = 0 ; i < tq ; i++)
	{
		//fprintf(stderr , "Q%d %d->%d\n" ,q[i].id , q[i].l , q[i].r);
		while (nr > q[i].r)
		{
			cnt[s[nr]]--;
			update(s[nr]);
			//fprintf(stderr , "-r %d\n" ,nr);
			nr--;
		}
		while (nr < q[i].r)
		{
			nr++;
			cnt[s[nr]]++;
			update(s[nr]);
			//fprintf(stderr , "+r %d\n" ,nr);
		}
		while (nl < q[i].l)
		{
			cnt[s[nl]]--;
			update(s[nl]);
			//fprintf(stderr , "+l %d\n" ,nl);
			nl++;
		}
		while (nl > q[i].l)
		{
			nl--;
			cnt[s[nl]]++;
			update(s[nl]);
			//fprintf(stderr , "-l %d\n" ,nl);
		}
		rans[q[i].id] = ans;
	}
	printf("%sCase #%d:\n" , (caseno == 1 ? "" : "\n") , caseno);
	for (int i = 0 ; i < tq ; i++)
		printf("%d\n" , rans[i]);
}
int main()
{
	int t;
	scanf("%d" , &t);
	for (int i = 1 ; i <= t ; i++)
		work(i);
	return 0;
}
