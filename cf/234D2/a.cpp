#include <bits/stdc++.h>
using namespace std;
char s[15];
void work()
{
	vector<pair<int , int> > ans;
	int arr1[] = {1 , 2 , 3 , 4 , 6 , 12};
	int arr2[] = {12 , 6 , 4 , 3 , 2 , 1};
	for (int i = 0 ; i < 6 ; i++)
	{
		bool flag = false;
		for (int j = 0 ; j < arr2[i] ; j++)
		{
			bool flag2 = true;
			for (int k = 0 ; k < arr1[i] ; k++)
				flag2 = flag2 && (s[ arr2[i]*k + j ] == 'X');
			flag = flag || flag2;
		}
		if (flag)
			ans.push_back( make_pair( arr1[i] , arr2[i] ) );
	}
	printf("%d",ans.size());
	for (unsigned int i = 0 ; i < ans.size() ; i++)
		printf(" %dx%d" , ans[i].first , ans[i].second);
	printf("\n");
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		scanf("%s" , s),work();
	return 0;
}
