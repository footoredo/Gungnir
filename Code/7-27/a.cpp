#include <bits/stdc++.h>

const int N = 555;
std::vector<int> inputs[N], outputs[N];
std::vector<int> dependee[N], succ[N];
int earliest[N], prev[N], need[N], execute[N];
int n, m, o;
char buf[N];
std::priority_queue<std::pair<int, int> > PQ;

void push(int v) {
	for (int i = 0; i < dependee[v].size(); i++)
		if (!--need[dependee[v][i]]) {
			int finish = earliest[v] + execute[dependee[v][i]];
			succ[prev[v]].push_back(dependee[v][i]);
			PQ.push(std::make_pair(-finish, dependee[v][i]));
		}
}

void print(int u) {
	std::cout << "(";
	if (u) std::cout << "P" << u;
	for (int i = 0; i < succ[u].size(); i++) {
		if (i) std::cout << "|";
		print(succ[u][i]);
	}
	std::cout << ")";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (int T = 1; std::cin >> n >> m >> o, n || m || o; ++T) {
		std::cin >> buf + 1; 
		for (int i = 0; i <= n; i++) succ[i].clear();
		for (int i = 1; i <= m; i++) {
			dependee[i].clear(); 
			earliest[i] = -1; prev[i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			std::cin >> execute[i];
			inputs[i].clear(); outputs[i].clear();
			int I; std::cin >> I;
			for (int j = 0; j < I; j++) {
				int v; std::cin >> v;
				inputs[i].push_back(v);
				++need[i]; dependee[v].push_back(i);
			}
			int O; std::cin >> O;
			for (int j = 0; j < O; j++) {
				int v; std::cin >> v;
				outputs[i].push_back(v);
			}
		}
		for (; !PQ.empty(); ) PQ.pop();
		for (int i = 1; i <= m; i++)
			if (buf[i] == '1') {
				earliest[i] = 0;
				push(i);
			}

		for (; !PQ.empty(); ) {
			int cur = -PQ.top().first;
			int u = PQ.top().second;
			PQ.pop();
			for (int i = 0; i < outputs[u].size(); i++)
				if (!~earliest[outputs[u][i]]) {
					earliest[outputs[u][i]] = cur;
					prev[outputs[u][i]] = u;
					push(outputs[u][i]);
				}
		}

		std::cout << "Case " << T << ": ";
		if (!~earliest[o]) std::cout << "-1" << std::endl;
		else {
			std::cout << earliest[o] << " ";
			print(0);
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}
