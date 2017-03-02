#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

double mat[500][500];
int target[500];

struct trie{
	int next[500][6], fail[500], end[500];
	int root, l;
	int newnode()
	{
		for (int i = 0; i < 6; i++) next[l][i] = -1;
		end[l] = 0;
		return l++;
	}
	void init()
	{
		l = 0;
		root = newnode();
	}
	int insert(int *buf)
	{
		int now = root;
		while (*buf)
		{
			if (next[now][*buf - 1] == -1)
				next[now][*buf - 1] = newnode();
			now = next[now][*buf - 1];
			buf++;
		}
		end[now]++;
		return now;
	}
	void build()
	{
		queue<int> q;
		fail[root] = root;
		for (int i = 0; i < 6; i++)
			if (next[root][i] == -1) next[root][i] = root;
			else
			{
				fail[next[root][i]] = root;
				q.push(next[root][i]);
			}
		while (!q.empty())
		{
			int now = q.front();
			q.pop();
			for (int i = 0; i < 6; i++)
				if (next[now][i] == -1)
					next[now][i] = next[fail[now]][i];
				else
				{
					fail[next[now][i]] = next[fail[now]][i];
					q.push(next[now][i]);
				}
		}
	}
	void build_mat()
	{
		memset(mat, 0, sizeof mat);
		mat[root][root] = mat[root][l] = 1.;
		for (int i = 0; i < l; i++)
		{
			mat[i][i] = 1.;
			if (!end[i])
				for (int j = 0; j < 6; j++)
					mat[next[i][j]][i] += -1 / 6.;
		}/*
		for (int i = 0; i < l; i++)
		{
			for (int j = 0; j <= l; j++)
				printf("%c %.3f ", " ="[j == l], mat[i][j]);
			printf("\n");
		}*/
	}
	bool sol_mat()
	{
		int i, j, k, col, max_r;
		for (k = 0, col = 0; k < l && col < l; k++, col++)
		{
			max_r = k;
			for (int i = k + 1; i < l; i++)
				if (fabs(mat[i][col]) > fabs(mat[max_r][col]))
					max_r = i;
			if (fabs(mat[max_r][col]) < eps) return 0;
			if (k != max_r)
				for (j = col; j <= l; j++)
					swap(mat[k][j], mat[max_r][j]);
			for (j = col + 1; j <= l; j++) mat[k][j] /= mat[k][col];
			mat[k][col] = 1.;
			for (i = 0; i < l; i++)
				if (i != k)
				{
					for (j = col + 1; j <= l; j++) mat[i][j] -= mat[k][j] * mat[i][col];
					mat[i][col] = 0;
				}
		}
		return 1;
	}
}ac;

int buf[20];

void sol()
{
	int n, m;
	scanf("%d%d", &n, &m);
	ac.init();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			scanf("%d", &buf[j]);
		target[i] = ac.insert(buf);
	}
	ac.build();
	ac.build_mat();
	ac.sol_mat();
	for (int i = 0; i < n; i++)
		printf("%.6f%c", mat[target[i]][ac.l], " \n"[i == n - 1]);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) sol();
	return 0;
}
