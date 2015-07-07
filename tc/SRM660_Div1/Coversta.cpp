#include <bits/stdc++.h>
using namespace std;
struct Coversta{
//    #define maxn (105);
	int Map[105][105];
	pair<int ,int > xy[10 + 5];
	vector< pair< int , pair< int , int > > > sol;
	int x1 = -1 , y1 = -1;
	int n , m , k;
	int get_max()
	{
		int tx , ty  , ans = 0 , tans;
		sol.clear();
		for (int i = 0 ; i < n ; i++)
			for (int j = 0 ; j < m ; j++)
			{
				tans = 0 ;
				for (int kk = 0 ; kk < k ; kk++)
				{
					tx = i + xy[kk].first;
					ty = j + xy[kk].second;
					if (0 <= tx && tx < n && 0 <= ty && ty < m)
						tans += Map[tx][ty];
				}
				sol.push_back(make_pair(tans , make_pair(i,j)));
			}
		sort(sol.begin() , sol.end() , greater< pair< int , pair< int , int > > >());
		int max_iter = min(k * k + 1 , m * n);
		for (int i = 0 ; i < max_iter ; i++)
		{
			map< pair<int,int> , bool > sel;
			tans = sol[i].first;
			for (int kk = 0 ; kk < k ; kk ++)
			{
				tx = sol[i].second.first + xy[kk].first;
				ty = sol[i].second.second + xy[kk].second;
				if (0 <= tx && tx < n && 0 <= ty && ty < m)
					sel[make_pair(tx , ty)] = true;
			}
			for (int j = i + 1 ; j < max_iter ; j++)
			{
				tans = sol[i].first + sol[j].first;
				for (int kk = 0 ; kk < k ; kk ++)
				{
					tx = sol[j].second.first + xy[kk].first;
					ty = sol[j].second.second + xy[kk].second;
					if (0 <= tx && tx < n && 0 <= ty && ty < m && sel[make_pair(tx , ty)])
						tans -= Map[tx][ty];
				}
				ans = max(ans , tans);
			}
		}
		return ans;
	}
	int place(vector <string> a, vector <int> x, vector <int> y)
	{
		n = a.size() , m = a[0].size() , k = x.size();
		for (int i = 0 ; i < n ; i++)
			for (int j = 0 ; j < m ; j++)
				Map[i][j] = a[i][j] - '0';
		for (int i = 0 ; i < k ; i++)
			xy[i] = make_pair(x[i] , y[i]);
		return get_max();
	}
};
#ifdef LOCAL
int main()
{
	Coversta Worker;
	// Case 1
	cout<<Worker.place(
			vector <string> {"11","11"} ,
			vector <int> {0,0} ,
			vector <int> {0,1})<<endl;
	// Case 2
	cout<<Worker.place(
			{"11", "11"} ,
			{0,1} ,
			{0,1})<<endl;
	// Case 3
	cout<<Worker.place(
			{"15", "61"},
			{0},
			{0})<<endl;
	// Case 4
	cout<<Worker.place(
			{"151", "655", "661"},
			{0,0,-1},
			{0,1,0})<<endl;
	// Case 5
	cout<<Worker.place(
			{"303", "333", "000"},
			{-1,-1},
			{-1,1})<<endl;
	// Case 6
	cout<<Worker.place(
			{"0000000", "1010101"},
			{-1,-1},
			{-1,1})<<endl;
	return 0;
}
#endif
