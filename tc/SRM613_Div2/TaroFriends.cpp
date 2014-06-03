// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
Cat Taro likes to play with his cat friends.
Each of his friends currently sits on some coordinate on a straight line that goes from the left to the right.
When Taro gives a signal, each of his friends must move exactly X units to the left or to the right.




You are given an vector <int> coordinates and the int X.
For each i, the element coordinates[i] represents the coordinate of the i-th cat before the movement.
Return the smallest possible difference between the positions of the leftmost cat and the rightmost cat after the movement.


DEFINITION
Class:TaroFriends
Method:getNumber
Parameters:vector <int>, int
Returns:int
Method signature:int getNumber(vector <int> coordinates, int X)


CONSTRAINTS
-coordinates will contain between 1 and 50 elements, inclusive.
-Each element of coordinates will be between -100,000,000 and 100,000,000, inclusive.
-X will be between 0 and 100,000,000, inclusive.


EXAMPLES

0)
{-3, 0, 1}
3

Returns: 3

The difference 3 is obtained if the cats move from {-3,0,1} to {0,-3,-2}.




1)
{4, 7, -7}
5

Returns: 4

The difference 4 is obtained if the cats move from {4,7,-7} to {-1,2,-2}.




2)
{-100000000, 100000000}
100000000

Returns: 0



3)
{3, 7, 4, 6, -10, 7, 10, 9, -5}
7

Returns: 7



4)
{-4, 0, 4, 0}
4

Returns: 4



5)
{7}
0

Returns: 0



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
#include <cctype>
#include <cmath>
using namespace std;

vector<string> split( const string& s, const string& delim =" " ) {
    vector<string> res;
    string t;
    for ( int i = 0 ; i != s.size() ; i++ ) {
        if ( delim.find( s[i] ) != string::npos ) {
            if ( !t.empty() ) {
                res.push_back( t );
                t = "";
            }
        } else {
            t += s[i];
        }
    }
    if ( !t.empty() ) {
        res.push_back(t);
    }
    return res;
}

vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}

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
class TaroFriends {
public:
    int getNumber(vector <int> c, int X) {
        int res=1<<30;
		sort(c.begin(),c.end());
		int len=c.size();
		vector<int> c2=c;
		for (int i=0;i<len;i++)
		{
			vector<int> Cnew;
			for (int j=0;j<len;j++)
			{
				if (c2[j]<c2[i])
				{
					Cnew.push_back(c2[j]+X);
					printf("%d ->\n",c2[j]);
				}
				else if (c2[j]>c2[i])
				{
					Cnew.push_back(c2[j]-X);
					printf("%d <-\n",c2[j]);
				}
			}
			sort(Cnew.begin(),Cnew.end());
			int minval,maxval;
			if (Cnew.size())
			{
				minval=Cnew[0],maxval=*(Cnew.end()-1);
				printf("%d - %d - %d",minval,c2[i],maxval);
				res=min(res,min(max(maxval,c2[i]+X)-min(minval,c2[i]+X),max(maxval,c2[i]-X)-min(minval,c2[i]-X)));
			}else
			{
				res=0;
			}
			cout<<res<<endl;
		}
        return res;
    }

};
// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        int coordinatesARRAY[] = {-3, 0, 1};
        vector <int> coordinates( coordinatesARRAY, coordinatesARRAY+ARRSIZE(coordinatesARRAY) );
        TaroFriends theObject;
        eq(0, theObject.getNumber(coordinates, 3),3);
    }
    {
        int coordinatesARRAY[] = {4, 7, -7};
        vector <int> coordinates( coordinatesARRAY, coordinatesARRAY+ARRSIZE(coordinatesARRAY) );
        TaroFriends theObject;
        eq(1, theObject.getNumber(coordinates, 5),4);
    }
    {
        int coordinatesARRAY[] = {-100000000, 100000000};
        vector <int> coordinates( coordinatesARRAY, coordinatesARRAY+ARRSIZE(coordinatesARRAY) );
        TaroFriends theObject;
        eq(2, theObject.getNumber(coordinates, 100000000),0);
    }
    {
        int coordinatesARRAY[] = {3, 7, 4, 6, -10, 7, 10, 9, -5};
        vector <int> coordinates( coordinatesARRAY, coordinatesARRAY+ARRSIZE(coordinatesARRAY) );
        TaroFriends theObject;
        eq(3, theObject.getNumber(coordinates, 7),7);
    }
    {
        int coordinatesARRAY[] = {-4, 0, 4, 0};
        vector <int> coordinates( coordinatesARRAY, coordinatesARRAY+ARRSIZE(coordinatesARRAY) );
        TaroFriends theObject;
        eq(4, theObject.getNumber(coordinates, 4),4);
    }
    {
        int coordinatesARRAY[] = {7};
        vector <int> coordinates( coordinatesARRAY, coordinatesARRAY+ARRSIZE(coordinatesARRAY) );
        TaroFriends theObject;
        eq(5, theObject.getNumber(coordinates, 0),0);
    }
}
// END CUT HERE
