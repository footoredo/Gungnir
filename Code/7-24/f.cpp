#include <bits/stdc++.h>

const int N = 222222 * 4, M = N * 2;

struct Graph {  // Remember to call .init()!
    int e, nxt[M], v[M], adj[N], n;
    bool base;
    __inline void init(bool _base, int _n = 0) {
        //assert(n < N);
        n = _n; base = _base;
        e = 0; memset(adj + base, -1, sizeof(*adj) * n);
    }
    __inline int new_node() {
        adj[n + base] = -1;
        //assert(n + base + 1 < N);
        return n++ + base;
    }
    __inline void ins(int u0, int v0) { // directional
        //assert(u0 < n + base && v0 < n + base);
        v[e] = v0; nxt[e] = adj[u0]; adj[u0] = e++;
        //assert(e < M);
    }
    __inline void bi_ins(int u0, int v0) {
        ins(u0, v0); ins(v0, u0);
    }
} raw_graph;

const bool DCC_VERTEX = 0, DCC_EDGE = 1;
struct DCC {  // N = N0 + M0.
    Graph *g, forest; // g is raw graph.
    int dfn[N], DFN, low[N];
    int stack[N], top;
    int expand_to[N];  // Where edge i is expanded to in expaned graph.
    // Vertex i expaned to i.
    int compress_to[N];  // Where vertex i is compressed to.
    bool vertex_type[N], cut[N], compress_cut[N], branch[M];
    //std::vector<int> DCC_component[N];  // Cut vertex belongs to none.
    __inline void init(Graph *raw_graph) {
		g = raw_graph;
    }
    void DFS(int u, int pe) {
        dfn[u] = low[u] = ++DFN; cut[u] = false;
        if (!~g->adj[u]) {
            cut[u] = 1; 
            compress_to[u] = forest.new_node();
            compress_cut[compress_to[u]] = 1;
        }
        for (int e = g->adj[u]; ~e; e = g->nxt[e]) {
			int v = g->v[e]; 
            if ((e ^ pe) > 1 && dfn[v] > 0 && dfn[v] < dfn[u]) {
				stack[top++] = e;
                low[u] = std::min(low[u], dfn[v]);
            }
            else if (!dfn[v]) {
				stack[top++] = e; branch[e] = 1;
                DFS(v, e);
                low[u] = std::min(low[v], low[u]);
                if (low[v] >= dfn[u]) {
                    if (!cut[u]) {
                        cut[u] = 1;
                        compress_to[u] = forest.new_node();
                        compress_cut[compress_to[u]] = 1;
                    }
                    int cc = forest.new_node();
                    forest.bi_ins(compress_to[u], cc);
                    compress_cut[cc] = 0;
                    //DCC_component[cc].clear();
                    do {
						int cur_e = stack[--top];
						compress_to[expand_to[cur_e]] = cc;
						if (branch[cur_e]) {
							int v = g->v[cur_e];
							if (cut[v]) 
								forest.bi_ins(cc, compress_to[v]);
							else {
								//DCC_component[cc].push_back(v);
								compress_to[v] = cc;
							}
						}
                    } while (stack[top] != e);
                    //assert(top >= 0);
                }
            }
        }
    }
    void solve() {
        forest.init(g->base);
		int n = g->n;
		for (int i = 0; i < g->e; i++) {
			expand_to[i] = g->new_node();
			branch[i] = 0;
		}
        memset(dfn + g->base, 0, sizeof(*dfn) * n); DFN = 0;
        for (int i = 0; i < n; i++)
            if (!dfn[i + g->base]) {
                top = 0;
                DFS(i + g->base, -1);
            }
    }
} dcc;

const int MODN = 1e9 + 7 + 1e-9;
int w[N], W[N], dcc_ans[N], root[N], f[N];
bool vis[N];

__inline int pw(int x, int n) {
    int ret = 1;
    for (; n; n >>= 1, x = 1LL * x * x % MODN)
        if (n & 1) ret = 1LL * ret * x % MODN;
    return ret;
}

int calc_f(int u, int _root) {
    int ret = W[u];
    root[u] = _root;
    vis[u] = 1;
    for (int e = dcc.forest.adj[u]; ~e; e = dcc.forest.nxt[e]) if (!vis[dcc.forest.v[e]]) {
        int tmp = calc_f(dcc.forest.v[e], _root);
        ret = 1LL * ret * tmp % MODN;
    }
    return f[u] = ret;
}

void dp(int u, bool is_root, int upsum) {
    vis[u] = 1;
    dcc_ans[u] = 0;
    if (!is_root && dcc.compress_cut[u]) dcc_ans[u] = (dcc_ans[u] + 1LL * upsum * pw(f[u], MODN - 2)) % MODN;

    for (int e = dcc.forest.adj[u]; ~e; e = dcc.forest.nxt[e]) if (!vis[dcc.forest.v[e]]) {
        dcc_ans[u] = (dcc_ans[u] + f[dcc.forest.v[e]]) % MODN;
        dp(dcc.forest.v[e], 0, upsum);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T; std::cin >> T;
    for (; T--; ) {
        int n, m; std::cin >> n >> m;
        raw_graph.init(1, n);
        for (int i = 1; i <= n; i++) std::cin >> w[i];
        for (int i = 0; i < m; i++) {
            int x, y; std::cin >> x >> y;
            raw_graph.bi_ins(x, y);
        }

        dcc.init(&raw_graph); dcc.solve();
		//std::cout << dcc.forest.n << std::endl;
        for (int i = 1; i <= dcc.forest.n; i++)
            W[i] = 1;
        for (int i = 1; i <= n; i++)
            W[dcc.compress_to[i]] = 1LL * 
                W[dcc.compress_to[i]] * w[i] % MODN;
        memset(vis + 1, 0, sizeof(*vis) * dcc.forest.n);
        int sum = 0;
        for (int i = 1; i <= dcc.forest.n; i++)
            if (!vis[i]) {
                sum = (sum + calc_f(i, i)) % MODN;
            }
        memset(vis + 1, 0, sizeof(*vis) * dcc.forest.n);
        for (int i = 1; i <= dcc.forest.n; i++)
            if (!vis[i]) {
                dp(i, 1, f[i]);
            }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dcc.cut[i]) {
                ans = (ans + 
                        1LL * (dcc_ans[dcc.compress_to[i]] +
                            sum - f[root[dcc.compress_to[i]]])
                        * i) % MODN;
            }
            else ans = (ans + (1LL * pw(w[i], MODN - 2) * 
                        f[root[dcc.compress_to[i]]] + 
                        sum - f[root[dcc.compress_to[i]]]) 
                    % MODN * i ) % MODN;
        }

        std::cout << (ans + MODN) % MODN << std::endl;
    }

    return 0;
}
