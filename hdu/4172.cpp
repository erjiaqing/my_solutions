#include <vector>
#include <utility>
#include <string>
#include <cstdio>
using namespace std;

typedef pair<string,string> pss;

int n;
char buf[64];

vector < pss > a;
bool chk(string s)
{
	int k;
	if (s.empty()) return true;
	for (int i = 0; i < a.size() ; i++ )
		if ((k = s.find(a[i].first)) != string::npos)
			return chk(s.substr( 0, k) + a[i].second + s.substr(k + a[i].first.size()));
	return false;
}
void init()
{
	a.push_back( pss("aa","") );
	a.push_back( pss("bb","") );
	a.push_back( pss("cc","") );
	a.push_back( pss("abab","baba") );
	a.push_back( pss("acac","caca") );
	a.push_back( pss("bcbc","cbcb") );
}
int main()
{
	init();
	scanf("%d", &n);
	while (n--)
		scanf("%s",buf),printf("%s\n",(chk(buf)?"closed":"open"));
	return 0;
}

