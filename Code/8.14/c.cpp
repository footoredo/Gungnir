#include <bits/stdc++.h>
#define foreach(it, v) for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++ it)

struct State {
	int f, g;
	__inline State() {}
	__inline State(int f, int g): f(f), g(g) {}
	__inline State operator+(int x) const {
		return State(f + x, g + x);
	}
	__inline State operator+(const State x) const {
		return State(f + x.f, g + x.g);
	}
};

State solve(std::vector<State> pack, int &f) {
	f = -1;
	State ret(0, 0);
	int min_lost = 1e9;
	foreach(it, pack) {
		if (it->g > 0) {
			ret.g += it->g;
			ret.f += it->g;
		}
		int lost = it->g > 0 ? - it->f + it->g : - it->f;
		if (lost < min_lost) {
			min_lost = lost;
			f = it - pack.begin();
		}
	}
	ret.f -= min_lost;
	return ret;
}

const int N = 111111;
State s[N];
int value[N];

template<typename T>
__inline void clear(T& container) {
	container.clear();
	T(container).swap(container);
}

int adj[N], v[N * 2], w[N * 2], nxt[N * 2], e;
__inline void ins(int u0, int v0, int w0) {
	v[e] = v0; w[e] = w0; nxt[e] = adj[u0]; adj[u0] = e ++;
}

void dp(int u, int p) {
	std::vector<State> sons;
	for (int e = adj[u]; ~e; e = nxt[e])
		if (v[e] != p) {
			dp(v[e], u);
			sons.push_back(s[v[e]] + State(-w[e], -w[e]*2));
		}
	if (!sons.size()) {
		s[u] = State(value[u], value[u]);
	}
	else {
		int tmp;
		s[u] = solve(sons, tmp) + value[u];
		s[u].f = std::max(s[u].f, s[u].g);
	}
	clear(sons);
	//std::cout << "oo " << u << " " << s[u].f << " " << s[u].g << std::endl;
}

int ans[N];
void solve(int u, int p, State ps) {
	//std::cout << u << " " << ps.f << " " << ps.g << std::endl;
	std::vector<State> pack;
	pack.push_back(ps);
	State tmp;
	for (int e = adj[u]; ~e; e = nxt[e])
		if (v[e] != p) {
			pack.push_back(s[v[e]] + State(-w[e], -w[e]*2));
		}
	int f_t;
	tmp = solve(pack, f_t) + value[u];
	//std::cout << "xxxx " << tmp.f << " " << tmp.g << std::endl;
	clear(pack);
	if (tmp.f < tmp.g) {
		tmp.f = tmp.g; f_t = -1;
	}
	ans[u] = tmp.f;
	for (int e = adj[u], c = 1; ~e; e = nxt[e], ++ c) 
		if (v[e] != p) {
			if (c != f_t) {
				State t_s = tmp;
				if (s[v[e]].g - w[e]*2> 0) {
					t_s.f -= s[v[e]].g - w[e]*2;
					t_s.g -= s[v[e]].g - w[e]*2;
				}
				solve(v[e], u, t_s + State(-w[e], -w[e]*2));
			}
			else {
				clear(pack); //std::cout << pack.size() << std::endl;
				pack.push_back(ps);
				for (int ee = adj[u]; ~ee; ee = nxt[ee])
					if (v[ee] != p && v[ee] != v[e]) {
						//std::cout << "pack " << v[ee] << std::endl;
						pack.push_back(s[v[ee]] + State(-w[ee], -w[ee]*2));
					}
				int dump;
				State ttt = solve(pack, dump) + value[u];
				//std::cout << "ttt " << ttt.f << " " << ttt.g << std::endl;
				ttt.f = std::max(ttt.f, ttt.g);
				solve(v[e], u, ttt + State(-w[e], -w[e]*2));
				clear(pack);
			}
		}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int T; std::cin >> T;
	for (int curT = 1; curT <= T; ++ curT) {
		int n; std::cin >> n;
		memset(adj + 1, -1, sizeof(*adj) * n); e = 0;
		for (int i = 1; i <= n; ++ i) std::cin >> value[i];
		for (int i = 1; i < n; ++ i) {
			int u, v, w; std::cin >> u >> v >> w;
			ins(u, v, w); ins(v, u, w);
		}

		dp(1, 0); solve(1, 0, State(0, 0));
		std::cout << "Case #" << curT << ":" << std::endl;
		for (int i = 1; i <= n; ++ i)
			std::cout << ans[i] << std::endl;
	}

	return 0;
}
