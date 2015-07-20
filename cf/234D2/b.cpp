#include <bits/stdc++.h>
using namespace std;
int n , m , a;
char p[1005];
int g[1005] , s[1005];
set <int> st;
int main()
{
	//cin >> n >> m;
	scanf("%d%d" , &n , &m);
	st.insert(1005);
	for (int i = 0 ; i < n ; i++)
	{
		scanf("%s" , p);
		for (int j = 0 ; j < m ; j++)
			if (p[j] == 'G')
				g[i] = j;
			else if (p[j] == 'S')
				s[i] = j;
		if (s[i] < g[i])
			return 0 & printf("-1\n");
		if ((*st.lower_bound(s[i]-g[i])) != s[i]-g[i])
		{
			st.insert(s[i] - g[i]);
			a++;
		}
	}
	for (int i = 0 ; i < n ; i++)
		for (int j = i + 1 ; j < n ; j++)
		{
			if (s[i] == s[j] && g[i] == g[j]) continue;
			if (g[i] == g[j] && s[i] != s[j])
				return 0 & printf("-1\n");
		}
	printf("%d\n" , a);
	return 0;
}

