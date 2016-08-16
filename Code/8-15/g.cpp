#include <bits/stdc++.h>
#define stack STACK123
using namespace std;

typedef long long LL;

const int MAXN = 111111;
const int MAXQ = 111111;
const int MAXH = 18;
LL sum[MAXN], ans[MAXN];
int belong[MAXN], dep[MAXN], fa[MAXN][MAXH], L[MAXN], R[MAXN], pos[MAXN], stack[MAXN], adj[MAXN], times[MAXN], table[MAXN], val[MAXN], seq[MAXN];
int n, cnt, DFN, top, Q1, Q2, S, T, Q;
bool used[MAXN];

struct edge {
	int v, nxt;
} e[MAXN * 2];

struct subtree {
	int l, r, a, b, id;
} q1[MAXQ];

struct path {
	int u, v, a, b, id;
} q2[MAXQ];

inline bool cmp1(const subtree &p, const subtree &q) {
	int x = (p.l - 1) / S + 1, y = (q.l - 1) / S + 1;
	return x < y || x == y && p.r < q.r;
}

inline bool cmp2(const path &p, const path &q) {
	return belong[p.u] < belong[q.u] || belong[p.u] == belong[q.u] && pos[p.v] < pos[q.v];
}

inline LL gcd(LL a, LL b) {
	return !b ? a : gcd(b, a % b);
}

inline void addedge(int x, int y) {
	e[++cnt].v = y; e[cnt].nxt = adj[x]; adj[x] = cnt;
}

inline void dfs(int u, int father) {
//cout << u << " " << father << endl;
	dep[u] = dep[father] + 1; fa[u][0] = father;
	seq[++DFN] = u; L[u] = DFN;
	for (int i = 1; i < MAXH; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int p = adj[u]; p; p = e[p].nxt) {
		int v = e[p].v;
		if (v == father) continue;
		dfs(v, u);
		if (top >= S) {
			++cnt;
			for (int i = 1; i <= S; ++i) belong[stack[top--]] = cnt;
		}
	}
	stack[++top] = u; R[u] = DFN;
}

inline void dfs2(int u) {
	for (int p = adj[u]; p; p = e[p].nxt)
		if (e[p].v != fa[u][0]) dfs2(e[p].v);
	pos[u] = ++DFN;
}

inline int getlca(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	for (int i = 0; i < MAXH; ++i)
		if ((dep[v] - dep[u]) & (1 << i)) v = fa[v][i];
	for (int i = MAXH - 1; i >= 0; --i)
		if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return u == v ? u : fa[u][0];
}

inline void change(int i) {
//cout << i << " " << used[i] << endl;
	if (used[i]) {
		sum[times[val[i]]] -= table[val[i]];
		sum[--times[val[i]]] += table[val[i]];
	} else {
		sum[times[val[i]]] -= table[val[i]];
		sum[++times[val[i]]] += table[val[i]];
	}
	used[i] = !used[i];
}

inline int modify(int u, int v) {
	for (; u != v;) {
		if (dep[u] > dep[v]) {
			//cout << u << " " << used[u] << endl;
			change(u); u = fa[u][0];
		} else {
			//cout << v << " " << used[v] << endl;
			change(v); v = fa[v][0];
		}
	}
	return u;
}

