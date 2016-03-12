#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
int main() {
	for (int i = 1; i <= 5000; i++) {
		int sz = i, lpos = 0;
		cerr << i << endl;
		set<int> s;
		for (int j = 1; j <= i; j++) s.insert(j);
		for (int l = 1; l <= i; l++) {
			if(l == i) {
				printf("%d,\n", *s.begin());
				break;
			} else {
				int nxt = (lpos + l - 1) % sz;
				auto pos = s.begin();
				for (int k = 0; k < nxt; k++) {
					pos++;
				}
				sz--;
				(lpos = nxt) %= sz;
				s.erase(pos);
			}
		}
	}
	return 0;
}
