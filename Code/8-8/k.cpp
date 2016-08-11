#include <bits/stdc++.h>

const int N = 1111 * 8;
int k, n, m, cc;
int node[2][N], socket[2][N];
int adj[N], nxt[N * 2], v[N * 2], e;
bool destroyed[N * 2];
__inline void ins(int u0, int v0) {
//	std::cout << u0 << " " << v0 << std::endl;
	v[e] = v0; nxt[e] = adj[u0]; destroyed[e] = false; adj[u0] = e ++;
}

void read(int n, bool t) {
	for (int i = 0; i < n + k - 1; ++ i) {
		char buf[2][20];
		std::cin >> buf[0] >> buf[1];
		int x, y; 
		sscanf(buf[0] + 2, "%d", &x);
		sscanf(buf[1] + 2, "%d", &y);
		int xx = buf[0][1] == 'S' ? socket[t][x - 1] :
			node[t][x - 1];
		int yy = buf[1][1] == 'S' ? socket[t][y - 1] :
			node[t][y - 1];
		ins(xx, yy); ins(yy, xx);
	}
}

std::string name[N];
int number[N];
bool boom;
bool vis[N];

__inline void print(int cc) {
	std::cout << name[cc] << number[cc];
}

bool solve(int u, int pe) {
//	std::cout << "solve "; print(u); std::cout << std::endl;
	int cnt = 0, cs = 0;
	for (int e = adj[u]; ~e; e = nxt[e]) {
//		std::cout << v[e] << " " << e << " " << pe <<std::endl;
		if ((e ^ pe) != 1 && (e ^ pe) != 0) {
			++ cs;
			cnt += solve(v[e], e);
		}
	}
//	std::cout << "cnt"; print(u); std::cout << " " << cnt << std::endl;
	if (cnt == 1 || cs == 0) {
		return true;
	}
	else if (cnt == 2) {
		if (~pe) destroyed[pe] = destroyed[pe ^ 1] = true;
		return false;
	}
	else {
//		std::cout << "BOOM "; print(u); std::cout << std::endl; 
		boom = true; return false;
	}
}

std::vector<int> seq;
void dfs(int u) {
	vis[u] = true; seq.push_back(u);
	for (int e = adj[u]; ~e; e = nxt[e])
		if (!vis[v[e]] && !destroyed[e]) {
			dfs(v[e]);
		}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (; T --; ) {
		std::cin >> k >> n >> m; cc = e = 0;
		for (int i = 0; i < k; ++ i) {
			socket[0][i] = cc; name[cc] = "AS"; number[cc] = i + 1; adj[cc ++] = -1;
			socket[1][i] = cc; name[cc] = "BS"; number[cc] = i + 1; adj[cc ++] = -1;
		}
		for (int i = 0; i < n; ++ i) {
			node[0][i] = cc; name[cc] = "AP"; number[cc] = i + 1; adj[cc ++] = -1;
		}
		for (int i = 0; i < m; ++ i) {
			node[1][i] = cc; name[cc] = "BP"; number[cc] = i + 1; adj[cc ++] = -1;
		}

		read(n, 0); read(m, 1);
		boom = false;
		if (solve(node[0][0], -1)) boom = true;
//		if (boom) std::cout << "xxasasdasdas" << std::endl;
		if (solve(node[1][0], -1)) boom = true;
		for (int i = 0; i < k; ++ i) {
			char buf[2][20];
			std::cin >> buf[0] >> buf[1];
			int x, y; 
			sscanf(buf[0] + 2, "%d", &x);
			sscanf(buf[1] + 2, "%d", &y);
			int xx = socket[buf[0][0] == 'B'][x - 1];
			int yy = socket[buf[1][0] == 'B'][y - 1];
			ins(xx, yy); ins(yy, xx);
		}

		memset(vis, 0, sizeof(*vis) * (cc + 5));
		if (!boom) {
//			std::cout << "xx" << std::endl;
			seq.clear();
			dfs(0);
			for (int i = 0; i < cc; ++ i) {
				if (!vis[i]) {
					boom = true; break;
				}
			}
		}

		if (boom) {
			std::cout << "NO" << std::endl;
		}
		else {
			std::cout << "YES";
			for (int i = 0; i < cc; ++ i) {
				std::cout << " ";
				print(seq[i]);
			}
			std::cout << std::endl;
		}
	}

	return 0;
}
