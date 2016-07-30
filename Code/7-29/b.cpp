#include <bits/stdc++.h>
using namespace std;

const int maxn = 101111;
const int inf = 1e9;
int fa[maxn], dep[maxn], ans[maxn], lim[maxn], mx[maxn], seq[maxn], deg[maxn], head[maxn], vis[maxn], final_ans[maxn], T, n, x, y, cnt;

vector<int> fu[maxn];
set<int> sp;

void clear(vector<int> &v) {
	v.clear();
	vector<int>(v).swap(v);
}

void clear(set<int> &v) {
	v.clear();
	set<int>(v).swap(v);
}

struct segmenttree {
	int mn, tag;
} tr[maxn * 4];

struct edge {
	int to, front;
} e[maxn * 2];

bool cmp_dep(int p, int q) {
	return dep[p] > dep[q];
}

void addedge(int x, int y) {
	e[++cnt].to = y; e[cnt].front = head[x]; head[x] = cnt;
}

void dfs(int u, int father) {
	fa[u] = father; dep[u] = dep[father] + 1;
	for (int p = head[u]; p; p = e[p].front) {
		int v = e[p].to;
		if (v != father) dfs(v, u);
	}
}

void bomb() {
	for (int i = 1; i <= n; ++i) ans[i] = n + 1;
}

inline int getnode(int l, int r) {
	return (l + r) | (l != r);
}

void buildtree(int l, int r) {
	int k = getnode(l, r);
	tr[k].mn = tr[k].tag = 0;
	if (l == r) return;
	int mid = l + r >> 1;
	buildtree(l, mid);
	buildtree(mid + 1, r);
}

inline void push_down(int k, int l, int r) {
	if (!tr[k].tag) return;
	int mid = l + r >> 1;
	int lc = getnode(l, mid), rc = getnode(mid + 1, r);
	tr[lc].tag += tr[k].tag; tr[lc].mn += tr[k].tag;
	tr[rc].tag += tr[k].tag; tr[rc].mn += tr[k].tag;
	tr[k].tag = 0;
}

inline void update(int k, int l, int r) {
	int mid = l + r >> 1;
	int lc = getnode(l, mid), rc = getnode(mid + 1, r);
	tr[k].mn = min(tr[lc].mn, tr[rc].mn);
}

void modify(int l, int r, int a, int b, int x) {
	if (l > b || r < a) return;
	int k = getnode(l, r);
	if (l != r) push_down(k, l, r);
	if (a <= l && r <= b) {
		tr[k].tag += x, tr[k].mn += x;
		return;
	}
	int mid = l + r >> 1;
	modify(l, mid, a, b, x);
	modify(mid + 1, r, a, b, x);
	update(k, l, r);
}

int query(int l, int r, int a, int b) {
	if (l > b || r < a) return inf;
	int k = getnode(l, r);
	if (l != r) push_down(k, l, r);
	if (a <= l && r <= b) return tr[k].mn;
	int mid = l + r >> 1;
	return min(query(l, mid, a, b), query(mid + 1, r, a, b));
}

bool check(int k, int mid) {
	modify(1, n, lim[k], n, 1);
	modify(1, n, mid, n, -1);
	bool ret;
	if (tr[k].mn >= 0) ret = true; else ret = false;
	modify(1, n, lim[k], n, -1);
	modify(1, n, mid, n, 1);
	return ret;
}

void getans(int rt) {
	dfs(rt, 0);
	int tail = 0;
	for (int i = 0; i < fu[n].size(); ++i) seq[++tail] = fu[n][i];
	sort(seq + 1, seq + tail + 1, cmp_dep);
	for (int i = 1; i < tail; ++i) 
		if (dep[seq[i]] - dep[seq[i + 1]] != 1 || fa[seq[i]] != seq[i + 1]) {
			bomb();
			return;
		}
	memset(vis, 0, sizeof(vis));
	ans[seq[1]] = n; vis[seq[1]] = 1;
	for (int i = 2; i <= tail; ++i) lim[seq[i]] = n, ans[seq[i]] = -1, vis[seq[i]] = 1;
	for (int k = n - 1; k; --k) {
		if (fu[k].size() == 0) continue;
		tail = 0;
		for (int i = 0; i < fu[k].size(); ++i) seq[++tail] = fu[k][i];
		sort(seq + 1, seq + tail + 1, cmp_dep);
		for (int i = 1; i < tail; ++i)
			if (dep[seq[i]] - dep[seq[i + 1]] != 1 || fa[seq[i]] != seq[i + 1]) {
				bomb();
				return;
			}
		if (!vis[fa[seq[tail]]]) {
			bomb();
			return;
		}
		ans[seq[1]] = k; vis[seq[1]] = 1;
		for (int i = 2; i <= tail; ++i) lim[seq[i]] = k, ans[seq[i]] = -1, vis[seq[i]] = 1;
	}
	
	clear(sp);
	for (int i = 1; i <= n; ++i)
		if (fu[i].size() == 0) sp.insert(i);
	buildtree(1, n);
	for (int i = 1; i <= n; ++i)
		if (ans[i] == -1) modify(1, n, lim[i], n, -1);
	for (int i = 1; i <= n; ++i)
		if (fu[i].size() == 0) modify(1, n, i, n, 1);
	for (int i = 1; i <= n; ++i) {
		if (ans[i] > 0) continue;
		int left = 1, right = n;
		while (left < right) {
			int mid = left + right >> 1;
			if (check(i, mid)) right = mid; else left = mid + 1;
		}
		if (left == n && !check(i, n)) {
			bomb();
			return;
		}
		set<int>::iterator it = sp.lower_bound(left);
		if (it == sp.end()) {
			bomb();
			return;
		}
		ans[i] = *it;
		sp.erase(it);
		modify(1, n, lim[i], n, 1);
		modify(1, n, left, n, -1);
	}
}

int main() {
	scanf("%d", &T);
	for (int Q = 1; Q <= T; ++Q) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) clear(fu[i]);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &mx[i]);
			head[i] = 0; deg[i] = 0;
			fu[mx[i]].push_back(i);
		}
		int cnt = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			addedge(x, y);
			addedge(y, x);
			if (mx[x] == n && mx[y] == n) deg[x]++, deg[y]++;
		}
		
		int tail = 0;
		for (int i = 1; i <= n; ++i)
			if (deg[i] == 1) seq[++tail] = i;
		if (tail != 2) {
			printf("Case #%d: Impossible\n", Q);
			continue;
		}
		
		for (int i = 1; i <= n; ++i) final_ans[i] = n + 1;
		for (int i = 1; i <= 2; ++i) {
			getans(seq[i]);
			bool flag = true;
			for (int j = 1; j <= n; ++j)
				if (ans[j] > final_ans[j]) {
					flag = false;
					break;
				} else {
					if (ans[j] < final_ans[j]) {
						flag = true; 
						break;
					}
				}
			if (flag) for (int j = 1; j <= n; ++j) final_ans[j] = ans[j];
		}
		printf("Case #%d:", Q);
		for (int j = 1; j <= n; ++j) printf(" %d", final_ans[j]);
		puts("");
	}
}
