// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
Cat Taro has a string S.
He wants to obtain the string "CAT" from the string S.
In a single turn he can choose any character and erase all occurrences of this character in S.
He can do as many turns as he wants (possibly zero).




You are given the string S.
Return "Possible" (quotes for clarity) if it is possible to obtain the string "CAT" and "Impossible" otherwise.



DEFINITION
Class:TaroString
Method:getAnswer
Parameters:string
Returns:string
Method signature:string getAnswer(string S)


CONSTRAINTS
-S will contain between 1 and 50 characters, inclusive.
-S will contain only uppercase English letters ('A'-'Z').


EXAMPLES

0)
"XCYAZTX"

Returns: "Possible"

It is possible to obtain string "CAT" in three turns, as follows:


Erase all characters 'X' (and obtain the string "CYAZT")


Erase all characters 'Y' (and obtain the string "CAZT")


Erase all characters 'Z' (and obtain the string "CAT")



1)
"CTA"

Returns: "Impossible"



2)
"ACBBAT"

Returns: "Impossible"

Note that whenever you are erasing a character, you must erase all its occurrences. In this case, it is not possible to erase the first 'A' and keep the second one.

3)
"SGHDJHFIOPUFUHCHIOJBHAUINUIT"

Returns: "Possible"



4)
"CCCATT"

Returns: "Impossible"



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
class TaroString {
public:
    string getAnswer(string S) {
        string res;
		int C,A,T;
		C=A=T=0;
		for (int i=0;S[i]!=0;i++)
		{
			if (S[i]=='C')
			{
				if (A!=0 || T!=0)
					return "Impossible";
				C++;
			}
			else if (S[i]=='A')
			{
				if (C==0 || T!=0)
					return "Impossible";
				A++;
			}else if (S[i]=='T')
			{
				if (C==0 || A==0)
					return "Impossible";
				T++;
			}
		}
		if (A==1 && C==1 && T==1)
			return "Possible";
		else
			return "Impossible";
    }

};
// BEGIN CUT HERE
void main( int argc, char* argv[] ) {
    {
        TaroString theObject;
        eq(0, theObject.getAnswer("XCYAZTX"),"Possible");
    }
    {
        TaroString theObject;
        eq(1, theObject.getAnswer("CTA"),"Impossible");
    }
    {
        TaroString theObject;
        eq(2, theObject.getAnswer("ACBBAT"),"Impossible");
    }
    {
        TaroString theObject;
        eq(3, theObject.getAnswer("SGHDJHFIOPUFUHCHIOJBHAUINUIT"),"Possible");
    }
    {
        TaroString theObject;
        eq(4, theObject.getAnswer("CCCATT"),"Impossible");
    }
}
// END CUT HERE
