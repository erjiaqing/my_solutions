// BEGIN CUT HERE
// PROBLEM STATEMENT
// In the Republic of Nlogonia there are N cities.
/*
For convenience, the cities are numbered 0 through N-1.
For each two different cities i and j, there is a direct one-way road from i to j.
You are given the lengths of those roads as a vector <string> dist with N elements, each with N characters.
For each i and j, the character dist[i][j] represents the length of the road from i to j.

The lengths of roads are integers between 1 and 9, inclusive, and they are represented by digits '1' through '9'.
That is, for distinct i and j, dist[i][j] will be between '1' and '9'.
For each i, dist[i][i] will be '0'.
Note that the roads from i to j and from j to i may have different lengths.

Every year on Algorithms Day (the most important holiday in Nlogonia) people travel between the cities.
More precisely, for each pair of distinct cities i and j, one full bus of people travels from i to j.
Each of those buses drives along a shortest path from its origin to its destination.
If there are multiple shortest paths, the bus driver picks one of them arbitrarily.

The roads in Nlogonia are currently limited.
You are given an int T with the following meaning: 
each of the current roads is only safe if it is guaranteed that there will be strictly fewer than T buses driving along the road.
In other words, a road is unsafe if it is possible that T or more buses will use it.
The government wants to rebuild all unsafe roads before the next Algorithms Day.
Return the sum of lengths of all unsafe roads.

DEFINITION
Class:BuildingRoutes
Method:build
Parameters:vector <string>, int
Returns:int
Method signature:int build(vector <string> dist, int T)


CONSTRAINTS
-N will be between 2 and 50, inclusive.
-dist will contain exactly N elements.
-Each element of dist will contain exactly N characters.
-For each i, dist[i][i] will be '0'.
-For each pair of distinct i and j, dist[i][j] will be between '1' and '9', inclusive.
-T will be between 1 and 2500, inclusive.


EXAMPLES

0)
{"011",
 "101",
 "110"}
1

Returns: 6

As T=1, a road is unsafe as soon as it is possible that a bus will use it. 
Each of the six roads in this test case belongs to some shortest path, hence each of them is unsafe

1)
{"033",
 "309",
 "390"}
1

Returns: 12

The roads 1->2 and 2->1 (the two roads of length 9) will not be used by any bus.
Only the four remaining roads are unsafe in this case.

2)
{"0123",
 "1023",
 "1203",
 "1230"}
2

Returns: 5



3)
{"05789654",
 "10347583",
 "65085479",
 "55602398",
 "76590934",
 "57939045",
 "12345608",
 "68647640"}
3

Returns: 40
*/


// END CUT HERE
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

// BEGIN CUT HERE
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))

template<typename T> void print( T a ) {
    cerr << a;
}
static void print( long long a ) {
    cerr << a << "L";
}
static void print( string a ) {
    cerr << '"' << a << '"';
}
template<typename T> void print( vector<T> a ) {
    cerr << "{";
    for ( int i = 0 ; i != a.size() ; i++ ) {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}
template<typename T> void eq( int n, T have, T need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
template<typename T> void eq( int n, vector<T> have, vector<T> need ) {
    if( have.size() != need.size() ) {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < have.size(); i++ ) {
        if( have[i] != need[i] ) {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
static void eq( int n, string have, string need ) {
    if ( have == need ) {
        cerr << "Case " << n << " passed." << endl;
    } else {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}
// END CUT HERE
class BuildingRoutes {
public:
	int Count[55][55];
	int Dist[55][55];
	int Len[55][55];
	int Pre[55][55];
	void shortestPath(int n)
	{
		for (int k=0;k<n;k++)
			for (int i=0;i<n;i++)
				for (int j=0;j<n;j++)
					Dist[i][j]=min(Dist[i][j],Dist[i][k]+Dist[k][j]);
		for (int s=0;s<n;s++)
			for (int t=0;t<n;t++)
				for (int u=0;u<n;u++)
					for (int v=0;v<n;v++)
						if (Dist[s][u]+Dist[v][t]+Len[u][v]==Dist[s][t])
							Count[u][v]++;
	}
    int build(vector <string> dist, int T) {
        int res=0;
        int n=dist.size();
        memset(Count,0,sizeof(Count));
        for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
				Len[i][j]=Dist[i][j]=dist[i][j]-'0';
			Pre[i][i]=i;
		}
		shortestPath(n);
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				if (Count[i][j]>=T)
					res+=Len[i][j];
        return res;
    }
};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
    {
        string distARRAY[] = {"011",
            "101",
            "110"};
        vector <string> dist( distARRAY, distARRAY+ARRSIZE(distARRAY) );
        BuildingRoutes theObject;
        eq(0, theObject.build(dist, 1),6);
    }
    {
        string distARRAY[] = {"033",
            "309",
            "390"};
        vector <string> dist( distARRAY, distARRAY+ARRSIZE(distARRAY) );
        BuildingRoutes theObject;
        eq(1, theObject.build(dist, 1),12);
    }
    {
        string distARRAY[] = {"0123",
            "1023",
            "1203",
            "1230"};
        vector <string> dist( distARRAY, distARRAY+ARRSIZE(distARRAY) );
        BuildingRoutes theObject;
        eq(2, theObject.build(dist, 2),5);
    }
    {
        string distARRAY[] = {"05789654",
            "10347583",
            "65085479",
            "55602398",
            "76590934",
            "57939045",
            "12345608",
            "68647640"};
        vector <string> dist( distARRAY, distARRAY+ARRSIZE(distARRAY) );
        BuildingRoutes theObject;
        eq(3, theObject.build(dist, 3),40);
    }
}
// END CUT HERE
