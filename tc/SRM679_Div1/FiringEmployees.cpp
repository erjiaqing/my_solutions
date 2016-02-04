class FiringEmployees {
public:
	vector <int> manager, salary, productivity; 
	vector <int> son[2505];
	int dfs(int nx) {
		int rx = 0;
		for (int i = 0; i < son[nx].size(); i++) {
			rx += dfs(son[nx][i]);
		}
		if (nx)
			rx += productivity[nx - 1] - salary[nx - 1];
		return max(rx, 0);
	}
	int fire(vector <int> _manager, vector <int> _salary, vector <int> _productivity) {
		manager = _manager;
		salary = _salary;
		productivity = _productivity;
		for (int i = 0; i < manager.size(); i++)
			son[manager[i]].push_back(i + 1);
		return dfs(0);
	}
};
