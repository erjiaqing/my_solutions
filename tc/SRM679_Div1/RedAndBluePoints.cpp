typedef pair<int, int> pii;
#define x first
#define y second
const int maxn = 55;
class RedAndBluePoints {
public:
	int inner[maxn][maxn][maxn];
	int upb[maxn][maxn], upr[maxn][maxn];
	int innerb[maxn][maxn][maxn], innerr[maxn][maxn][maxn];
	int dp1[maxn][maxn][maxn], dp2[maxn][maxn][maxn];
	vector<pii> bl, rd;
	int cross(const pii &a, const pii &b) {
		return a.x * b.y - a.y * b.x;
	}
	pii _(const pii &a, const pii &b) {return pii(a.x - b.x, a.y - b.y);}
	bool isinner(const pii &a, const pii &b, const pii &c, const pii &q) {
		return (q != a && q != b && q != c && 
		cross(_(q, a), _(b, a)) >= 0 && cross(_(q, b), _(c, b)) >= 0 && cross(_(q, c), _(a, c)) >= 0);
	}
	int eabs(const int &x) {return x < 0 ? -x : x;}
	int find(vector <int> blueX, vector <int> blueY, vector <int> redX, vector <int> redY) {
		int b = blueX.size(), r = redX.size();
		int ans = min(2, b);
		memset(inner, 0, sizeof(inner));memset(upb, 0, sizeof(upb));memset(upr, 0, sizeof(upr));
		memset(innerb, 0, sizeof(innerb));memset(innerr, 0, sizeof(innerr));
		memset(dp1, -1, sizeof(dp1));memset(dp2, -1, sizeof(dp2));
		for (int i = 0; i < b; i++) bl.push_back(pii(blueX[i], blueY[i]));
		for (int i = 0; i < r; i++) rd.push_back(pii(redX[i], redY[i]));
		sort(bl.begin(), bl.end());
		for (int i = 0; i < b; i++)
			for (int j = i + 1; j < b; j++)
				for (int k = 0; k < b; k++)
					if (cross(_(bl[k], bl[i]), _(bl[j], bl[i])) > 0) {
						for (int l = 0; l < b; l++)
							innerb[i][j][k] += isinner(bl[i], bl[j], bl[k], bl[l]);
						for (int l = 0; l < r; l++)
							innerr[i][j][k] += isinner(bl[i], bl[j], bl[k], rd[l]);
						if(innerr[i][j][k] == 0)
							ans = max(ans, dp1[i][j][k] = dp2[i][k][j] = innerb[i][j][k] + 3);
					}
		for (int i = 0; i < b; i++)
			for (int j = i + 1; j < b; j++)
				for (int k = j + 1; k < b; k++)
					for (int l = k + 1; l < b; l++)
						if (innerr[i][k][l] == 0 && cross(_(bl[l], bl[i]), _(bl[k], bl[i])) > 0 && cross(_(bl[l], bl[j]), _(bl[k], bl[j])) > 0)
							dp1[i][k][l] = max(dp1[i][k][l], dp1[i][j][k] + innerb[i][k][l] + 1), ans = max(ans, dp1[i][k][l]);
		for (int i = 0; i < b; i++)
			for (int j = i + 1; j < b; j++)
				for (int k = j + 1; k < b; k++)
					for (int l = k + 1; l < b; l++)
						if (innerr[i][l][k] == 0 && cross(_(bl[l], bl[i]), _(bl[k], bl[i])) < 0 && cross(_(bl[l], bl[j]), _(bl[k], bl[j])) < 0)
							dp2[i][k][l] = max(dp2[i][k][l], dp2[i][j][k] + innerb[i][l][k] + 1), ans = max(ans, dp2[i][k][l]);
		for (int i = 0; i < b; i++)
			for (int j = i + 1; j < b; j++)
				for (int k = i + 1; k < j; k++)
					for (int l = i + 1; l < j; l++)
						if (k != l)
							ans = max(ans, dp1[i][k][j] + dp2[i][l][j] - 2);
		return ans;
	}
};

