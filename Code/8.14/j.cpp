#include <bits/stdc++.h>
using namespace std;

const int D = 18;
//const int D = 2;
const int MAXN = 111111;
const int MAXNODE = 5000000;
int n, Q, T, m, cnt, L, R, tmp[1111], bin[MAXNODE], rt[MAXN], adj[MAXN], ans[MAXN], fa[MAXN], seq[MAXN];

struct trie {
	int c[2], size, num, f;
} tr[MAXNODE];

struct edge {
	int v, nxt;
} e[MAXN * 2];

inline int getnext(int k) {
	return (k + 1) % MAXNODE;
}

inline int getnode() {
	int u;
	if (L != getnext(R)) {
		u = bin[L];
		L = getnext(L);
		if (tr[u].c[0]) bin[R = getnext(R)] = tr[u].c[0];
		if (tr[u].c[1]) bin[R = getnext(R)] = tr[u].c[1];
	} else u = ++cnt;
	tr[u].c[0] = tr[u].c[1] = tr[u].size = tr[u].num = 0;
	tr[u].f = -1;
	return u;
}

inline void addnode(int u, int w) {
	for (int i = 0; i < D; ++i)
		if (w & (1 << i)) tmp[i] = 1; else tmp[i] = 0;
	tr[u].num = w; tr[u].size = 1;
	for (int i = D - 1; i >= 0; --i) {
		tr[u].c[tmp[i]] = getnode();
		u = tr[u].c[tmp[i]];
		tr[u].num = w; tr[u].size = 1;
	}
}

inline void addedge(int x, int y) {
	e[++m].v = y; e[m].nxt = adj[x]; adj[x] = m;
}

inline int update(int x, int y) {
	if (x == -1) return y;
	if (y == -1) return x;
	return min(x, y);
}

inline int getans(int u, int num) {
//cout << u << " " << num << " " << (tr[u].num ^ num) << endl;
	if (!tr[u].c[0] && !tr[u].c[1]) return tr[u].num ^ num;
	int ret = -1;
	if (tr[u].c[0]) ret = update(getans(tr[u].c[0], num), ret);
	if (tr[u].c[1]) ret = update(getans(tr[u].c[1], num), ret);
	return ret;
}

inline void addnumber(int u, int d, int number) {
	tr[u].size++; tr[u].num = number;
	if (!d) {
		if (tr[u].size > 1) tr[u].f = 0;
		return;
	}
	int x = tmp[d - 1] == 1;
	if (!tr[u].c[x]) tr[u].c[x] = getnode();
	addnumber(tr[u].c[x], d - 1, number);
 	if (!tr[u].c[0] || !tr[u].c[1]) {
 		tr[u].f = (tr[u].c[0]) ? tr[tr[u].c[0]].f : tr[tr[u].c[1]].f;
 		return;
 	}
 	x = -1;
 	if (tr[tr[u].c[0]].size == 1) x = 0;
 	if (tr[tr[u].c[1]].size == 1) x = 1;
 	if (x > -1) {
 		if (tmp[d - 1] == x) {
 			//cout << "merge: " << u << " " << d << " " <<tr[u].c[0] << " " << tr[u].c[1] <<" " << number <<  endl;
 			tr[u].f = getans(tr[u].c[x ^ 1], number);
 			//cout << tr[u].f << endl;
 		}
 		else tr[u].f = update(tr[u].f, tr[tr[u].c[x]].num ^ number);
 	} else {
 		tr[u].f = max(tr[tr[u].c[0]].f, tr[tr[u].c[1]].f);
 	}
}

inline void dfstrie(int u, int v, int d, int number) {
	if (!d) {
		for (int i = 1; i <= tr[v].size; ++i) {
			//cout << number << endl;
			addnumber(u, D, number);
		}
	}
	if (tr[v].c[0]) {
		tmp[d - 1] = 0;
		dfstrie(u, tr[v].c[0], d - 1, number);
	}
	if (tr[v].c[1]) {
		tmp[d - 1] = 1;
		dfstrie(u, tr[v].c[1], d - 1, number | (1 << d - 1));
	}
}

void print(int u) {
	if (!u) return;
	cout << u << " " << tr[u].c[0] << " " << tr[u].c[1] << " " << tr[u].size << " " << tr[u].num << " " << tr[u].size << " " << tr[u].f << endl;
	print(tr[u].c[0]);
	print(tr[u].c[1]);
}

inline int merge(int u, int v) {
	if (tr[u].size < tr[v].size) swap(u, v);
	dfstrie(u, v, D, 0);
	bin[R = getnext(R)] = v;
//print(u);
//puts("------------");
	return u;
}

int main() {
	int cs = 0;
	L = 1; R = cnt = 0;
	scanf("%d", &T);
	for (; T; --T) {
	L = 1; R = cnt = 0;
		scanf("%d", &n);
		memset(adj, 0, sizeof(*adj) * (n + 1));
		for (int i = 1; i <= n; ++i) {
			int w;
			scanf("%d", &w);
			rt[i] = getnode();
			addnode(rt[i], w);
		}
		m = 0;
		for (int i = 1; i < n; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			addedge(x, y);
			addedge(y, x);
		}
		
		int head = 1, tail = 1;
		seq[1] = 1; fa[1] = 0;
		for (; head <= tail; ++head) {
			int u = seq[head];
			for (int p = adj[u]; p; p = e[p].nxt) {
				int v = e[p].v;
				if (v != fa[u]) {
					fa[v] = u;
					seq[++tail] = v;
				}
			}
		}
		for (int i = tail; i; --i) {
			int u = seq[i];
			ans[u] = tr[rt[u]].f;
			if (u == 1) continue;
			rt[fa[u]] = merge(rt[u], rt[fa[u]]);
		}
		
		scanf("%d", &Q);
		printf("Case #%d:\n", ++cs);
		for (; Q; --Q) {
			int u;
			scanf("%d", &u);
			printf("%d\n", ans[u]);
		}
	}
}
