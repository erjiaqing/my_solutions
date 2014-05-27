#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int numbers[6];
const double eps=1e-6;
bool _eq(double a,double b){return fabs(a-b)<eps;}
int get(double before,int dep)
{
	if (dep==4)
		return _eq(before,24);
	int ans=0;
	ans+=get(before*numbers[dep],dep+1);
	ans+=get(before+numbers[dep],dep+1);
	ans+=get(before/numbers[dep],dep+1);
	ans+=get(before-numbers[dep],dep+1);
	return ans;
}
int main()
{
	int ans=0;
	scanf("%d%d%d%d",&numbers[0],&numbers[1],&numbers[2],&numbers[3]);
	sort(&numbers[0],&numbers[4]);
	while (next_permutation(&numbers[0],&numbers[4]))
		ans+=get(numbers[0],1);
	printf("%d\n",ans);
	return 0;
}
