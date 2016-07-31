#include <bits/stdc++.h>
#define foreach(it, v) for (__typeof(v.begin()) it = v.begin(); it != v.end(); ++ it)

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
const int sim[4] = {2, 3, 0, 1};
const int neighbour[6][4] = {
	{4, 2, 1, 3},
	{0, 2, 5, 3},
	{4, 5, 1, 0},
	{4, 0, 1, 5},
	{5, 2, 0, 3},
	{1, 2, 4, 3}
};
int direction[6][6];

__inline int calc_shift(int i, int d, int shift) {
	return (4 - sim[d] + direction[neighbour[i][(shift + d) % 4]][i]) % 4;
}

__inline int go(int i, int d, int shift) {
	return neighbour[i][(d + shift) % 4];
}

struct Graph {
	bool adj[6][6], available[12];
	int u[12], v[12], n, m, shift[6];
	__inline void init(int _n = 0) {
		n = _n; m = 0;
		memset(adj, 0, sizeof(adj));
	}
	__inline int new_node() {
		return n++;
	}
	__inline void ins(int u0, int v0) {
		assert(u0 < n && v0 < n);
		if (!adj[u0][v0]) {
			adj[u0][v0] = adj[v0][u0] = 1;
			u[m] = u0; v[m] = v0;
			available[m ++] = 1;
		}
	}
	__inline void play(int e) {
		adj[u[e]][v[e]] = adj[v[e]][u[e]] = available[e] ^= 1;
	}

	int p[6];
	int fd(int x) { return x == p[x] ? x : (p[x] = fd(p[x])); }
	__inline bool connected() {
		for (int i = 0; i < n; ++ i) p[i] = i;
		int cc = n;
		for (int i = 0; i < m; ++ i) if (available[i])
			if (fd(u[i]) != fd(v[i])) {
				--cc; p[fd(u[i])] = fd(v[i]);
			}
		return cc == 1;
	}
} cube;

typedef std::pair<int, int> Pos;
typedef std::vector<Pos> Expand;
Expand expand(Graph& cube) {
	Expand pos(6);
	bool vis[6]; memset(vis, 0, sizeof vis); vis[0] = 1;
	pos[0] = std::make_pair(0, 0);
	cube.shift[0] = 0;
	int Q[6], l = 0, r = 0; Q[r ++] = 0;
	for (; l < r; ) {
		int u = Q[l ++]; 
		for (int d = 0; d < 4; ++ d) {
			int v = go(u, d, cube.shift[u]);
			if (cube.adj[u][v] && !vis[v]) {
				cube.shift[v] = calc_shift(u, d, cube.shift[u]);
				pos[v] = std::make_pair(pos[u].first + dx[d],
						pos[u].second + dy[d]);
				Q[r ++] = v;
				vis[v] = 1;
			}
		}
	}
	return pos;
}

const int connect[6][2] = {
	{0, 2}, {1, 3}, {0, 3}, {0, 1}, {1, 2}, {2, 3}
};

void pre() {
	memset(direction, -1, sizeof direction);
	cube.init(6);
	for (int i = 0; i < 6; ++ i)
		for (int j = 0; j < 4; ++ j) {
			cube.ins(i, neighbour[i][j]);
			direction[i][neighbour[i][j]] = j;
		}
}

const int N = 20;
int n, m, a[N][N];

__inline int fc(int u, const Expand& pos, int c) {
	return connect[a[pos[u].first][pos[u].second]][c];
}

int count(const Expand& exp) {
	int l = 0, r = 0, u = 0, d = 0;
	foreach(it, exp) {
		u = std::min(u, it->first);
		d = std::max(d, it->first);
		l = std::min(l, it->second);
		r = std::max(r, it->second);
	}
	int ret = 0;
	for (int i = -u; i + d < n; ++ i)
		for (int j = -l; j + r < m; ++ j) {
			Expand pos(6);
			foreach(it, exp) {
				int x = i + it->first, y = j + it->second;
				pos[it - exp.begin()] = std::make_pair(x, y);
			}
			Graph tmp; tmp.init(6);
			bool valid = 1;
			for (int u = 0; u < 6; ++ u)
				for (int c = 0; c < 2; ++ c) {
					int d = fc(u, pos, c);
					int v = go(u, d, cube.shift[u]);
					if (go(v, fc(v, pos, 0), cube.shift[v]) != u &&
							go(v, fc(v, pos, 1), cube.shift[v]) != u) {
						valid = 0; break;
					}
					tmp.ins(u, v);
				}
			ret += valid && tmp.connected();
		}
	return ret;
}

std::vector<std::pair<Graph, Expand> > sol;

int main() {
	pre();
	for (int mask = 0; mask < (1 << 12); ++ mask)
		if (__builtin_popcount(mask) == 5) {
			for (int i = 0; i < 12; ++ i)
				if (~mask >> i & 1)
					cube.play(i);
			if (cube.connected()) {
				Expand exp = expand(cube);
				bool valid = true;
				foreach(it, exp) 
					if (it->first < 0 || it->first == 0 && it->second < 0)
						valid = false;
				if (valid) sol.push_back(std::make_pair(cube, exp));
			}
			for (int i = 0; i < 12; ++ i)
				if (~mask >> i & 1)
					cube.play(i);
		}
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (int curT = 1; curT <= T; ++ curT) {
		std::cin >> n >> m;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
				std::cin >> a[i][j];

		int ans = 0;
		foreach(it, sol) {
			cube = it->first;
			ans += count(it->second);
		}

		std::cout << "Case " << curT << ": " << ans << std::endl;
	}

	return 0;
}
