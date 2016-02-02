class BearFair {
public:
#define ut( _x ) vec[ _x ].first
#define qu( _x ) vec[ _x ].second
	string isFair(int n, int b, vector <int> upTo, vector <int> quantity) {
		int cnq = upTo.size();
		vector< pair<int, int> > vec;
		vec.push_back(make_pair(0, 0));
		for (int i = 0; i < cnq; i++)
			vec.push_back(make_pair(upTo[i], quantity[i]));
		vec.push_back(make_pair(b, n));
		sort(vec.begin(), vec.end());
		int mxe = 0, mxo = 0, mxc = 0;
		mxe = min(ut(0) / 2, qu(0));
		mxo = min((ut(0) + 1) / 2, qu(0));
		for (int i = 1; i <= cnq + 1; i++) {
			if (qu(i) < qu(i - 1)) return "unfair";
			if (ut(i) == ut(i - 1) && qu(i) != qu(i - 1)) return "unfair";
			if (ut(i) - ut(i - 1) < qu(i) - qu(i - 1)) return "unfair";
			mxe += min(ut(i) / 2 - ut(i - 1) / 2, qu(i) - qu(i - 1));
			mxo += min((ut(i) + 1) / 2 - (ut(i - 1) + 1) / 2, qu(i) - qu(i - 1));
		}
		return (mxe < n / 2 || mxo < n / 2) ? "unfair" : "fair";
	}
};