inline bool check_in_path(int x, int u, int v, int lca) {
	if (dep[x] > max(dep[u], dep[v]) || dep[x] < dep[lca]) return false;
	if (getlca(u, x) == x || getlca(v, x) == x) return true; else return false;
}
int main() {
	std::cin.sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	for (int cs = 1; cs <= T; ++cs) {
		cin >> n >> Q;
		memset(adj, 0, sizeof(*adj) * (n + 1));
		memset(belong, 0, sizeof(*belong) * (n + 1));
		for (int i = 1; i <= n; ++i) {
			cin >> val[i];
			table[i] = val[i];
		}
		cnt = 0;
		for (int i = 1; i < n; ++i) {
			static int x, y;
			cin >> x >> y;
			addedge(x, y);
			addedge(y, x);
		}
		
		DFN = top = cnt = 0; S = sqrt(n) + 1;
		dfs(1, 0);
		DFN = 0;
		dfs2(1);
		
		Q1 = Q2 = 0;
		for (int i = 1; i <= Q; ++i) {
			static int type, u, v, a, b;
			cin >> type >> u >> v >> a >> b;
			if (type == 1) {
				q1[++Q1].l = L[u]; q1[Q1].r = R[u];
				q1[Q1].a = a; q1[Q1].b = b; q1[Q1].id = i;
			} else {
				q2[++Q2].u = u; q2[Q2].v = v;
				q2[Q2].a = a; q2[Q2].b = b; q2[Q2].id = i;
			}
		}
		sort(q1 + 1, q1 + Q1 + 1, cmp1);
		sort(q2 + 1, q2 + Q2 + 1, cmp2);
		sort(table + 1, table + n + 1);
		cnt = unique(table + 1, table + n + 1) - table - 1;
		for (int i = 1; i <= n; ++i) val[i] = lower_bound(table + 1, table + cnt + 1, val[i]) - table;
		
//for (int i = 1; i <= n; ++i) cout << seq[i] << " "; cout << endl;
//for (int i = 1; i <= n; ++i) cout << i << " " << dep[i] << " " << L[i] << " " << R[i] << " " << belong[i] << endl;
		
		memset(used, false, sizeof(*used) * (n + 1));
		memset(sum, 0, sizeof(*sum) * (n + 1));
		memset(times, 0, sizeof(*times) * (n + 1));
		int lastl = 1, lastr = 0;
		for (int i = 1; i <= cnt; ++i) sum[0] += table[i];
		for (int i = 1; i <= Q1; ++i) {
		//cout << q1[i].l << " " << q1[i].r << endl;
			for (; lastr < q1[i].r; ++lastr) change(seq[lastr + 1]);
			for (; lastr > q1[i].r; --lastr) change(seq[lastr]);
			for (; lastl > q1[i].l; --lastl) change(seq[lastl - 1]);
			for (; lastl < q1[i].l; ++lastl) change(seq[lastl]);
			lastl = q1[i].l; lastr = q1[i].r;
			ans[q1[i].id] = gcd(sum[q1[i].a], sum[q1[i].b]);
		}
		
		memset(used, false, sizeof(*used) * (n + 1));
		memset(sum, 0, sizeof(*sum) * (n + 1));
		memset(times, 0, sizeof(*times) * (n + 1));
		int lastu = 1, lastv = 1;
		times[val[1]] = 1; sum[1] = table[val[1]]; used[1] = true;
		for (int i = 1; i <= cnt; ++i) sum[0] += table[i] * (val[1] != i);
		for (int i = 1; i <= Q2; ++i) {
//cout << q2[i].u << " " << q2[i].v << " " << q2[i].a << " " << q2[i].b << " " << q2[i].id << endl;
			int u = modify(lastu, q2[i].u);
			int v = modify(lastv, q2[i].v);
			int lca = getlca(q2[i].u, q2[i].v);
			int lastlca = getlca(lastu, lastv);
//cout << u << " " << v << " " << lastu << " " << lastv << " " << q2[i].u << " " << q2[i].v << endl;
//for (int j = 1; j <= n; ++j) cout << used[j] << " "; cout << endl;
			if (check_in_path(lastu, q2[i].u, q2[i].v, lca) ^ (used[lastu] == true)) change(lastu);
			if (check_in_path(lastv, q2[i].u, q2[i].v, lca) ^ (used[lastv] == true)) change(lastv);
			if (check_in_path(lastlca, q2[i].u, q2[i].v, lca) ^ (used[lastlca] == true)) change(lastlca);
			if (used[q2[i].u] == false) change(q2[i].u);
			if (used[q2[i].v] == false) change(q2[i].v);
			if (used[lca] == false) change(lca);
//cout << u << " " << q2[i].u << " " << q2[i].v << " " << lca << " " << check_in_path(u, q2[i].u, q2[i].v, lca) << endl;
			if (check_in_path(u, q2[i].u, q2[i].v, lca) ^ (used[u] == true)) change(u);
			if (check_in_path(v, q2[i].u, q2[i].v, lca) ^ (used[v] == true)) change(v);
//cout << v << " " << q2[i].u << " " << q2[i].v << " " << lca << " " << check_in_path(v, q2[i].u, q2[i].v, lca) << endl;	
//for (int j = 1; j <= n; ++j) cout << used[j] << " "; cout << endl;
//cout << sum[0] << " " << sum[1] << " " << sum[2] << endl;
			lastu = q2[i].u; lastv = q2[i].v;
			ans[q2[i].id] = gcd(sum[q2[i].a], sum[q2[i].b]);
		}
		
		cout << "Case #" << cs << ":" << endl;
		for (int i = 1; i <= Q; ++i) cout << ans[i] << endl;
	}
}
