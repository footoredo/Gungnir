#include <bits/stdc++.h>
using namespace std;

const int gx[] = {0, 0, 1, -1};
const int gy[] = {1, -1, 0, 0};
const int hx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int hy[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int bx[] = {-1, 0, 0, 1, 1, 0, 0, -1};
const int by[] = {0, 1, 1, 0, 0, -1, -1, 0};
const int MAXS = 300000;
const int INF = 1e9;
int dis[MAXS], n = 0;

struct State {
	int x1, y1, x2, y2, x3, y3, f, l;
	State() {};
	State(int _x1, int _y1, int _x2, int _y2, int _x3, int _y3, int _f, int _l):
	x1(_x1), y1(_y1), x2(_x2), y2(_y2), x3(_x3), y3(_y3), f(_f), l(_l) {};
	inline bool operator < (const State &rhs) const{
		if (x1 != rhs.x1) return x1 < rhs.x1;
		if (y1 != rhs.y1) return y1 < rhs.y1;
		if (x2 != rhs.x2) return x2 < rhs.x2;
		if (y2 != rhs.y2) return y2 < rhs.y2;
		if (x3 != rhs.x3) return x3 < rhs.x3;
		if (y3 != rhs.y3) return y3 < rhs.y3;
		if (f != rhs.f) return f < rhs.f;
		else return l < rhs.l;
	}
	inline bool block(int dir) {
		int blockx = x2 + bx[dir], blocky = y2 + by[dir];
		int tx = x2 + hx[dir], ty = y2 + hy[dir];
		if (blockx == x3 && blocky == y3 || blockx == x1 && blocky == y1) return true;
		return tx == x3 && ty == y3;
	}
	inline bool checkdie() {
		return x3 == x1 && (x1 != x2 || y2 > y3 || y2 < y1 || l == 0);
	}
	inline void print() {
		cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << f << " " << l << endl;
	}
} F[MAXS];

map<State, int> M;
vector<int> pre[MAXS], nxt[MAXS];

inline void link(int x, int y) {
	nxt[x].push_back(y);
	pre[y].push_back(x);
}

inline void getgraph() {
	n = 0;
	for (int x1 = 3; x1 <= 5; ++x1)
		for (int y1 = 0; y1 <= 2; ++y1)
			for (int x2 = 0; x2 <= 8; ++x2)
				for (int y2 = 0; y2 <= 9; ++y2)
					for (int x3 = 3; x3 <= 5; ++x3)
						for (int y3 = 7; y3 <= 9; ++y3)
							for (int f = 0; f <= 1; ++f)
								for (int l = 0; l <= 1; ++l) {
									State now = State(x1, y1, x2, y2, x3, y3, f, l);
									M[now] = ++n; F[n] = now;
									pre[n].clear(); nxt[n].clear();
								}	
	for (int i = 1; i <= n; ++i) {
		State now = F[i];
		for (int dir = 0; dir < 4; ++dir) {
			if (now.f) break;
			int tx = now.x1 + gx[dir], ty = now.y1 + gy[dir];
			State news = now;
			news.x1 = tx, news.y1 = ty, news.f ^= 1;
			if (!M.count(news)) continue;
			if (tx == news.x2 && ty == news.y2) news.l = 0;
			link(M[now], M[news]);
		}
		
		for (int dir = 0; dir < 8; ++dir) {
			if (now.l == 0 || !now.f) break;
			int tx = now.x2 + hx[dir], ty = now.y2 + hy[dir];
			State news = now;
			news.x2 = tx; news.y2 = ty; news.f ^= 1;
			if (!M.count(news) || now.block(dir)) continue;
			link(M[now], M[news]);
		}
		
		for (int dir = 0; dir < 4; ++dir) {
			if (!now.f) break;
			int tx = now.x3 + gx[dir], ty = now.y3 + gy[dir];
			State news = now;
			news.x3 = tx; news.y3 = ty; news.f ^= 1;
			if (!M.count(news) || news.x2 == tx && news.y2 == ty && news.l) continue;
			if (!now.checkdie() && news.checkdie()) continue;
			link(M[now], M[news]);
		}
	}
}

queue<int> Q;
bool inq[MAXS], boo[MAXS];

inline int getans(int S) {
	int mx = -INF, mn = INF, inf = 0;
	for (int i = 0; i < nxt[S].size(); ++i) {
		int tmp = nxt[S][i];
		if (dis[tmp] == -INF) {
			inf = 1;
			continue;
		} else {
			mx = max(mx, dis[tmp]);
			mn = min(mn, dis[tmp]);
		}
	}
	if (F[S].f) return mn != INF ? mn + 1 : -INF;
	else return inf ? -INF : mx + 1;
}

inline void DP() {
	for (int i = 1; i <= n; ++i) dis[i] = -INF, inq[i] = false, boo[i] = true;
	while (!Q.empty()) Q.pop();
	for (int i = 1; i <= n; ++i) {
		State now = F[i];
		if (now.x1 == now.x3 && (now.x1 != now.x2 || now.y2 > now.y3 || now.y2 < now.y1 || now.l == 0)) {
			if (now.f == 1) dis[i] = 1; else dis[i] = -INF;
			Q.push(i); inq[i] = true; boo[i] = false; continue;
		}
		if (now.x2 == now.x1 && now.y2 == now.y1 && now.l && now.f == 0) {
			dis[i] = 0; Q.push(i); inq[i] = true; boo[i] = false; continue;
		}
	}
	while (!Q.empty()) {
		int u = Q.front(); inq[u] = false; Q.pop();
		for (int i = 0; i < pre[u].size(); ++i) {
			int pres = pre[u][i];
			if (!boo[pres]) continue;
			int tmp = getans(pres);
			if (tmp != dis[pres]) {
				dis[pres] = tmp;
				if (!inq[pres]) {
					Q.push(pres);
					inq[pres] = true;
				}
			}
		}
	}
}

int main() {
	getgraph();
	DP();
	int T;
	scanf("%d", &T);
	for (; T; --T) {
		int x1, y1, x2, y2, x3, y3, f;
		scanf("%d%d%d%d%d%d%d", &x2, &y2, &x3, &y3, &x1, &y1, &f);
		swap(x1, y1); swap(x2, y2); swap(x3, y3);
		State S = State(x1, y1, x2, y2, x3, y3, f, 1);
		int ans = dis[M[S]];
		if (ans >= 0) printf("Lose in %d steps T.T!\n", ans);
		else puts("Lucky guy!");
	}
}
