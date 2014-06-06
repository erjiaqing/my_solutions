// END CUT HERE
#include <bits/stdc++.h>
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
class UniformBoard {
public:
	int amap[25][25],pmap[25][25],bmap[25][25],empty=false;
	int check(int l,int r,int u,int d,int ta,int tp,int tb)
	{
		int x1,x2,x3,x4,x5,x6;
		x1=amap[r][d]-amap[l-1][d]-amap[r][u-1]+amap[l-1][u-1];
		x2=pmap[r][d]-pmap[l-1][d]-pmap[r][u-1]+pmap[l-1][u-1];
//		x3=bmap[r][d]-bmap[l-1][d]-bmap[r][u-1]+bmap[l-1][u-1];
		if (tb)
		{
			if (ta>=(r-l+1)*(d-u+1))
				return x2+((r-l+1)*(d-u+1)-x1);
			else
				return 0x3f3f3f3f;
		}else
		{
			if (x2)
				return 0x3f3f3f3f;
			else
				return 0;
		}
	}
    int getBoard(vector <string> board, int K) {
        int res,n=board.size();
        memset(amap,0,sizeof(amap));
        memset(pmap,0,sizeof(pmap));
        memset(bmap,0,sizeof(bmap));
        int ta,tb,tp,tans;
        ta=tb=tp=res=0;
        for (int i=1;i<=n;i++)
        	for (int j=1;j<=n;j++)
			{
				amap[i][j]=amap[i-1][j]+amap[i][j-1]-amap[i-1][j-1]+(board[i-1][j-1]=='A');
				pmap[i][j]=pmap[i-1][j]+pmap[i][j-1]-pmap[i-1][j-1]+(board[i-1][j-1]=='P');
//				bmap[i][j]=bmap[i-1][j]+bmap[i][j-1]-bmap[i-1][j-1]+(board[i-1][j-1]=='.');
				ta+=(board[i-1][j-1]=='A');
				tb+=(board[i-1][j-1]=='.');
				tp+=(board[i-1][j-1]=='P');
			}
		for (int l=1;l<=n;l++)
			for (int u=1;u<=n;u++)
				for (int r=l;r<=n;r++)
					for (int d=u;d<=n;d++)
					{
						tans=check(l,r,u,d,ta,tp,tb);
//						printf("%d %d %d %d %d\n",l,r,u,d,tans);
						if (tans<=K)
							res=max(res,(r-l+1)*(d-u+1));
					}
        return res;
    }

};
// BEGIN CUT HERE
int main( int argc, char* argv[] ) {
//Sample Test Datas
//
printf(">>>>Sample Test Datas\n");
    {
        string boardARRAY[] = {"AP",
            ".A"};
        vector <string> board( boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
        UniformBoard theObject;
        eq(0, theObject.getBoard(board, 0),1);
    }
    {
        string boardARRAY[] = {"AP",
            ".A"};
        vector <string> board( boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
        UniformBoard theObject;
        eq(1, theObject.getBoard(board, 1),2);
    }
    {
        string boardARRAY[] = {"PPP",
            "APA",
            "A.P"};
        vector <string> board( boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
        UniformBoard theObject;
        eq(2, theObject.getBoard(board, 2),3);
    }
    {
        string boardARRAY[] = {"AAA",
            "PPP",
            "AAA"};
        vector <string> board( boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
        UniformBoard theObject;
        eq(3, theObject.getBoard(board, 10),3);
    }
    {
        string boardARRAY[] = {"."};
        vector <string> board( boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
        UniformBoard theObject;
        eq(4, theObject.getBoard(board, 1000),0);
    }
    {
        string boardARRAY[] = {"PPAAPA..AP",
            "PPA.APAP..",
            "..P.AA.PPP",
            "P.P..APAA.",
            "P.P..P.APA",
            "PPA..AP.AA",
            "APP..AAPAA",
            "P.P.AP...P",
            ".P.A.PAPPA",
            "..PAPAP..P"};
        vector <string> board( boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
        UniformBoard theObject;
        eq(5, theObject.getBoard(board, 10),15);
    }

printf("System Test Datas:\n");

//System Test Datas


{
    string boardARRAY[]={"AP", ".A"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(0, theObject.getBoard(board,  0),1);
}
    
{
    string boardARRAY[]={"AP", ".A"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(1, theObject.getBoard(board,  1),2);
}
    
{
    string boardARRAY[]={"PPP", "APA", "A.P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(2, theObject.getBoard(board,  2),3);
}
    
{
    string boardARRAY[]={"AAA", "PPP", "AAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(3, theObject.getBoard(board,  10),3);
}
    
{
    string boardARRAY[]={"PPAAPA..AP", "PPA.APAP..", "..P.AA.PPP", "P.P..APAA.", "P.P..P.APA", "PPA..AP.AA", "APP..AAPAA", "P.P.AP...P", ".P.A.PAPPA", "..PAPAP..P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(4, theObject.getBoard(board,  10),15);
}
    
{
    string boardARRAY[]={".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(5, theObject.getBoard(board,  0),1);
}
    
{
    string boardARRAY[]={".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A.", ".A.A.A.A.A.A.A.A.A.A", "A.A.A.A.A.A.A.A.A.A."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(6, theObject.getBoard(board,  99),198);
}
    
{
    string boardARRAY[]={"PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(7, theObject.getBoard(board,  1000),1);
}
    
{
    string boardARRAY[]={"PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPAP", "PAPAPAPAPAPAPAPAPAPA", "APAPAPAPAPAPAPAPAPA."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(8, theObject.getBoard(board,  199),200);
}
    
{
    string boardARRAY[]={"AP.PA", "AP.PA", "AP.PA", "AP.PA", "AP.PA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(9, theObject.getBoard(board,  7),6);
}
    
{
    string boardARRAY[]={"APAPA", "APAPA", "APAPA", "APAPA", "APAPA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(10, theObject.getBoard(board,  1000),5);
}
    
{
    string boardARRAY[]={"AAAAA", "PPPPP", "AAAAA", "PPPPP", "AAAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(11, theObject.getBoard(board,  100),5);
}
    
{
    string boardARRAY[]={"PP..P.....PPPPPPP.P.", "P..P..P..PP.P.P.PPP.", "PP.PP.PPP.P..PPPPPP.", ".P.........P.P...PP.", "PP......P..P.PP...PP", "PPP...P.P.PP...PPPP.", "..P.PPP.P...P...PPPP", "PPPPPPP.P.....P..P.P", ".P.P.PPP..P....P.P..", "P.PP....PP.P.PPP.PP.", "P.PP.PP..P...PP.PPPP", "PP.P.......PP.PP....", ".P.P.PP..P...P....PP", "P...P..PPPP..PP...PP", "P.PPPP.P.P..PP..P.PP", ".P..PP.PP.P..PPPP.PP", "PP.PPPP..P..P..P.P.P", "PPPP...PP.P...P...PP", "P.P..P.PP...PP.P....", "PP.P.PP......PP.PP.P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(12, theObject.getBoard(board,  1000),0);
}
    
{
    string boardARRAY[]={"."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(13, theObject.getBoard(board,  1000),0);
}
    
{
    string boardARRAY[]={"PPPPP", "PPPPP", "PPPPP", "PPPPP", "PPPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(14, theObject.getBoard(board,  345),0);
}
    
{
    string boardARRAY[]={"AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(15, theObject.getBoard(board,  0),400);
}
    
{
    string boardARRAY[]={"..AA.AAAAA.......A.A", ".AA.AA.AA..A.A.A...A", "..A..A...A.AA......A", "A.AAAAAAAAA.A.AAA..A", "..AAAAAA.AA.A..AAA..", "...AAA.A.A..AAA....A", "AA.A...A.AAA.AAA....", ".......A.AAAAA.AA.A.", "A.A.A...AA.AAAA.A.AA", ".A..AAAA..A.A...A..A", ".A..A..AA.AAA..A....", "..A.AAAAAAA..A..AAAA", "A.A.A..AA.AAA.AAAA..", ".AAA.AA....AA..AAA..", ".A....A.A.AA..AA.A..", "A.AA..A..A.AA....A..", "..A....AA.AA.AA.A.A.", "....AAA..A.AAA.AAA..", ".A.AA.A..AAA..A.AAAA", "..A.A..AAAAAA..A..A."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(16, theObject.getBoard(board,  1000),200);
}
    
{
    string boardARRAY[]={"AAAAAAAAAAA", "AAAAAAAA.AA", "AAAAAA..AAA", "AAAAAA.AAAA", "AA.AAAAAAAA", "AAAAAAAAAAA", "AAAAAAAAAAA", "AAA.AAAAAAA", "AA.AAAAAAAA", "AA.AAAAAAAA", "AAAAAAAAAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(17, theObject.getBoard(board,  30),110);
}
    
{
    string boardARRAY[]={".........A..........", "...............A....", ".....A..............", "....A.A.AA..........", ".....A.A..A.........", "....A........A.....A", "....................", "...............A....", "..A.................", "..........A.A.......", ".A..A.....AA........", "....AA..........A...", ".......A....A.A.....", "...A...........AA...", ".A........A...A.....", "A.A......A..........", ".......A..A.........", "....AAA........A....", ".........A........A.", ".........A.........A"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(18, theObject.getBoard(board,  1000),45);
}
    
{
    string boardARRAY[]={"APPPPPAAAPPAPPPPPPPA", "PPPPPPAPPPAPPP.PPPPP", "PPPPPAPPPPPPPPPPPAPP", "PPPPPAPPPPPPPPAPPPAP", "PPPPPPPPPPPPPPAPPPAP", "PAPPPPAPPPPPPPPPPPPA", "PPAPPAPAPPPPPPPAPPPP", "PPPPAPPPPPPPPPPPAAPP", "PPPPPPPPPPPPPAPPPPAP", "PPAPPPPPPPPPPPPPPPPP", "PPPAPPAPPPPPPAAPPPPP", "PPPPPAPPPPPAAPPPPPPA", "PPAPPAPPPPPPPAPPPPPA", "PPPPPPPPPPPPPPAPPPPA", "PPPPAPPPPAPPPAPPPPPP", "PPPPPPPPPPAPPPAPPPPP", "PPAAPPPPAPPPPPPPPPPP", "PPPAPPPAPPPAPPPPPPPP", "PPAPPAAPPAPPPPPAPPPP", "PPPPAPPPPPPPPPPPPPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(19, theObject.getBoard(board,  1000),57);
}
    
{
    string boardARRAY[]={"APPPPPAAAPPAPPPPPPPA", "PPPPPPAPPPAPPP.PPPPP", "PPPPPAPPPPPPPPPPPAPP", "PPPPPAPPPPPPPPAPPPAP", "PPPPPPPPPPPPPPAPPPAP", "PAPPPPAPPPPPPPPPPPPA", "PPAPPAPAPPPPPPPAPPPP", "PPPPAPPPPPPPPPPPAAPP", "PPPPPPPPPPPPPAPPPPAP", "PPAPPPPPPPPPPPPPPPPP", "PPPAPPAPPPPPPAAPPPPP", "PPPPPAPPPPPAAPPPPPPA", "PPAPPAPPPPPPPAPPPPPA", "PPPPPPPPPPPPPPAPPPPA", "PPPPAPPPPAPPPAPPPPPP", "PPPPPPPPPPAPPPAPPPPP", "PPAAPPPPAPPPPPPPPPPP", "PPPAPPPAPPPAPPPPPPPP", "PPAPPAAPPAPPPPPAPPPP", "PPPPAPPPPPPPPPPPPPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(20, theObject.getBoard(board,  15),12);
}
    
{
    string boardARRAY[]={"PAAAAAAAAAAAPAAPAAAA", "AAAAAAAAAPAPAAAAAAAP", "PPPAAAAAAAAAAPAAAPPA", "AAAAAAAPAAAAAAAAAAAA", "AAAAPAAAPAAAAAAAAAAA", "AAAAAPAAPAAAAPAAAAAA", "APAAAAAAAPAAAAAAAPAA", "AAAAAPAAAAAAPAPAAPAA", "AAPAAPAAAAAAPAAPAPAA", "APAAAAAAAAAAPAAAAAPA", "AAAPAAAAAPPAAAAAPAAA", "AAAAAAAAPPAAPAAAAAAA", "AAAPAAAPAAAAAAAPAAAA", "PAPAAAAAPAAAAAAAPAAA", "AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAPAAAAA", "PAAAAPAAAAAPAAAAAAAP", "AAAAPAAAAAAAAAAAAAAP", "AAPAAAAAAAAPAAAAAAAA", "AAAAAPAAAAAAPAAA.PAP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(21, theObject.getBoard(board,  59),224);
}
    
{
    string boardARRAY[]={".P.PP...PP.P", "P.P....P.P.P", "....P.PP...P", ".P.PP.PPP...", "....PP....P.", "P..PP.PPP.P.", "...P.P.PP.PP", ".PP.P.......", "..P.PP.PPPPP", "PPP....PP.PP", "..P.P...PPP.", "APPP.P.PP.PP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(22, theObject.getBoard(board,  998),1);
}
    
{
    string boardARRAY[]={"..PPAA...AAP", "P.AA.P....P.", ".P.P.AP.A.AP", ".A.PAAA..A.P", "AAP.APPAPPAA", ".AP..A.PAPPA", "PPPA.PPPA.PA", "A..A....P.A.", "A.APAAPAP.AP", "APA.APAAPPPA", "AAPA.A.PAPP.", "P....AP.AA.."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(23, theObject.getBoard(board,  12),20);
}
    
{
    string boardARRAY[]={"AAA.AAPPPA", "P.P.A.PAA.", "AAAA..A..P", ".PP.APP.PP", "A.PPA.P...", "PA.APP.PPA", "A..PAPAAP.", "AAA.P.P.P.", ".PAP.AA...", "AAAAPPP.AP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(24, theObject.getBoard(board,  11),18);
}
    
{
    string boardARRAY[]={"A.APAPAA.A.", "A.PPP...PP.", ".PPPP.P.PP.", "P.PPP.PPP.P", "P..P...P.P.", "P.PPPP...PP", "..P.PPP..PP", "...PP.P..P.", ".PP..P..PP.", "P.PPP.P.P..", "P.P....P.PP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(25, theObject.getBoard(board,  261),7);
}
    
{
    string boardARRAY[]={"APPAA.P..A.PP", "PA..AA.AP.AAA", "..PP.P..PPP.P", "P.P...PP...PP", ".PP....P.P.PP", ".P.PPPP.P..PP", "P.P.P..PPPPP.", "P..P.P.PP....", "PP..PP.PPP.PP", ".P..PP..P..P.", "...P....P....", "..PP.P.PP.P.P", "PPPP.P.P....P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(26, theObject.getBoard(board,  659),11);
}
    
{
    string boardARRAY[]={"PP.AAAA....APA.", "A.AAA..AA.PP.A.", "..PPPP..P..PP.P", "..PP.PPP....PPP", "...PPPP.P..PPPP", ".P.....P.P....P", "PP.......P..P..", "..PP..P.PP...PP", "P.P...P.PP.P.PP", "P.P..PPP.PP..P.", "PP.......PPPP.P", "P.PP..PPP.P.P..", "..PP.PPPP..P...", ".PP...PP.PPPP..", "P.P...P....PPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(27, theObject.getBoard(board,  123),13);
}
    
{
    string boardARRAY[]={"AAPPA.AAAAA.A", "AAAPAPPPA..P.", "P..PPPPPP.P..", "..P...P...P..", "P.P.P.PPPP.PP", "PP.P.P.PP...P", ".....P..P..PP", "P.P..P..PP...", "PPP.P.PP.P..P", "P.PPPPPPP..P.", ".P.....P..PPP", "P.PP..PP..P.P", "..P..P.P..P.."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(28, theObject.getBoard(board,  221),14);
}
    
{
    string boardARRAY[]={"PA...PAPAA...A", "APAA.A.PA..P..", "..AAPAAPA.P.P.", ".....P.P.P....", "P.PPP.P.PPPP..", ".P.PPPPPP..P.P", "P..PPP..PPPP.P", "..P...P.PP...P", ".P..PPP..P.P..", "P.P.....PPP...", "..PP..PPPP..P.", "....PP...PPPPP", "PP.PPPP.P...P.", "P...PPP..P.PPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(29, theObject.getBoard(board,  155),15);
}
    
{
    string boardARRAY[]={"...AAPAPAAAAAP.A", "..PAAA.PAAPA.PP.", "APPPPP.....PP.P.", "PP.PP...P.P...PP", "PPPP.....P..PP..", "..PP.PPP.P.PP.P.", "P.P.P.PP..P.P.PP", ".P...PPPP..PPP.P", ".PPP...P.P....P.", "...PP.PPPP.PPPP.", "PPP.PPPPPPP.P.PP", "....PP.P.P.PPP.P", "...PP.P.......P.", ".P.P.PPP..P.P.P.", "..PP..P.P..PPPP.", "PP.PPP..P..PP..."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(30, theObject.getBoard(board,  169),16);
}
    
{
    string boardARRAY[]={"PAPAAAAP.PP.PP.AAP", "AAAAA.PPP.AAAAP.AP", "...P.P.PPPPP.P.PP.", "PP.PP..P........P.", "PPP.PPP.PPPP..PP.P", "PPPPP...P..P..PP.P", ".....PP..PP.PPPP..", ".PP.PPPP...PPP...P", "PPPPP....PPPPPP.PP", "....P.PPPPPPP.P.P.", "PPP.PP.P..PP.P.PPP", "P.P...P.PPP.PPP..P", "..PP.PPPP.PP.P..PP", ".....PPP.P.P.P.P..", ".PP..PP.P..P..PPPP", "PPPPPP.PP..P.P..P.", "..P.P.P.PPP.PPPP..", ".PPPPP..P.P.PPP.P."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(31, theObject.getBoard(board,  899),17);
}
    
{
    string boardARRAY[]={"AAA.AA.AAA.PAA", "PP.APPA.A.AAAA", "PA..P..P.P....", "P.PPPPP..P..PP", "P..PP.PP.PP...", ".P.PP.P.P..PP.", "....P...P.PP.P", "...PPP.PP.PP..", "..P....PPPP..P", "...P.P..P....P", ".P.P.P..P.P.PP", ".P.P.PP..PPP..", ".PPPPP.PPP.P..", "..PPPPP...PP.."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(32, theObject.getBoard(board,  678),18);
}
    
{
    string boardARRAY[]={".PAAAA..APP.A.AP", ".PPAPPAPAAA..APP", "AAA.PAAAP..PPP..", ".PPP..P....PPP.P", "P..P.PP.P.P.PP..", "PP..PPPPPPP.P...", "..P..PP...P.....", "P.PPP..P...P.PP.", "..P....PPPP....P", "P.PP.PP..P.P....", "PPP.P..PPPP..PPP", "P.PP..PP..P.P.PP", "PP.PPPP...P.P..P", "PP...P.P...P.P.P", "..P..P...P.PP...", ".PPPPP...PP.PP.."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(33, theObject.getBoard(board,  133),18);
}
    
{
    string boardARRAY[]={"A.AAA.APA.P.PPAPA.PA", "AAAPA..AAA.P.PPPPAAA", "PP.PP..PP.P...P...PP", "....P..P...PP..P.P..", "P.P.PPP.PPPP.PPP..PP", "P..PPP.P....P.P.....", "PPP..PP..PP..P.PPP.P", "P.PP.PP.PPPP.PP..PPP", ".PP.PPP.P.PP.P.P.PP.", ".P..P.P.P..PPP...PPP", ".P.PPPPPP.PP..PP...P", "...PP.PPP..PP.PPPP..", ".P....P..P.P.PPP...P", "P.PPPP.PP......P....", "...P.P.PPPP..PPPP...", "..P.PPP..PPPP..PPP..", "..P.P....P..PP......", "PPP..P.P..P.......P.", "P...P.P..P...P.P.P.P", "PPP..PPPPP.P...PP..."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(34, theObject.getBoard(board,  131),19);
}
    
{
    string boardARRAY[]={"AAAAPA.APAAP.AAAAPAA", "P.A.A.AA.AA...PP..P.", "P..P.PPPP.PP..P.PP..", "P..P.PPPPP..P..PP..P", ".P.PP.PP.....PPPPP.P", "..PPPP.PPPPPP..P....", "...PPPPP..P.PP...P..", "PP...PPPP..PP...PPP.", "PP....PPP.P.P.PPPPPP", ".....P..........PPPP", "P..PP..P..P..PPP.PP.", "...P.P.P..P.P.P...P.", "PP.P..P.P.PP.PP..PPP", "....PP.P.PP.PP......", "PPP.PP...P..P....P.P", ".P.P...P..PPPPPPPP.P", ".P....PP.P.PP.P.P..P", "PP..P.PPP.PPPP..P.PP", "P...PP...P.P..P.P...", "PPPP...P.PP....P.P.P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(35, theObject.getBoard(board,  531),20);
}
    
{
    string boardARRAY[]={".PPPAA..P.", "A.AAAAAP.A", "AAP.PAP.PP", "AAA...P.A.", ".AAPPAA.P.", "P..PPPPP.P", "P...P.....", "P...PPPPP.", "PP..P...PP", "..P.P.PP.P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(36, theObject.getBoard(board,  341),20);
}
    
{
    string boardARRAY[]={"AAAAA", "AAAAA", "AAAAA", "AAAAA", ".P..P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(37, theObject.getBoard(board,  1),20);
}
    
{
    string boardARRAY[]={"AAAAAA", "AAAAAA", "AAAAAA", "P.PP.P", "....P.", "PP.P.P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(38, theObject.getBoard(board,  1),18);
}
    
{
    string boardARRAY[]={"AAP.A.P.P", ".AA.PA.AP", ".A.PPAA..", "APPPAA.A.", "A.PAPAA..", "PP.P..PPP", "PPP.P.PPP", ".PPP.PPP.", "P...P.P.P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(39, theObject.getBoard(board,  123),18);
}
    
{
    string boardARRAY[]={".PA.AAPA", "A...P.AA", "A..APA.P", "A.AAAAA.", "..P.P.P.", ".P.P...P", "...P....", "PPP..PPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(40, theObject.getBoard(board,  795),16);
}
    
{
    string boardARRAY[]={"AAAAA", "AAAAA", "AAAAA", ".P..P", "PP.P."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(41, theObject.getBoard(board,  189),15);
}
    
{
    string boardARRAY[]={"AAP.A", ".AAA.", "AA.AA", "..PP.", "PPPP."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(42, theObject.getBoard(board,  11),10);
}
    
{
    string boardARRAY[]={".A.A", "PPAP", "A.PP", "APA."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(43, theObject.getBoard(board,  99),6);
}
    
{
    string boardARRAY[]={"A.AA.", "AAAA.", "AAPAP", "A..P.", ".P..."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(44, theObject.getBoard(board,  677),10);
}
    
{
    string boardARRAY[]={"AAAAA", ".PAAP", ".PP..", "P...P", ".PPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(45, theObject.getBoard(board,  333),6);
}
    
{
    string boardARRAY[]={"AAAAP.PA", "PPAAP...", "PPP.P.P.", "PP.P..PP", ".P.P....", "P....PPP", "..P.P...", ".P.P.P.P"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(46, theObject.getBoard(board,  11),7);
}
    
{
    string boardARRAY[]={"A..AAPPPAAAAPA.P", "PPPAAA..AP..PAPP", "A.PAAAPAAPA.PA.A", "AP.PAAA.A.PAAAAA", "....P..A..AP..AP", ".PA.A.AAP.P.P.AA", "A.AP.....A.PAPA.", ".AAPA..AAA.PA.A.", ".P.PAPAAPPAPAAA.", "PA.APA...AAAPPPP", ".P.PP..A.PP..A.A", "APP.A.PP.APPPPAA", "...AAAAPPPPPAP.A", "PP.PPAP.PAAA.AP.", "PAAP.AAP.AA.APPA", "AA.PPPAAA.PAPAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(47, theObject.getBoard(board,  1000),100);
}
    
{
    string boardARRAY[]={"AAAAA", "AAAAA", "AAAAA", "AA...", "....."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(48, theObject.getBoard(board,  1000),16);
}
    
{
    string boardARRAY[]={"AAAA", "AAPP", "PPPP", "PAA."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(49, theObject.getBoard(board,  4),8);
}
    
{
    string boardARRAY[]={"AAPAAP.PPP", "AAPAAPPPPA", "AAPAAPPPAA", "PPPPPPPPPP", "PPPPPPPPPP", "PPPPPPPPPP", "PPPPPPPPPP", "PPPPPPPPPP", "PPPPPPPPPP", "PPPPPPPPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(50, theObject.getBoard(board,  6),15);
}
    
{
    string boardARRAY[]={"AAAP", "PPAP", "AAAP", "P.AA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(51, theObject.getBoard(board,  1000),9);
}
    
{
    string boardARRAY[]={".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".A.A.A.A.A.A.A.A.A.A", ".AAAAAAAAAAAAAAAAAP.", ".A.A.A.A.A.A.A.A.A.A"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(52, theObject.getBoard(board,  10),36);
}
    
{
    string boardARRAY[]={"PP", "PP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(53, theObject.getBoard(board,  1),0);
}
    
{
    string boardARRAY[]={".AAA", "APPP", "AAAA", "APPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(54, theObject.getBoard(board,  20),9);
}
    
{
    string boardARRAY[]={"AP.A", "PPPP", "PPAA", "PPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(55, theObject.getBoard(board,  3),4);
}
    
{
    string boardARRAY[]={"PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAPA", "PAPAPAPAPAPAPAPAPAP."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(56, theObject.getBoard(board,  1000),198);
}
    
{
    string boardARRAY[]={"APA", "PP.", "AAP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(57, theObject.getBoard(board,  1000),4);
}
    
{
    string boardARRAY[]={".AAAPPPAAA", ".AAAPPPAAA", ".AAAPPPAAA", ".AAAPPPAAA", ".AAAPPPAAA", ".AAAPPPAAA", ".AAAPPPAAA", ".AAAPPPAAA", ".AAAPPPAAA", ".AAAPPPAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(58, theObject.getBoard(board,  60),60);
}
    
{
    string boardARRAY[]={"APPPPP", "PAAAAP", "PAAAAP", "PAAP.P", "PPPPPA", "PPPPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(59, theObject.getBoard(board,  3),12);
}
    
{
    string boardARRAY[]={"AA", "A."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(60, theObject.getBoard(board,  100),2);
}
    
{
    string boardARRAY[]={"APPP", "PAPP", ".PAP", "PPPA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(61, theObject.getBoard(board,  4),4);
}
    
{
    string boardARRAY[]={"AAA..", "AAA..", "A....", ".....", "....."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(62, theObject.getBoard(board,  100),6);
}
    
{
    string boardARRAY[]={"PPPPPPPPAPAP", "AAAAPPPAPAPP", "AAAPPPPA.PAA", "APAAPAPAPPAP", "PPAAAPAPPAAA", "PAAPAAPAPAAP", "AAAPPAPPAPPP", "AAPAAAAPPPPP", "AAPAAAPPAPAP", "APPPAPPPPPAP", "PAPPAPAAAPAA", "PAPPPAPPAAAP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(63, theObject.getBoard(board,  376),66);
}
    
{
    string boardARRAY[]={"APP", "A.A", "PPA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(64, theObject.getBoard(board,  3),4);
}
    
{
    string boardARRAY[]={"AAA...", "A.A...", "AAA...", "...AAA", "...AAA", "...AAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(65, theObject.getBoard(board,  0),9);
}
    
{
    string boardARRAY[]={"AA.P", "PPAP", "PPPA", "PPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(66, theObject.getBoard(board,  3),4);
}
    
{
    string boardARRAY[]={"A.AP", "PPAA", "AAAA", "AAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(67, theObject.getBoard(board,  4),12);
}
    
{
    string boardARRAY[]={"AA.A", "PPPA", "PPPA", "AAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(68, theObject.getBoard(board,  13),9);
}
    
{
    string boardARRAY[]={"AAAP", "APAA", "AAAP", "PPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(69, theObject.getBoard(board,  100),3);
}
    
{
    string boardARRAY[]={"APA", "A.P", "AAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(70, theObject.getBoard(board,  50),6);
}
    
{
    string boardARRAY[]={"..AAA", "A..AA", "AAA.A", "....A", "AAAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(71, theObject.getBoard(board,  10),16);
}
    
{
    string boardARRAY[]={"APAP", "PAPA", "APAP", "PPP."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(72, theObject.getBoard(board,  6),6);
}
    
{
    string boardARRAY[]={"APAP", "PAPA", "APAP", "PAP."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(73, theObject.getBoard(board,  400),6);
}
    
{
    string boardARRAY[]={"AAAA", "A.PA", "APPA", "AAAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(74, theObject.getBoard(board,  15),12);
}
    
{
    string boardARRAY[]={"PPPA.", "PAAAP", "PAAAP", "PAPPP", "APPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(75, theObject.getBoard(board,  100),9);
}
    
{
    string boardARRAY[]={"AAAA", "..PP", "AAAA", "PPPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(76, theObject.getBoard(board,  6),8);
}
    
{
    string boardARRAY[]={"PPP", "APA", "A.A"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(77, theObject.getBoard(board,  10),4);
}
    
{
    string boardARRAY[]={"PAP", "A.A", "PAP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(78, theObject.getBoard(board,  1000),4);
}
    
{
    string boardARRAY[]={"AAAPP", "A.PPP", "AAAPP", "PPPPP", "PPPAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(79, theObject.getBoard(board,  3),9);
}
    
{
    string boardARRAY[]={"...", ".A.", "..A"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(80, theObject.getBoard(board,  1000),2);
}
    
{
    string boardARRAY[]={"P.....P", "PAP..PP", "PA.APAP", "..AAAP.", ".PPPP.P", "..PAP..", "APPA.P."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(81, theObject.getBoard(board,  9),10);
}
    
{
    string boardARRAY[]={"APP", "PAP", ".PA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(82, theObject.getBoard(board,  3),3);
}
    
{
    string boardARRAY[]={"AAA", "AAA", "PPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(83, theObject.getBoard(board,  100),6);
}
    
{
    string boardARRAY[]={"AAAAAAAAAA..........", "PPPPPPPPPP..........", "AAAAAAAAAA..........", "PPPPPPPPPP..........", "AAAAAAAAAA..........", "PPPPPPPPPP..........", "PPPPPPPPPP..........", "AAAAAAAAAA..........", "PPPPPPPPPP..........", "AAAAAAAAAA..........", "PPPPPPPPPP..........", "AAAAAAAAAA..........", "AAAAAAAAAA..........", "PPPPPPPPPP..........", "AAAAAAAAAA..........", "PPPPPPPPPP..........", "AAAAAAAAAA..........", "PPPPPPPPPP..........", "AAAAAAAAAA..........", "PPPPPPPPPP.........."};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(84, theObject.getBoard(board,  1000),100);
}
    
{
    string boardARRAY[]={"AAAA", "APP.", "PPAA", "APPP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(85, theObject.getBoard(board,  7),8);
}
    
{
    string boardARRAY[]={"AAP", "PPP", ".AA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(86, theObject.getBoard(board,  4),4);
}
    
{
    string boardARRAY[]={"AAP", ".PA", "APP"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(87, theObject.getBoard(board,  3),4);
}
    
{
    string boardARRAY[]={"AAA", "P.P", "PPA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(88, theObject.getBoard(board,  3),4);
}
    
{
    string boardARRAY[]={"AAAAAP", "AAAAAP", "AAAAAP", "AAAAAP", "AAAA.P", "PPPPAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(89, theObject.getBoard(board,  1),25);
}
    
{
    string boardARRAY[]={"AAA", "PPP", "AAA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(90, theObject.getBoard(board,  10),3);
}
    
{
    string boardARRAY[]={"AAAP", "AP.P", "AAAP", "PAPA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(91, theObject.getBoard(board,  3),9);
}
    
{
    string boardARRAY[]={"AAP", ".PA", "PPA"};
    vector<string> board(boardARRAY, boardARRAY+ARRSIZE(boardARRAY) );
    UniformBoard theObject;
    eq(92, theObject.getBoard(board,  3),4);
}
}
// END CUT HERE
