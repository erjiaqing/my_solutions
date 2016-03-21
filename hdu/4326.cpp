#include <bits/stdc++.h>
using namespace std;
const int maxn = 15;
const double eps = 1e-8;
int id[maxn][maxn];
double mat[maxn * maxn][maxn * maxn];
double x[maxn * maxn];
int mxid, cnt;
int n, m, k;
int getid(int curwin, int curpos) {
	if (curwin == m && curpos != 1) return maxn * maxn - 1;
	else if (curwin == m && curpos == 1) return maxn * maxn - 2;
	if (~id[curwin][curpos]) return id[curwin][curpos];
	return id[curwin][curpos] = mxid++;
}
void sol_mat() {
	for (int i = 0; i < mxid; i++) {
		int val = i;
		for (int j = i; j < mxid; j++)
			if (fabs(mat[j][i]) > fabs(mat[val][i]))
				val = j;
		if (val != i) {
			for (int j = 0; j < mxid; j++) swap(mat[i][j], mat[val][j]);
			swap(x[i], x[val]);
		}
		for (int j = 0; j < mxid; j++) {
			if (j == i) continue;
			double ratio = mat[j][i] / mat[i][i];
			for (int k = 0; k < mxid; k++)
				mat[j][k] -= mat[i][k] * ratio;
			x[j] -= x[i] * ratio;
		}
		for (int j = 0; j < mxid; j++) {
			if (j == i) continue;
			mat[i][j] /= mat[i][i];
		}
		x[i] /= mat[i][i];
		mat[i][i] = 1;
	}
}
double sol() {
	memset(id, -1, sizeof(id));
	memset(mat, 0, sizeof(mat));
	memset(x, 0, sizeof(x));
	mxid = cnt = 0;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; i++) {
		for (int j = 1; j <= n; j++) {
			mat[cnt][getid(i, j)] = 1;
			if (j == 1) {
				mat[cnt][getid(i + 1, 1)] -= 0.25;
				mat[cnt][getid(1, n - 2)] -= 0.75;
			} else if (j == 2) {
				mat[cnt][getid(1, 1)] -= 0.25;
				mat[cnt][getid(i + 1, n - 2)] -= 0.25;
				mat[cnt][getid(1, n - 1)] -= 0.5;
			} else if (j == 3) {
				mat[cnt][getid(1, 1)] -= 0.25;
				mat[cnt][getid(i + 1, n - 1)] -= 0.25;
				mat[cnt][getid(1, n - 1)] -= 0.25;
				mat[cnt][getid(1, n)] -= 0.25;
			} else if (j == 4) {
				mat[cnt][getid(1, 1)] -= 0.25;
				mat[cnt][getid(i + 1, n)] -= 0.25;
				mat[cnt][getid(1, n)] -= 0.5;
			} else {
				mat[cnt][getid(i + 1, j - 3)] -= 0.25;
				mat[cnt][getid(1, j - 3)] -= 0.75;
			}
			cnt++;
		}
	}
	for (int i = 0; i < cnt; i++)
		x[i] -= mat[i][maxn * maxn - 2];
	sol_mat();
	return x[getid(0, k)];
}
int main() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t;)
		printf("Case #%d: %.6f\n", ++i, sol());
	return 0;
}
