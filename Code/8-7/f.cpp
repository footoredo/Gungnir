#include <bits/stdc++.h>

const int N = 55555;
struct Q {
	int type, xc, yc, l, w, r, c;
} query[N];

int n, m, q;
int p[N], nxt[N];
bool vis[N];
inline int fd(int x) {
	return x == p[x] ? x : (p[x] = fd(p[x]));
}
/*
__inline int color(int l, int r) {
	int root = fd(l);
	int ret = 0;
	for (int y = nxt[root]; y <= r; ) {
		int tr = fd(y);
		assert(nxt[tr] == y);
		++ ret;
		p[tr] = root; nxt[root] = nxt[fd(y + 1)];
		if (nxt[fd(y + 1)] != y + 1) {
			p[fd(y + 1)] = root;
		}
		y = nxt[root];
	}
	return ret;
}
*/

std::stack<int> ss;
__inline int color(int cl, int cr) {
	int ret = 0;
	for (int i = cl; i <= cr; i = nxt[i]) {
		if (vis[i]) continue;
		vis[i] = true;
		++ ret;
		ss.push(i);
	}
	while (!ss.empty()) {
		int x = ss.top();
		ss.pop();
		nxt[x] = nxt[cr];
	}
	return ret;
}

int cnt[10];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (; std::cin >> n >> m >> q; ) {
		for (int i = 0; i < q; ++ i) {
			std::string buf; std::cin >> buf;
			Q &q = query[i];
			if (buf == "Circle") {
				q.type = 0;
				std::cin >> q.xc >> q.yc >> q.r >> q.c;
			}
			else if (buf == "Diamond") {
				q.type = 1;
				std::cin >> q.xc >> q.yc >> q.r >> q.c;
			}
			else if (buf == "Rectangle") {
				q.type = 2;
				std::cin >> q.xc >> q.yc >> q.l >> q.w >> q.c;
			}
			else if (buf == "Triangle") {
				q.type = 3;
				std::cin >> q.xc >> q.yc >> q.w >> q.c;
			}
			else assert(0);
			++q.xc; ++q.yc;
		}
		std::reverse(query, query + q);
		memset(cnt, 0, sizeof cnt);
		for (int x = 1; x <= n; ++ x) {
			//std::cout << "Line " << x << std::endl;
			for (int y = 1; y <= m + 1; ++ y) {
				nxt[y] = y + 1; vis[y] = 0;
			}

			for (int j = 0; j < q; ++ j) {
				Q q = query[j];
				if (q.type == 0) {
					long long r = 1LL * q.r * q.r - 1LL * (q.xc - x) * (q.xc - x);
					if (r < 0) continue;
					long long ll = q.yc - (long long)(sqrt(r + 1e-9) + 1e-9);
					long long rr = q.yc + (long long)(sqrt(r + 1e-9) + 1e-9);
					//std::cout << q.type << " " << std::max(1, ll) << " " << std::min(m, rr) << std::endl;
					cnt[q.c] += color(std::max(1LL, ll), std::min((long long)m, rr));
				}
				else if (q.type == 1) {
					int r = q.r - abs(x - q.xc);
					if (r < 0) continue;
					int ll = q.yc - r;
					int rr = q.yc + r;
					//std::cout << q.type << " " << std::max(1, ll) << " " << std::min(m, rr) << std::endl;
					cnt[q.c] += color(std::max(1, ll), std::min(m, rr));
				}
				else if (q.type == 2) {
					if (x < q.xc || x > q.xc + q.l - 1) continue;
					int ll = q.yc;
					int rr = q.yc + q.w - 1;
					//std::cout << q.type << " " << std::max(1, ll) << " " << std::min(m, rr) << std::endl;
					cnt[q.c] += color(std::max(1, ll), std::min(m, rr));
				}
				else if (q.type == 3) {
					if (x >= q.xc + (q.w + 1) / 2 || x < q.xc) continue;
					int r = (q.w + 1) / 2 + q.xc - x - 1;
					int ll = q.yc - r;
					int rr = q.yc + r;
					//std::cout << q.type << " " << std::max(1, ll) << " " << std::min(m, rr) << std::endl;
					cnt[q.c] += color(std::max(1, ll), std::min(m, rr));
				}
				//std::cout << cnt[1] << std::endl;
			}
		}
		for (int i = 1; i <= 9; ++ i) {
			std::cout << cnt[i];
			if (i == 9) std::cout << std::endl;
			else std::cout << " ";
		}
	}

	return 0;
}

