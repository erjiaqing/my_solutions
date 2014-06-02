#include <bits/stdc++.h>
using namespace std;
char Map[500][500];
int valid0[405][405], /* -> */
     valid1[405][405], /* |  */
     valid2[405][405], /* \  */
     valid3[405][405]; /* /  */
int n,m,ans;
bool vaild(int x,int y) //spell error =.=
{
	return (!(x<1 || x>n || y<1 || y>m || Map[x][y]=='1'));
}
int Calc(int x,int y,int l)
{
	int ret=0;
	ret+=(vaild(x-l,y) && vaild(x,y-l) && 
	     (valid0[x][y]-valid0[x-l][y]==0) && 
	     (valid1[x][y]-valid1[x][y-l]==0) &&
	     (valid3[x][y-l]-valid3[x-l][y]==0));
//cout<<ret;
/*
  /|
 / |
/  |
---+
*/
	ret+=(vaild(x-l,y) && vaild(x,y+l) && 
	     (valid0[x][y]-valid0[x-l][y]==0) && 
	     (valid1[x][y+l]-valid1[x][y]==0) &&
	     (valid2[x][y+l]-valid2[x-l][y]==0));
//cout<<ret;
/*
|\
| \
|  \
+---
*/

	ret+=(vaild(x+l,y) && vaild(x,y-l) && 
	     (valid0[x+l][y]-valid0[x][y]==0) && 
	     (valid1[x][y]-valid1[x][y-l]==0) &&
	     (valid2[x+l][y]-valid2[x][y-l]==0));
//cout<<ret;
/*
---+
\  |
 \ |
  \|
*/
	ret+=(vaild(x+l,y) && vaild(x,y+l) && 
	     (valid0[x+l][y]-valid0[x][y]==0) && 
	     (valid1[x][y+l]-valid1[x][y]==0) &&
	     (valid3[x+l][y]-valid3[x][y+l]==0));
//cout<<ret;
/*
+---
|  /
| /
|/
*/
	ret+=(vaild(x-l,y-l) && vaild(x+l,y-l) &&
         (valid0[x+l][y-l] - valid0[x-l][y-l] == 0) &&
         (valid2[x][y] - valid2[x-l][y-l] == 0) &&
         (valid3[x+l][y-l] - valid3[x][y] == 0));
//cout<<ret;
/*
|\
| *
|/
*/
	ret+=(vaild(x-l,y-l) && vaild(x-l,y+l) &&
         (valid1[x-l][y+l] - valid1[x-l][y-l] == 0) &&
         (valid2[x][y] - valid2[x-l][y-l] == 0) &&
         (valid3[x][y] - valid3[x-l][y+l] == 0));
//cout<<ret;
/*
\-/
 *
*/
	ret+=(vaild(x+l,y+l) && vaild(x+l,y-l) &&
         (valid1[x+l][y+l] - valid1[x+l][y-l] == 0) &&
         (valid2[x+l][y+l] - valid2[x][y] == 0) &&
         (valid3[x+l][y-l] - valid3[x][y] == 0));
//cout<<ret;
/*
 *
/-\
*/
	ret+=(vaild(x+l,y+l) && vaild(x-l,y+l) &&
         (valid0[x+l][y+l] - valid0[x-l][y+l] == 0) &&
         (valid2[x+l][y+l] - valid2[x][y] == 0) &&
         (valid3[x][y] - valid3[x-l][y+l] == 0));
//cout<<ret;
//cout<<' ';
/*
 /|
* |
 \|
*/
	return ret;
}
int main()
{
//	memset(Map,'1',sizeof(Map));
	ios::sync_with_stdio(0);
	cin>>n>>m;
//    cout<<n<<" "<<m<<endl;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			cin>>Map[i][j];
//    for (int i=1;i<=n;i++)
//        for (int j=1;j<=m;j++)
//            cout<<Map[i][j]<<(j==m?'\n':' ');
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
        {
			valid0[i][j]=valid0[i-1][j]+Map[i][j]-'0';
			valid1[i][j]=valid1[i][j-1]+Map[i][j]-'0';
			valid2[i][j]=valid2[i-1][j-1]+Map[i][j]-'0';
		}
        for (int j=m;j>=1;j--)
			valid3[i][j]=valid3[i-1][j+1]+Map[i][j]-'0';
	}
//    for (int i=1;i<=n;i++)
//    {
//        for (int j=1;j<=m;j++)
 //       {
//            cout<<valid0[i][j]<<valid1[i][j]<<" ";
 //       }
//        cout<<endl;
 //   }
	int l=min(n,m);
	int tans=0;
	for (int i=1;i<=l;i++)
		for (int x=1;x<=n;x++)
			for (int y=1;y<=m;y++)
				if (Map[x][y]=='0')
				{
					tans=Calc(x,y,i);
//					cout<<x<<" "<<y<<" "<<i<<" "<<tans<<endl;
					ans+=tans;
				}
	cout<<ans<<endl;
	return 0;
}

