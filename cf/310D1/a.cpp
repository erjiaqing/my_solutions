#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
int n , m;
int v[maxn],b[maxn];
int main()
{
	int ts,pos = 0;
	int n_take_apart = 0;
	scanf("%d%d",&n,&m);
	for (int i = 0 ; i < m ; i++)
	{
		scanf("%d",&ts);
		b[i] = pos;
		for (int j = 0 ; j < ts ; j++)
			scanf("%d", &v[pos++]);
	}
	b[m] = pos;
	for (int i = 0 ; i < m ; i++)
		if (v[b[i]] == 1)
			for (int j = b[i] ; j < b[i + 1] - 1 ; j++)
				if (v[j + 1] == v[j] + 1)
					n_take_apart++;
				else
					break;
	printf("%d\n",(n - 1) * 2 - m + 1 - n_take_apart * 2);
	return 0;
}
