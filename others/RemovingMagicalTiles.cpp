#include <cstring>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

#define LOWBIT( _x) ( (_x) & (-_x) )

using namespace std;

typedef pair<int ,int > pii;
typedef pair<int ,pii > pipii;
typedef vector<pipii > :: iterator vpipiii;
vector<pipii> L;
vector<int> U;

const int maxn = 100000 + 5;

int n;
int bit[ maxn << 1 ];
int l[ maxn ] , r[ maxn ] , f[ maxn ];

void insert(int p, int v)
{
	for (; p <= U.size() ; p += LOWBIT( p ) )
		bit[p] = max(bit[p] , v);
}

int query(int p)
{
	int ret = 0;
	for (; p ; p-= LOWBIT( p ) )
		ret = max(ret , bit[p]);
	return ret;
}

int main()
{
	int t1 , t2;
	scanf("%d",&n);
	for (int i = 0 ; i < n ; i++)
		scanf("%d%d%d%d", &t1, &t2, &l[i], &r[i]),
		L.push_back( pipii( t1 , pii( 0 , i ) ) ),
		L.push_back( pipii( t2 , pii( 1 , i ) ) ),
		U.push_back( l[i] ),
		U.push_back( r[i] );
	sort( U.begin() , U.end() );
	sort( L.begin() , L.end() );
	for (int i = 0 ; i < U.size() ; i++)
	{
		int id = L[i].second.second , flag = L[i].second.first;
		if ( flag )
		{
			insert( lower_bound( U.begin() , U.end() , r[id] ) - U.begin() + 1 , f[id]);
		}else
			f[id] = query( lower_bound( U.begin() , U.end() , l[id] ) - U.begin() + 1 ) + 1;
	}
	printf("%d\n", *max_element(&f[0] , &f[n]) );
	return 0;
}
