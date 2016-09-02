#include <bits/stdc++.h>
using namespace std;

const int MAXN = 211111;
const long long INF = (long long) 4000000000000000000;
int link[MAXN], ans, fa[MAXN], wh[MAXN];

typedef pair<long long, pair<long long, long long> > PPP;
PPP tmp;

namespace k_dimensional_tree {
	int const N = MAXN;

	struct point {
		int x, y, id;
	};

	inline long long sqr(const long long &x) {
		return x * x;
	}

	inline long long dist(const point &a, const point &b) {
		return sqr(a.x - b.x) + sqr(a.y - b.y);
	}

	struct rectangle {
		int lx, rx, ly, ry;
		inline void set(const point &p) {
			lx = rx = p.x;
			ly = ry = p.y;
		}
		inline void mergy(const point &p) {
			lx = min(lx, p.x);
			rx = max(rx, p.x);
			ly = min(ly, p.y);
			ry = max(ry, p.y);
		}
		inline void mergy(const rectangle &r) {
			lx = min(lx, r.lx);
			rx = max(rx, r.rx);
			ly = min(ly, r.ly);
			ry = max(ry, r.ry);
		}
		/*	minimum distance	*/
		inline long long dist(const point &p) {
			if (p.x <= lx && p.y <= ly) {
				return sqr(p.x - lx) + sqr(p.y - ly);
			}
			if (p.x <= rx && p.y <= ly) {
				return sqr(p.y - ly);
			}
			if (p.x >= rx && p.y <= ly) {
				return sqr(p.x - rx) + sqr(p.y - ly);
			}
			if (p.x >= rx && p.y <= ry) {
				return sqr(p.x - rx);
			}
			if (p.x >= rx && p.y >= ry) {
				return sqr(p.x - rx) + sqr(p.y - ry);
			}
			if (p.x >= lx && p.y >= ry) {
				return sqr(p.y - ry);
			}
			if (p.x <= lx && p.y >= ry) {
				return sqr(p.x - lx) + sqr(p.y - ry);
			}
			if (p.x <= lx && p.y >= ly) {
				return sqr(p.x - lx);
			}
			return 0;
		}
	};

	struct node {
		int child[2];
		point p;
		rectangle r;
		inline void set(const point &_p) {
			p = _p;
			r.set(p);
			child[0] = child[1] = 0;
		}
	};

	int size;
	point a[N];
	node tree[N];

	inline bool xcompare(const point &a, const point &b) {
		return a.x < b.x || a.x == b.x && a.y < b.y;
	}

	inline bool ycompare(const point &a, const point &b) {
		return a.y < b.y || a.y == b.y && a.x < b.x;
	}

	inline int build(int dep, int left, int right, bool dim = 0) {
		int x = ++size, mid = left + right >> 1;
		nth_element(a + left, a + mid, a + right, dim ? xcompare : ycompare);
		tree[x].set(a[mid]);
		wh[a[mid].id] = x;
		if (left < mid) {
			tree[x].child[0] = build(dep + 1, left, mid, dim ^ 1);
			tree[x].r.mergy(tree[tree[x].child[0]].r);
		}
		if (mid + 1 < right) {
			tree[x].child[1] = build(dep + 1, mid + 1, right, dim ^ 1);
			tree[x].r.mergy(tree[tree[x].child[1]].r);
		}
		return x;
	}

	inline void query(int x, const point &p, PPP &ret, bool dim = 0) {
		if (tree[x].r.dist(p) > ret.first) {
			return;
		}
		tmp = make_pair(dist(tree[x].p, p), make_pair(tree[x].p.x, tree[x].p.y));
		if (tmp.first && tmp < ret) {
			ret = tmp;
			ans = tree[x].p.id;
		}
		if (dim && xcompare(p, tree[x].p) || !dim && ycompare(p, tree[x].p)) {
			if (tree[x].child[0]) {
				query(tree[x].child[0], p, ret, dim ^ 1);
			}
			if (tree[x].child[1]) {
				query(tree[x].child[1], p, ret, dim ^ 1);
			}
		} else {
			if (tree[x].child[1]) {
				query(tree[x].child[1], p, ret, dim ^ 1);
			}
			if (tree[x].child[0]) {
				query(tree[x].child[0], p, ret, dim ^ 1);
			}
		}
	}
	
	inline void clear() {
		size = 0;
	}
}
	int T, n, Q;

inline int getfa(int x) {
	return (x == fa[x]) ? x : fa[x] = getfa(fa[x]);
}

int main() {
	scanf("%d", &T);
	for (int cs = 1; cs <= T; ++cs) {
		printf("Case #%d:\n", cs);
		scanf("%d%d", &n, &Q);
		k_dimensional_tree::clear();
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &k_dimensional_tree::a[i].x, &k_dimensional_tree::a[i].y);
		for (int i = 1; i <= n; ++i)
			k_dimensional_tree::a[i].id = i;
		k_dimensional_tree::build(1, 1, n + 1, 0);
		for (int i = 1; i <= n; ++i) fa[i] = i;
		for (int i = 1; i <= n; ++i) {
			PPP temp = make_pair(INF, make_pair(INF,  INF));
			k_dimensional_tree::query(1, k_dimensional_tree::tree[wh[i]].p, temp, 0);
			fa[getfa(ans)] = getfa(i);
		}
		for (; Q; --Q) {
			int u, v;
			scanf("%d%d", &u, &v);
			u = getfa(u);
			v = getfa(v);
			if (u == v) puts("YES");
			else puts("NO");
		}
	}
}
