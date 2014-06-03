// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
Cat Taro has N cards.
Exactly two integers are written on each card.
You are given two vector <int>s first and second, each with N elements.
For each i, the element first[i] represents the first integer on the i-th card, and the element second[i] represents the second integer on the i-th card.




It is known that for each x from 1 to N, inclusive, there is exactly one card with the first integer equal to x.
In other words, all elements of first represent a permutation of integers from 1 to N, inclusive.
On the other hand, second may contain duplicates, but all elements of second are only between 1 and 10, inclusive.




You are also given an int K. Taro wants to choose some subset of the cards (possibly none or all of them) in such a way that the total number of different integers written on the cards is less than or equal to K. Return the total number of ways to do that.


DEFINITION
Class:TaroCards
Method:getNumber
Parameters:vector <int>, vector <int>, int
Returns:long long
Method signature:long long getNumber(vector <int> first, vector <int> second, int K)


CONSTRAINTS
-first will contain between 1 and 50 elements, inclusive.
-first and second will contain the same number of elements.
-first will represent a permutation of integers between 1 and N, inclusive, where N is the number of elements in first.
-Each element of second will be between 1 and 10, inclusive.
-K will be between 1 and 2N, inclusive, where N is the number of elements in first.


EXAMPLES

0)
{1, 2}
{2, 3}
2

Returns: 3

In this case, there are four subsets of cards:


None of the cards. The number of different integers is 0.


Only the first card. The number of different integers is 2.


Only the second card. The number of different integers is 2.


Both the first and the second card. The number of different integers is 3.


However, the last subset has too many different integers. Thus, the answer is 3.

1)
{3, 1, 2}
{1, 1, 1}
3

Returns: 8



2)
{4, 2, 1, 3}
{1, 2, 3, 4}
5

Returns: 16



3)
{1, 2, 3, 4, 5, 6, 7}
{2, 1, 10, 9, 3, 2, 2}
3

Returns: 17



4)
{1}
{2}
1

Returns: 1



5)
{6, 20, 1, 11, 19, 14, 2, 8, 15, 21, 9, 10, 4, 16, 12, 17, 13, 22, 7, 18, 3, 5}
{4, 5, 10, 7, 6, 2, 1, 10, 10, 7, 9, 4, 5, 9, 5, 10, 10, 3, 6, 6, 4, 4}
14

Returns: 2239000



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
class TaroCards {
public:
    long long getNumber(vector <int> first, vector <int> second, int K) {
        long long res;
        return res;
    }

};
// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        int firstARRAY[] = {1, 2};
        vector <int> first( firstARRAY, firstARRAY+ARRSIZE(firstARRAY) );
        int secondARRAY[] = {2, 3};
        vector <int> second( secondARRAY, secondARRAY+ARRSIZE(secondARRAY) );
        TaroCards theObject;
        eq(0, theObject.getNumber(first, second, 2),3L);
    }
    {
        int firstARRAY[] = {3, 1, 2};
        vector <int> first( firstARRAY, firstARRAY+ARRSIZE(firstARRAY) );
        int secondARRAY[] = {1, 1, 1};
        vector <int> second( secondARRAY, secondARRAY+ARRSIZE(secondARRAY) );
        TaroCards theObject;
        eq(1, theObject.getNumber(first, second, 3),8L);
    }
    {
        int firstARRAY[] = {4, 2, 1, 3};
        vector <int> first( firstARRAY, firstARRAY+ARRSIZE(firstARRAY) );
        int secondARRAY[] = {1, 2, 3, 4};
        vector <int> second( secondARRAY, secondARRAY+ARRSIZE(secondARRAY) );
        TaroCards theObject;
        eq(2, theObject.getNumber(first, second, 5),16L);
    }
    {
        int firstARRAY[] = {1, 2, 3, 4, 5, 6, 7};
        vector <int> first( firstARRAY, firstARRAY+ARRSIZE(firstARRAY) );
        int secondARRAY[] = {2, 1, 10, 9, 3, 2, 2};
        vector <int> second( secondARRAY, secondARRAY+ARRSIZE(secondARRAY) );
        TaroCards theObject;
        eq(3, theObject.getNumber(first, second, 3),17L);
    }
    {
        int firstARRAY[] = {1};
        vector <int> first( firstARRAY, firstARRAY+ARRSIZE(firstARRAY) );
        int secondARRAY[] = {2};
        vector <int> second( secondARRAY, secondARRAY+ARRSIZE(secondARRAY) );
        TaroCards theObject;
        eq(4, theObject.getNumber(first, second, 1),1L);
    }
    {
        int firstARRAY[] = {6, 20, 1, 11, 19, 14, 2, 8, 15, 21, 9, 10, 4, 16, 12, 17, 13, 22, 7, 18, 3, 5};
        vector <int> first( firstARRAY, firstARRAY+ARRSIZE(firstARRAY) );
        int secondARRAY[] = {4, 5, 10, 7, 6, 2, 1, 10, 10, 7, 9, 4, 5, 9, 5, 10, 10, 3, 6, 6, 4, 4};
        vector <int> second( secondARRAY, secondARRAY+ARRSIZE(secondARRAY) );
        TaroCards theObject;
        eq(5, theObject.getNumber(first, second, 14),2239000L);
    }
}
// END CUT HERE
